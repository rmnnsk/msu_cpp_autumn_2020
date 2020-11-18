#include <iostream>
#include <functional>
#include <vector>

#include "my_format.h"

void test1()
{
    std::cout << "TEST 1" << std::endl;
    std::cout << "TEST FROM TASK DESCRIPTION." << std::endl;
    std::cout << R"(format("{1}+{1} = {0}", 2, "one"))" << std::endl;
    auto text = format("{1}+{1} = {0}", 2, "one");
    assert(text == "one+one = 2");
}

void test2()
{
    std::cout << "TEST 2" << std::endl;
    std::cout << "TESTING WRONG FORMAT STRINGS." << std::endl;
    std::cout << R"(format("{-1}+{1} = {0}", 2, "one"))" << std::endl;

    try {
        auto text = format("{-1}+{1} = {0}", 2, "one");
    }
    catch (WrongFormat_Exception& err) {
        std::cout << "Catch WrongFormat_Exception" << std::endl;
    }

    std::cout << R"(format("{first}+{1} = {0}", 2, "one"))" << std::endl;
    try {
        auto text = format("{first}+{1} = {0}", 2, "one");
    }
    catch (WrongFormat_Exception& err) {
        std::cout << "Catch WrongFormat_Exception" << std::endl;
    }

    std::cout << R"(format("{}+{1} = {0}", 2, "one"))" << std::endl;
    try {
        auto text = format("{}+{1} = {0}", 2, "one");
    }
    catch (WrongFormat_Exception& err) {
        std::cout << "Catch WrongFormat_Exception" << std::endl;
    }

    std::cout << R"(format("{1 + {1} = {0}", 2, "one"))" << std::endl;
    try {
        auto text = format("{ + {1} = {0}", 2, "one");
    }
    catch (WrongFormat_Exception& err) {
        std::cout << "Catch WrongFormat_Exception" << std::endl;
    }

    std::cout << R"(format("test}", 2, "one"))" << std::endl;
    try {
        auto text = format("test}", 2, "one");
    }
    catch (WrongFormat_Exception& err) {
        std::cout << "Catch WrongFormat_Exception" << std::endl;
    }

    std::cout << R"(format("{0} + {1} = {0"))" << std::endl;
    try {
        auto text = format("{0} + {1} = {0", 2, "one");
    }
    catch (WrongFormat_Exception& err) {
        std::cout << "Catch WrongFormat_Exception" << std::endl;
    }

    std::cout << R"(format("{0} + {0} = {1}{"))" << std::endl;
    try {
        auto text = format("{0} + {0} = {1}{", 2, "one");
    }
    catch (WrongFormat_Exception& err) {
        std::cout << "Catch WrongFormat_Exception" << std::endl;
    }
}

void test3()
{
    std::cout << "TEST 3" << std::endl;
    std::cout << "TESTING WRONG ARGS EXCEPTION ." << std::endl;

    std::cout << R"(format("{1}+{1} = {0}", 2, "one", "test"))" << std::endl;
    try {
        auto text = format("{1}+{1} = {0}", 2, "one", "test");
    }
    catch (LowArgs_Exception& err) {
        std::cout << "Catch WrongFormat_Exception" << std::endl;
    }

    std::cout << R"(format("{1}+{1} = {0}", 2))" << std::endl;
    try {
        auto text = format("{1}+{1} = {0}", 2);
    }
    catch (LowArgs_Exception& err) {
        std::cout << "Catch WrongFormat_Exception" << std::endl;
    }

    std::cout << R"(format("{0} + {1} = {12345678900}", 2, "one"))" << std::endl;
    try {
        auto text = format("{0} + {1} = {12345678900}", 2, "one");
    }
    catch (LowArgs_Exception& err) {
        std::cout << "Catch WrongFormat_Exception" << std::endl;
    }
}

void test4()
{
    std::cout << "TEST 4" << std::endl;
    std::cout << "ANOTHER WORK EXAMPLE" << std::endl;

    std::cout << R"(format("{001}+{1} = {0}", 2, "one"))" << std::endl;
    auto text = format("{001}+{1} = {0}", 2, "one");
    assert(text == "one+one = 2");

    std::cout << R"(format("{000}+{00000} = {1}", 2, 5000))" << std::endl;
    text = format("{000}+{00000} = {1}", 2, 5000);
    assert(text == "2+2 = 5000");

    std::cout << R"(format("{0}+{1} != {2}", 1234567, 7654321, "mandarinka"))" << std::endl;
    text = format("{0}+{1} != {2}", 1234567, 7654321, "mandarinka");
    assert(text == "1234567+7654321 != mandarinka");

    std::cout << R"(format("{0}+{1} != {2}", 1234567, 7654321, "mandarinka"))" << std::endl;
    text = format("{0}+{1} != {2}", 1234567, 7654321, "mandarinka");
    assert(text == "1234567+7654321 != mandarinka");


}

int main()
{
    std::vector<std::function<void()>> tests = {test1, test2, test3, test4};
    for (const auto& test : tests) {
        test();
        std::cout << std::endl;
    }
}