#pragma once

#include <iostream>
#include <string>

class BigInt
{
private:
    bool minus = false;
    int* number = nullptr;
    int size = 0;
    const int BASE = 10;
public:
    BigInt() = default;

    explicit BigInt(const std::string& num);

    BigInt(const int& num);

    BigInt(const BigInt& rhs);

    BigInt& operator=(const BigInt& rhs);

    BigInt(BigInt&&);

    BigInt& operator=(BigInt&& rhs);

    friend std::ostream& operator<<(std::ostream&, const BigInt&);

    BigInt operator+(const BigInt& rhs) const;

    BigInt operator-(const BigInt& rhs) const;

    BigInt operator*(const BigInt& rhs) const;

    BigInt operator-() const;

    bool operator==(const BigInt& rhs) const;

    bool operator!=(const BigInt& rhs) const;

    bool operator<(const BigInt& rhs) const;

    bool operator>(const BigInt& rhs) const;

    bool operator<=(const BigInt& rhs) const;

    bool operator>=(const BigInt& rhs) const;

    BigInt abs() const;

    bool empty() const;

    ~BigInt();

};

