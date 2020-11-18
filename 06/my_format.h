#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>
#include <cassert>

struct ReplaceInfo
{
    int first_ind;
    int last_ind;
    int arg_number;

    ReplaceInfo() = default;

    ReplaceInfo(int fi, int li, int arg) : first_ind(fi), last_ind(li), arg_number(arg) {};
};


class LowArgs_Exception : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Not enough arguments to format.";
    }
};

class WrongFormat_Exception : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Incorrect format string.";
    }
};

class WrongArg_Exception : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Argument cannot be used with output streams.";
    }
};

std::vector<std::string> process()
{
    return std::vector<std::string>();
}

template<class T, class ...Args>
std::vector<std::string> process(const T &cur, const Args &...other)
{
    std::vector<std::string> res;
    std::stringstream casting_stream;
    casting_stream << cur;
    res.push_back(casting_stream.str());
    auto proc_next = process(other...);
    res.insert(res.end(), proc_next.begin(), proc_next.end());
    return res;
}

template<class ...Args>
std::vector<std::string> get_args_strings(const Args &...args)
{
    return process(args...);
}

template<class ...Args>
std::string format(const std::string &fmt, const Args &...args)
{
    std::string tmp = fmt;
    int cur_ind = 0;
    bool inside_param = false;
    int max_param = -1;
    int last_open = -1;
    std::vector<ReplaceInfo> to_replace;
    while (cur_ind < fmt.size()) {

        if (fmt[cur_ind] == '{') {
            if (inside_param) {
                throw WrongFormat_Exception();
            }
            last_open = cur_ind;
            inside_param = true;
        } else if (fmt[cur_ind] == '}') {
            if (!inside_param || last_open == cur_ind - 1) {
                throw WrongFormat_Exception();
            }
            std::string arg_string = fmt.substr(last_open + 1, cur_ind - last_open - 1);
            int arg_ind;
            try {
                arg_ind = std::stoi(arg_string);
            }
            catch (std::out_of_range &exc){
                throw LowArgs_Exception();
            }
            to_replace.emplace_back(last_open, cur_ind, arg_ind);
            max_param = std::max(max_param, arg_ind);
            inside_param = false;
        } else if (inside_param) {
            auto sym = static_cast<unsigned char>(fmt[cur_ind]);
            if (!isdigit(sym)) {
                throw WrongFormat_Exception();
            }
        }
        cur_ind++;
    }
    if (inside_param) {
        throw WrongFormat_Exception();
    }
    if (max_param >= sizeof...(args)) {
        throw LowArgs_Exception();
    }
    auto args_strings = get_args_strings(args...);
    int delta = 0;
    for (const auto &info : to_replace) {
        tmp.replace(info.first_ind - delta, info.last_ind - info.first_ind + 1, args_strings[info.arg_number]);
        delta += (info.last_ind - info.first_ind + 1) - (int) args_strings[info.arg_number].size();
    }

    return tmp;
}
