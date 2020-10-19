#include <algorithm>
#include "parser.h"

void test1()
{
    std::cout << "TEST 1" << std::endl;
    std::cout << "Create parser and parse some strings." << std::endl;
    TokenParser par{};
    std::string test_string = "Hello      world i'am 1st string. I   am  10 minutes old. ";
    std::vector<std::string> ans = {"Hello", "world", "i'am", "1st", "string.", "I", "am", "10", "minutes", "old."};
    std::cout << "String to parse: " << test_string << std::endl;
    auto res = par.parse(test_string);
    assert(ans == res);
    std::cout << std::endl;

    test_string = "Oh, hi, I'am 2nd string, i have 123123123 questions to you. <3";
    ans = {"Oh,", "hi,", "I'am", "2nd", "string,", "i", "have", "123123123", "questions", "to",
           "you.", "<3"};
    std::cout << "String to parse: " << test_string << std::endl;
    res = par.parse(test_string);
    assert(ans == res);
}

void test2()
{
    std::cout << "TEST 2" << std::endl;
    std::cout << "Create parser and change start and finish callbacks." << std::endl;
    TokenParser par{};
    par.SetStartCallback([]() {
        std::cout << "I'am new start callback" << std::endl;
    });
    par.SetFinishCallback([]() {
        std::cout << "I'am new finish callback" << std::endl;
    });
    std::string test_string = "Let's see our new callbacks.";
    std::cout << "String to parse: " << test_string << std::endl;
    auto res = par.parse(test_string);
}

void test3()
{
    std::cout << "TEST 3" << std::endl;
    std::cout << "Create parser and change STRING and NUMBER callbacks." << std::endl;
    TokenParser par{};
    par.SetStringCallback([](std::string &token) {
        std::transform(token.begin(), token.end(), token.begin(),
                       [](unsigned char c) -> unsigned char { return std::tolower(c); });
        std::cout << "Found string + to_lower -> " << token << std::endl;

    });
    par.SetNumberCallback([](const std::string &token) {
        std::cout << "Found number " << token << " + mod 10 -> " << std::stoi(token) % 10 << std::endl;
    });
    std::string test_string = "WoooooooooW      2 BRAND NeW \n\
                              callbacks. Such many tests 123321 .";
    std::cout << "String to parse: " << test_string << std::endl;
    auto res = par.parse(test_string);
}

int main()
{
    std::vector<std::function<void()>> tests = {test1, test2, test3};
    for (const auto &test: tests) {
        test();
        std::cout << std::endl;
    }
}