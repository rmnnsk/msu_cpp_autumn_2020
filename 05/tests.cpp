#include <iostream>
#include <vector>
#include <functional>
#include <sstream>
#include <cassert>
#include "serializer.h"

struct Data_TEST1
{
    uint64_t a;
    bool b;
    uint64_t c;

    template<class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
};

struct Data_TEST2
{
    bool a;
    bool b;
    bool c;
    uint64_t d;

    template<class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c, d);
    }
};

void test1()
{
    std::cout << "TEST 1" << std::endl;
    std::cout << "TEST FROM DESCRIPTION." << std::endl;
    std::cout << "struct Data{uint64_t, bool, uint64_t}" << std::endl;


    std::cout << "INIT: Data x{1, true, 2}" << std::endl;
    Data_TEST1 x{1, true, 2};

    std::stringstream stream;

    Serializer serializer(stream);
    std::cout << "Save x to stringstream." << std::endl;
    serializer.save(x);

    Data_TEST1 y{0, false, 0};

    Deserializer deserializer(stream);
    std::cout << "Load struct from stringstream and save to y." << std::endl;
    const Error err = deserializer.load(y);

    std::cout << "Check for NoError and x == y." << std::endl;
    assert(err == Error::NoError);

    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
}

void test2()
{
    std::cout << "TEST 2" << std::endl;
    std::cout << "CHECK FOR DESERIALIZATION FROM STREAM." << std::endl;
    std::stringstream inp;
    std::cout << "Put (false false true 135) in stream." << std::endl;
    inp << "false false true 135";
    Deserializer deserializer(inp);

    Data_TEST2 x{false, false, false, 0};
    std::cout << "Load from stream to x." << std::endl;
    const Error err = deserializer.load(x);

    std::cout << "Check for NoError and fields equality." << std::endl;
    assert(err == Error::NoError);
    assert(!x.a);
    assert(!x.b);
    assert(x.c);
    assert(x.d == 135);
}

void test3()
{
    std::cout << "TEST 3" << std::endl;
    std::cout << "CHECK FOR DESERIALIZATION ERROR DETECTION.(bool)" << std::endl;
    std::stringstream inp;
    std::cout << "Put (false salsa true 135) in stream." << std::endl;
    inp << "false salsa true 135";
    Deserializer deserializer(inp);

    Data_TEST2 x{false, false, false, 0};
    std::cout << "Load from stream to x." << std::endl;
    const Error err = deserializer.load(x);

    std::cout << "Check for CorruptedArchive." << std::endl;
    assert(err == Error::CorruptedArchive);
}

void test4()
{
    std::cout << "TEST 4" << std::endl;
    std::cout << "CHECK FOR DESERIALIZATION ERROR DETECTION.(uint64_t)" << std::endl;
    std::stringstream inp;
    std::cout << "Put (false false true 100000000000000000000) in stream." << std::endl;
    inp << "false false true 100000000000000000000";
    Deserializer deserializer(inp);

    Data_TEST2 x{false, false, false, 0};
    std::cout << "Load from stream to x." << std::endl;
    const Error err = deserializer.load(x);

    std::cout << "Check for CorruptedArchive." << std::endl;
    assert(err == Error::CorruptedArchive);

}

void test5()
{
    std::cout << "TEST 5" << std::endl;
    std::cout << "CHECK FOR CORRECT SERIALIZATION" << std::endl;
    std::stringstream out;
    Serializer serializer(out);

    std::cout << "INIT x{false, true, false, 123123123}" << std::endl;
    Data_TEST2 x{false, true, false, 123123123};
    std::cout << "Load x to stream." << std::endl;
    serializer.save(x);
    std::cout << "Check stream.str() == \"false true false 123123123 \"" << std::endl;
    assert(out.str() == "false true false 123123123 ");

}

int main()
{
    std::vector<std::function<void()>> tests = {test1, test2, test3, test4, test5};

    for (const auto& test : tests) {
        test();
        std::cout << std::endl;
    }
}