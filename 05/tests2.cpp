#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <sstream>
#include <cassert>
#include "serializer.h"

struct Data_TEST6
{
    uint64_t a;
    bool b;
    std::string c;

    template<class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
};

void test6()
{
    std::cout << "TEST 6" << std::endl;
    std::cout << "CHECK FOR WRONG STRUCT" << std::endl;

    std::cout << "INIT: Data x{1, true, \"abc\"}" << std::endl;
    Data_TEST6 x{1, true, "abc"};

    std::stringstream stream;

    Serializer serializer(stream);
    std::cout << "Save x to stringstream." << std::endl;
    serializer.save(x);

    Data_TEST6 y{0, false, ""};

    Deserializer deserializer(stream);
    std::cout << "Load struct from stringstream and save to y." << std::endl;
    const Error err = deserializer.load(y);

    std::cout << "Check for NoError and x == y." << std::endl;
    assert(err == Error::NoError);

    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
}

int main()
{
    std::vector<std::function<void()>> tests = {test6};

    for (const auto& test : tests) {
        test();
        std::cout << std::endl;
    }
}