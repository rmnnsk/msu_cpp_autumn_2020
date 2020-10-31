#include <iostream>
#include <vector>
#include <functional>
#include <cassert>
#include "BigInt.h"

void test1()
{
    std::cout << "TEST CONSTRUCTORS AND OUTPUT." << std::endl;

    BigInt a = 1337;
    BigInt b("100500100500100500100500");
    std::cout << "Init a = " << a << " and " << "b = " << b << std::endl;
    BigInt a_copy(a);
    BigInt b_moved(std::move(b));
    std::cout << "Copied from a = " << a_copy << std::endl;
    std::cout << "Moved from b = " << b_moved << std::endl;
    assert(b.empty());
}

void test2()
{
    std::cout << "TEST ASSIGNMENT OPERATOR AND (UN)EQUALITY OPERATORS" << std::endl;
    BigInt a = 1337;
    BigInt a_copy = a;
    BigInt b = 1337;
    std::cout << "Init a = " << a << ", a_copy = a, b = " << b << std::endl;
    std::cout << "Check for a == b and a_copy == b" << std::endl;
    assert(a == b);
    assert(a_copy == b);
    std::cout << "Make a = a + 1" << std::endl;
    a = a + 1;
    std::cout << "Check for a != b and a != a_copy" << std::endl;
    assert(a != b);
    assert(a != a_copy);
    std::cout << "Move b to b_moved." << std::endl;
    BigInt b_moved = std::move(b);
    assert(b_moved == 1337);
    assert(b.empty());
    std::cout << "b_moved = " << b_moved << std::endl;

}

void test3()
{
    std::cout << "TEST COMPARISION OPERATORS" << std::endl;

    BigInt a("12345678901234567890");
    BigInt b("-12345678901234567890");
    BigInt zero = 0;
    BigInt small = 1337;
    std::cout << "Init a = " << a << ", b = " << b << ", zero = " << zero << ", small = " << small << std::endl;
    std::cout << "Check for a > b." << std::endl;
    assert(a > b);
    std::cout << "Check for a <= a." << std::endl;
    assert(a <= a);
    std::cout << "Check for small < a." << std::endl;
    assert(small < a);
    std::cout << "Check for small >= zero." << std::endl;
    assert(small >= zero);
    std::cout << "Check for !(zero < zero)." << std::endl;
    assert(!(zero < zero));
}


void test4()
{
    std::cout << "TEST ARITHMETIC OPERATORS" << std::endl;
    BigInt a("12345678901234567890");
    BigInt min_a("-12345678901234567890");
    BigInt b("987654321123456789");
    std::cout << "Init a = " << a << ", min_a = " << min_a << ", b = " << b << std::endl;
    BigInt res1 = 0; // a + min_a
    std::cout << "Check for a + min_a = min_a + a = 0" << std::endl;
    std::cout << min_a + a << std::endl;
    assert(min_a + a == 0);
    BigInt res2("24691357802469135780"); // a - min_a
    std::cout << "Check for a - min_a == " << res2 << " and  min_a - a = " << -res2  << std::endl;
    assert(a - min_a == res2 && min_a - a == -res2);
    BigInt res3("11358024580111111101");
    std::cout << "Check for a - b = 11358024580111111101" << std::endl;
    assert(a - b == res3);
    BigInt res4("13333333222358024679");
    std::cout << "Check for a + b = 13333333222358024679" << std::endl;
    assert(a + b == res4);
    std::cout << "Check for a * b = 12193263114007011086297820577501905210" << std::endl;
    BigInt res5("12193263114007011086297820577501905210");
    assert(a * b == res5);
    std::cout << "Check for b * 0 = 0" << std::endl;
    assert(b * 0 == 0);
    std::cout << "Check for b * -1 = -b" << std::endl;
    assert(b * -1 == -b);
    std::cout << "Check for (b + 1) * 2 = b + b + 2" << std::endl;
    assert((b + 1) * 2 == b + b + 2);
    std::cout << "Check for b + (-b) == a * a * 0" << std::endl;
    assert(b + (-b) == a * a * 0);
}

int main()
{
    std::vector<std::function<void()>> tests = {test1, test2, test3, test4};
    for (const auto& test : tests) {
        test();
        std::cout << std::endl;
    }
}