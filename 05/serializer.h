#pragma once

#include <iostream>
#include <sstream>
#include <string>

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
    static constexpr char Separator = ' ';

public:

    explicit Serializer(std::ostream& out) : out_(out)
    {};

    template<class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template<class... ArgsT>
    Error operator()(ArgsT... args)
    {
        return process(args...);
    }

    Error process(uint64_t token)
    {
        out_ << token << Separator;
        return Error::NoError;
    }

    Error process(bool token)
    {
        if (token) {
            out_ << "true";
        } else {
            out_ << "false";
        }
        out_ << Separator;
        return Error::NoError;
    }


    template<typename T, typename ...ArgsT>
    Error process(T cur, ArgsT ...other)
    {
        Error cur_state = process(cur);
        if (cur_state != Error::NoError) {
            return cur_state;
        }
        return process(other...);
    }

private:
    // process использует variadic templates
    std::ostream& out_;
};

class Deserializer
{
    static constexpr char Separator = ' ';

public:

    explicit Deserializer(std::istream& in) :
            in_(in)
    {};

    template<class T>
    Error load(T& object)
    {
        return object.serialize(*this);
    }

    template<class... ArgsT>
    Error operator()(ArgsT& ...args)
    {
        return process(args...);
    }

    Error process(uint64_t& token)
    {
        std::string tmp;
        if (!(in_ >> tmp) || tmp[0] == '-') {
            return Error::CorruptedArchive;
        }
        std::stringstream casting_stream;
        casting_stream << tmp;
        uint64_t checker;
        if (!(casting_stream >> checker)) {
            return Error::CorruptedArchive;
        }
        token = checker;
        return Error::NoError;
    }

    Error process(bool& token)
    {
        std::string token_text;
        if (!(in_ >> token_text)) {
            return Error::CorruptedArchive;
        }
        if (token_text == "true") {
            token = true;
        } else if (token_text == "false") {
            token = false;
        } else {
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }


    template<typename T, typename ...ArgsT>
    Error process(T& cur, ArgsT& ...other)
    {
        Error cur_state = process(cur);
        if (cur_state != Error::NoError) {
            return cur_state;
        }
        return process(other...);
    }

private:
// process использует variadic templates
    std::istream& in_;
};