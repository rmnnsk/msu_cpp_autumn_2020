#include <cassert>
#include <iostream>
#include <vector>
#include <functional>

#include "Matrix.h"

void test1()
{
    std::cout << "TEST 1" << std::endl;
    std::cout << "Check getRows and getColumns" << std::endl;
    int rows = 3;
    int columns = 4;
    std::cout << "Create Matrix m1(3, 4)" << std::endl;
    Matrix m1(rows, columns);
    std::cout << "Check m1.getRows() == " << rows << std::endl;
    assert(m1.getRows() == rows);
    std::cout << "Check m1.getColumns() == " << columns << std::endl;
    assert(m1.getColumns() == columns);
}

void test2()
{
    std::cout << "TEST 2" << std::endl;
    std::cout << "Check assignment to element and receiving element." << std::endl;
    int rows = 3;
    int columns = 4;
    std::cout << "Create Matrix m1(3, 4)" << std::endl;
    Matrix m1(rows, columns);
    std::cout << "Assign m1[2][3] = 4" << std::endl;
    m1[2][3] = 4;
    std::cout << "Check for m1[2][3] == 4" << std::endl;
    assert(m1[2][3] == 4);
    std::cout << "Assign m1[3][3] = 5" << std::endl;
    try {
        m1[3][3] = 5;
    }
    catch (const std::out_of_range& oor) {

        std::cout << "STD::OUT_OF_RANGE" << std::endl;
    }
}

void test3()
{
    std::cout << "TEST 3" << std::endl;
    std::cout << "Check multiplying." << std::endl;
    int rows = 3;
    int columns = 4;
    std::cout << "Create two same matrices m1(3, 4) and m2(3,4)" << std::endl;
    Matrix m1(rows, columns);
    Matrix m2(rows, columns);
    std::cout << "Assign m1[2][3] = m2[2][3] = 4" << std::endl;
    m1[2][3] = m2[2][3] = 4;
    std::cout << "Assign m1[0][2] = m2[0][2] = 10" << std::endl;
    m1[0][2] = m2[0][2] = 10;
    int mul = 3;
    std::cout << "m1 *= " << mul << std::endl;
    m1 *= mul;
    std::cout << "Check for m1[i][j] == m2[i][j] * " << mul << std::endl;
    for (int i = 0; i < m1.getRows(); i++) {
        for (int j = 0; j < m1.getColumns(); j++) {
            assert(m1[i][j] == m2[i][j] * mul);
        }
    }
}

void test4()
{
    std::cout << "TEST 4" << std::endl;
    std::cout << "Check addition." << std::endl;
    int rows = 3;
    int columns = 4;
    std::cout << "Create two matrices m1(3, 4) and m2(3, 4)" << std::endl;
    Matrix m1(rows, columns);
    Matrix m2(rows, columns);
    std::cout << "Assign m1[2][3] = 7 and m2[2][3] = 4" << std::endl;
    m1[2][3] = 7;
    m2[2][3] = 4;
    std::cout << "Assign m1[1][2] = -1 and m2[0][2] = 10" << std::endl;
    m1[1][2] = -1;
    m2[0][2] = 10;
    std::cout << "res = m1 + m2" << std::endl;
    Matrix res = m1 + m2;
    std::cout << "Check for res[i][j] ==  m1[i][j] + m2[i][j]" << std::endl;
    for (int i = 0; i < m1.getRows(); i++) {
        for (int j = 0; j < m1.getColumns(); j++) {
            assert(res[i][j] == m1[i][j] + m2[i][j]);
        }
    }
}

void test5()
{
    std::cout << "TEST 5" << std::endl;
    std::cout << "Check operators == and !=." << std::endl;
    int rows = 3;
    int columns = 4;
    std::cout << "Create two matrices m1(3, 4) and m2(3, 4)" << std::endl;
    Matrix m1(rows, columns);
    Matrix m2(rows, columns);
    std::cout << "Assign m1[2][3] = 7 and m2[2][3] = 4" << std::endl;
    m1[2][3] = 7;
    m2[2][3] = 4;
    std::cout << "Check for m1 != m2" << std::endl;
    assert(m1 != m2);
    std::cout << "Create two matrices m3(3, 4) and m4(3, 4)" << std::endl;
    Matrix m3(rows, columns);
    Matrix m4(rows, columns);
    std::cout << "Assign m3[2][3] = 5 and m4[2][3] = 5" << std::endl;
    m3[2][3] = 5;
    m4[2][3] = 5;
    std::cout << "Check for m3 == m4" << std::endl;
    assert(m3 == m4);
}

void test6()
{
    std::cout << "TEST 6" << std::endl;
    std::cout << "Check output" << std::endl;
    int rows = 3;
    int columns = 4;
    std::cout << "Create matrix m1(3, 4)" << std::endl;
    Matrix m1(rows, columns);
    std::cout << "Assign m1[2][3] = 7, m1[1][3] = 4, m1[0][0] = 10, m1[2][1] = 15" << std::endl;
    m1[2][3] = 7;
    m1[1][3] = 4;
    m1[0][0] = 10;
    m1[2][1] = 15;
    std::cout << m1 << std::endl;
}

int main()
{
    std::vector<std::function<void()>> tests = {test1, test2, test3, test4, test5, test6};
    for (const auto& test: tests) {
        test();
        std::cout << std::endl;
    }
}