#include "Matrix.h"


Matrix::Matrix(int r, int c) : rows(r), cols(c)
{
    matr = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matr[i] = new int[cols]{};
    }
}

int Matrix::getRows() const
{
    return rows;
}

int Matrix::getColumns() const
{
    return cols;
}

Matrix::Proxy Matrix::operator[](int r) const
{
    if (0 <= r && r < rows)
        return Proxy(matr[r], cols);
    throw std::out_of_range("");
}


Matrix& Matrix::operator*=(const int& num)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matr[i][j] *= num;
        }
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix& other) const
{
    Matrix tmp(rows, cols);
    if (this->rows != other.getRows() || this->cols != other.getColumns()) {
        throw std::out_of_range("Different sizes");
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            tmp[i][j] = this->matr[i][j] + other[i][j];
        }
    }
    return tmp;
}

bool Matrix::operator==(const Matrix& other) const
{
    if (this->rows != other.rows || this->cols != other.cols) {
        return false;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (this->matr[i][j] != other[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& other) const
{
    return !((*this) == other);
}

Matrix::~Matrix()
{
    for (int i = 0; i < rows; i++) {
        delete[] matr[i];
    }
    delete[] matr;
}

std::ostream& operator<<(std::ostream& os, const Matrix& obj)
{
    for (int i = 0; i < obj.rows; i++) {
        for (int j = 0; j < obj.cols; j++) {
            os << obj.matr[i][j] << ' ';
        }
        os << std::endl;
    }
    return os;
}

