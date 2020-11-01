#include "BigInt.h"
#include <iomanip>

int num_len(int num)
{
    if (num == 0) {
        return 1;
    }
    int len = 0;
    while (num > 0) {
        len += 1;
        num /= 10;
    }
    return len;
}


BigInt::BigInt(const std::string& num)
{
    std::string rem_sign = num;
    if (!rem_sign.empty() && num[0] == '-') {
        rem_sign.erase(0, 1);
        minus = true;
    }
    int base_len = num_len(BASE) - 1;
    size = (num.size() + base_len - 1) / base_len;
    number = new int[size]{};
    for (int i = (int) rem_sign.size(), free = 0; i > 0; i -= base_len, free++) {
        if (i < base_len) {
            number[free] = std::stoi(rem_sign.substr(0, i));
        }
        else {
            number[free] = std::stoi(rem_sign.substr(i - 9, 9));
        }
    }
}

BigInt::BigInt(int num) : size(num_len(std::abs(num)))
{
    int tmp = num;
    if (tmp < 0) {
        minus = true;
        tmp = std::abs(num);
    }
    number = new int[size]{};
    for (int i = 0; i < size; i++) {
        number[i] = tmp % BASE;
        tmp /= BASE;
    }
}

BigInt::BigInt(const BigInt& rhs) : size(rhs.size), minus(rhs.minus)
{
    number = new int[size]{};
    for (int i = 0; i < size; i++) {
        number[i] = rhs.number[i];
    }
}

BigInt& BigInt::operator=(const BigInt& rhs)
{
    if (this == &rhs) {
        return *this;
    }
    size = rhs.size;
    minus = rhs.minus;
    int* tmp = new int[size]{};
    delete[] number;
    number = tmp;
    std::copy(number, number + size, rhs.number);
    return *this;
}

BigInt::BigInt(BigInt&& rhs) : size(rhs.size), minus(rhs.minus)
{
    number = rhs.number;
    rhs.number = nullptr;
    rhs.size = 0;
    rhs.minus = false;
}

BigInt& BigInt::operator=(BigInt&& rhs)
{
    if (this == &rhs) {
        return *this;
    }
    size = rhs.size;
    minus = rhs.minus;
    number = rhs.number;
    rhs.number = nullptr;
    rhs.size = 0;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const BigInt& big_num)
{
    int sz = big_num.size;
    while (sz - 1 >= 0 && big_num.number[sz - 1] == 0) {
        sz -= 1;
    }
    if (sz == 0) {
        os << 0;
        return os;
    }
    if (big_num.minus) {
        os << '-';
    }
    int fill_len = num_len(big_num.BASE) - 1;
    os << big_num.number[sz - 1];
    for (int i = sz - 2; i >= 0; i--) {
        os << std::setfill('0') << std::setw(fill_len) << big_num.number[i];
    }
    return os;
}

BigInt BigInt::operator+(const BigInt& rhs) const
{
    if (minus != rhs.minus) {
        if (minus) {
            return rhs - this->abs();
        } else {
            return *this - rhs.abs();
        }
    }

    int* bigger = (size > rhs.size) ? number : rhs.number;
    size_t bigger_size = (size > rhs.size) ? size : rhs.size;

    BigInt res{};
    res.number = new int[bigger_size + 1]{};
    res.size = bigger_size + 1;
    res.minus = minus;

    int carry = 0;
    for (int i = 0; i < std::min(size, rhs.size); i++) {
        int tmp = this->number[i] + rhs.number[i] + carry;
        res.number[i] = tmp % BASE;
        carry = tmp / BASE;
    }

    for (int i = std::min(size, rhs.size); i < bigger_size; i++) {
        int tmp = bigger[i] + carry;
        res.number[i] = tmp % BASE;
        carry = tmp / BASE;
    }
    res.number[bigger_size] = carry;
    return res;
}

BigInt BigInt::operator-(const BigInt& rhs) const
{
    if (minus != rhs.minus) {
        if (minus) {
            return -(this->abs() + rhs);
        } else {
            return *this + rhs.abs();
        }
    }
    BigInt bigger = *this;
    BigInt smaller = rhs;
    bool swapped = false;
    if (bigger < smaller) {
        std::swap(bigger, smaller);
        swapped = true;
    }

    BigInt res = bigger;

    int min_size = std::min(this->size, rhs.size);
    int carry = 0;
    int i = 0;
    while (i < min_size || carry) {
        if (i < min_size) {
            res.number[i] -= (carry + smaller.number[i]);
        } else {
            res.number[i] -= carry;
        }
        carry = res.number[i] < 0;
        if (carry) {
            res.number[i] += BASE;
        }
        i++;
    }
    res.minus = swapped;
    return res;

}

BigInt BigInt::operator-() const
{
    BigInt res = *this;
    res.minus ^= true;
    return res;
}

BigInt BigInt::operator*(const BigInt& rhs) const
{
    BigInt res{};
    res.number = new int[size + rhs.size + 1]{};
    res.size = size + rhs.size + 1;
    res.minus = minus ^ rhs.minus;

    long long carry = 0;
    int i = 0;
    while (i < size) {
        int j = 0;
        while (j < rhs.size || carry) {
            long long cur;
            if (j < rhs.size) {
                cur = res.number[i + j] * 1LL + number[i] * 1LL * rhs.number[j] + carry;
            } else {
                cur = res.number[i + j] * 1LL + carry;
            }
            res.number[i + j] = (cur % BASE);
            carry = cur / BASE;
            j++;
        }
        i++;
    }
    return res;
}

bool BigInt::operator==(const BigInt& rhs) const
{
    if (minus != rhs.minus) {
        return false;
    }
    int cur_ind = (int) size - 1;
    while (cur_ind - 1 >= 0 && number[cur_ind] == 0) {
        cur_ind -= 1;
    }
    int rhs_cur_ind = (int) rhs.size - 1;
    while (rhs_cur_ind - 1 >= 0 && rhs.number[rhs_cur_ind] == 0) {
        rhs_cur_ind -= 1;
    }
    if (cur_ind != rhs_cur_ind) {
        return false;
    }
    while (cur_ind >= 0) {
        if (number[cur_ind] != rhs.number[rhs_cur_ind]) {
            return false;
        }
        cur_ind -= 1;
        rhs_cur_ind -= 1;
    }
    return true;
}

bool BigInt::operator!=(const BigInt& rhs) const
{
    return !(rhs == *this);
}

bool BigInt::operator<(const BigInt& rhs) const
{
    if (minus != rhs.minus) {
        return minus;
    }
    int cur_ind = (int) size - 1;
    while (cur_ind - 1 >= 0 && number[cur_ind] == 0) {
        cur_ind -= 1;
    }
    int rhs_cur_ind = (int) rhs.size - 1;
    while (rhs_cur_ind - 1 >= 0 && rhs.number[rhs_cur_ind] == 0) {
        rhs_cur_ind -= 1;
    }
    if (cur_ind != rhs_cur_ind) {
        return (cur_ind < rhs_cur_ind) ^ minus;
    }
    while (cur_ind >= 0) {
        if (number[cur_ind] != rhs.number[rhs_cur_ind]) {
            return (number[cur_ind] < rhs.number[rhs_cur_ind]) ^ minus;
        }
        cur_ind -= 1;
        rhs_cur_ind -= 1;
    }
    return minus;
}

bool BigInt::operator>(const BigInt& rhs) const
{
    return rhs < *this;
}

bool BigInt::operator<=(const BigInt& rhs) const
{
    return !(rhs < *this);
}

bool BigInt::operator>=(const BigInt& rhs) const
{
    return !(*this < rhs);
}

BigInt BigInt::abs() const
{
    BigInt res = *this;
    res.minus = false;
    return res;
}

bool BigInt::empty() const
{
    return (number == nullptr);
}

BigInt::~BigInt()
{
    delete[] number;
}