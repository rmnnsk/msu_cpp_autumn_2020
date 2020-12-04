#include <iostream>
#include <functional>
#include <vector>
#include <cassert>
#include "my_vector.h"

class TestClass
{

public:
    static int alive;

    TestClass()
    {
        alive++;
        std::cout << "TestClass()" << std::endl;
    };

    ~TestClass()
    {
        alive--;
        std::cout << "~TestClass()" << std::endl;
    }
};

int TestClass::alive;

void test1()
{
    std::cout << "TEST 1" << std::endl;
    std::cout << "Test vector initializing, resize, reserve" << std::endl;
    std::cout << "Init MyVector<int>(10)" << std::endl;
    MyVector<int> vec1(10);
    std::cout << "check size, capacity" << std::endl;
    assert(vec1.size() == 10);
    assert(vec1.capacity() >= 10);

    std::cout << "Resizing vector to 15." << std::endl;
    vec1.resize(15);
    std::cout << "check size, capacity and vec[11] == 0" << std::endl;
    assert(vec1.size() == 15);
    assert(vec1.capacity() >= 15);
    assert(vec1[11] == 0);

    try {
        std::cout << "Try to reserve 2000000000 ints" << std::endl;
        vec1.reserve(2000000000);
    }
    catch (const std::bad_alloc& exc) {
        std::cout << "Catched std::bad_alloc" << std::endl;
    }
    std::cout << "Try to reserve 200 ints" << std::endl;
    vec1.reserve(200);
    std::cout << "check capacity >= 200" << std::endl;
    assert(vec1.capacity() >= 200);

    std::cout << "Init MyVector<TestClass>(3)" << std::endl;
    TestClass::alive = 0;
    MyVector<TestClass> vec(3);
    std::cout << "Resize to size=3" << std::endl;
    vec.resize(1);
    std::cout << "Check for TestClass::alive == 1" << std::endl;
    assert(TestClass::alive == 1);

}

void test2()
{
    std::cout << "TEST 2" << std::endl;
    std::cout << "Test operator[] and assignment" << std::endl;
    std::cout << "Init MyVector<std::string>(10,\"abc\")" << std::endl;
    MyVector<std::string> vec_str(10, "abc");
    std::cout << "Check for vec[3] == \"abc\" " << std::endl;
    assert(vec_str[3] == "abc");
    std::cout << "Assign vec[5] == \"test\" " << std::endl;
    vec_str[5] = "test";
    std::cout << "Check for vec[5] == \"test\" " << std::endl;
    assert(vec_str[5] == "test");
}

void test3()
{
    std::cout << "TEST 3" << std::endl;
    std::cout << "Test push_back, emplace_back, pop_back" << std::endl;

    std::cout << "Init MyVector<int>(5)" << std::endl;
    MyVector<std::pair<int, int>> vec;
    vec.resize(5);
    std::cout << "push_back {-100, 123} to vector" << std::endl;
    vec.push_back({-100, 123});
    std::cout << "check size and vec[5] == {-100, 123}" << std::endl;
    assert(vec.size() == 6);
    assert(vec[5] == std::make_pair(-100, 123));

    std::cout << "Emplace back {10, 20} to vector" << std::endl;
    vec.emplace_back(10, 20);
    std::cout << "check size and vec[6] == {10, 20}" << std::endl;
    assert(vec.size() == 7);
    assert(vec[6] == std::make_pair(10, 20));

    std::cout << "Pop back from vector" << std::endl;
    vec.pop_back();
    std::cout << "check size and vec[5] == {-100, 123}" << std::endl;
    assert(vec.size() == 6);
    assert(vec[5] == std::make_pair(-100, 123));
}

void test4() {
    std::cout << "TEST 4" << std::endl;
    std::cout << "Testing clear and empty." << std::endl;
    MyVector<TestClass> vec(3);
    assert(!vec.empty());
    std::cout << "Clearing vec" << std::endl;
    vec.clear();
    std::cout << "Cleared" << std::endl;
    assert(vec.empty());
}

void test5() {
    std::cout << "TEST 5" << std::endl;
    std::cout << "Iterators test." << std::endl;
    MyVector<int> vec;
    std::cout << "Filling vector with 1, 2, ... , 10" << std::endl;
    for (int i = 1; i <= 10; i++) {
        vec.push_back(i);
    }
    std::cout << "Test iterators in cycle " << std::endl;
    int tmp = 1;
    for (auto it = vec.begin(); it != vec.end(); it++) {
        assert(*it == tmp);
        std::cout << *it << ' ';
        tmp++;
    }
    std::cout << std::endl;
    std::cout << "Test reverse_iterators in cycle " << std::endl;
    tmp = 10;
    for (auto it = vec.rbegin(); it != vec.rend(); it++) {
        assert(*it == tmp);
        std::cout << *it << ' ';
        tmp--;
    }
    std::cout << std::endl;

    std::cout << std::endl << "Test random accessing" << std::endl;
    auto beg = vec.begin();
    auto end = vec.end();
    std::cout << "*(vec.begin() + 5) == 6" << std::endl;
    assert(*(beg + 5) == 6);
    std::cout << "*(vec.end() - 1) == 10" << std::endl;
    assert(*(end - 1) == 10);
    std::cout << "vec.begin()[3] == 4" << std::endl;
    assert(vec.begin()[3] == 4);

    std::cout << "*(++vec.begin()) = 2" << std::endl;
    assert(*(++beg) == 2);
    std::cout << "*(vec.begin()--) = 1" << std::endl;
    assert(*(vec.begin()--) = 1);

    std::cout << std::endl << "Test (in)equality : "  << std::endl;
    std::cout << "vec.begin() == vec.begin()" << std::endl;
    assert(vec.begin() == vec.begin());
    std::cout << "vec.begin() != vec.end()" << std::endl;
    assert(vec.begin() != vec.end());
    std::cout << "vec.begin() < vec.end()" << std::endl;
    assert(vec.begin() < vec.end());
}

int main()
{
    std::vector<std::function<void()>> tests = {test1, test2, test3, test4, test5};
    for (const auto& test : tests) {
        test();
        std::cout << "------------------------------------------------------------------" << std::endl;
    }
    return 0;
}
