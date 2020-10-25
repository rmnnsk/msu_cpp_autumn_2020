#pragma once

#include <iostream>
class Matrix
{
private:
    int rows = 0;
    int cols = 0;
    int** matr = nullptr;

    class Proxy
    {
    private:
        friend Matrix;
        int* row = nullptr;
        int row_size = 0;

        Proxy(int* r, int rs) : row(r), row_size(rs)
        {}

    public:
        int& operator[](int c) const
        {
            if (0 <= c && c < row_size)
                return row[c];
            throw std::out_of_range("");
        }
    };

public:
    Matrix(int r, int c);

    int getRows() const;

    int getColumns() const;

    Proxy operator[](int r) const;

    friend std::ostream& operator<<(std::ostream&, const Matrix&);

    Matrix& operator*=(const int& num);
    Matrix operator+(const Matrix& other) const;

    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;

    ~Matrix();
};