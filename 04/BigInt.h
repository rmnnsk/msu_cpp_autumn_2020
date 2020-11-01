#pragma once

#include <iostream>
#include <string>

class BigInt
{
private:
    bool minus = false;
    int* number = nullptr;
    size_t size = 0;
    const int BASE = 1000000000;
public:
    BigInt() = default;

    explicit BigInt(const std::string& num);

    BigInt(int num);

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

