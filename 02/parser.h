#pragma once

#include <functional>
#include <iostream>
#include <vector>
#include <cassert>
#include <cctype>

class TokenParser
{
private:
    std::function<void()> start_callback = []() {
        std::cout << "Start parsing." << std::endl;
    };
    std::function<void(std::string token)> number_token_callback = [](std::string token) {
        std::cout << "Found number : " << token << std::endl;
    };
    std::function<void(std::string token)> string_token_callback = [](std::string token) {
        std::cout << "Found string : " << token << std::endl;
    };
    std::function<void()> finish_callback = []() {
        std::cout << "Finish parsing." << std::endl;
    };

public:
    TokenParser() = default;

    std::vector<std::string> parse(const std::string& st);

    void SetStartCallback(const std::function<void()>& st_callback);

    void SetNumberCallback(const std::function<void(std::string token)>& num_callback);

    void SetStringCallback(const std::function<void(std::string token)>& str_callback);

    void SetFinishCallback(const std::function<void()>& fin_callback);
};