#include <algorithm>
#include <concepts>
#include <iostream>
#include <format>
#include <print>
#include <string>
#include <string_view>
#include <vector>
#include <cmath>

#include "BigInt.h"

// private methods:

void BigInt::_reserve_optimization(std::vector<int>& vec, const std::vector<size_t>& sizes) {
    vec.reserve(std::max(*(std::max_element(sizes.begin(), sizes.end())), _reserve_value));
}

void BigInt::_reserve_optimization(const std::vector<size_t>& sizes) {
    _reserve_optimization(_num, sizes);
}

void BigInt::_reserve_optimization() {
    _num.reserve(std::max(size(), _reserve_value));
}

void BigInt::_delete_leading_zeros(std::vector<int>& vec) {
    while (vec.size() > 1 && vec.back() == 0) {
        vec.pop_back();
    }
}

void BigInt::_delete_leading_zeros() {
    _delete_leading_zeros(_num);
}

void BigInt::_init() {
    if (_num.empty()) {
        _num.push_back(0);
    }
    _delete_leading_zeros();
    if (size() == 1 && _num[0] == 0) {
        _sign = 0;
    }
    _reserve_optimization();
}

// Constructors and Destructor here:

BigInt::BigInt() : _num{ {0} }, _sign{ 0 } {};

BigInt::BigInt(const BigInt& other) : _num{ other._num }, _sign{ other.sign() } {
    _init();
}

BigInt::BigInt(BigInt&& other) noexcept : _num{ std::move(other._num) }, _sign{ other.sign() } {
    _init();
}

BigInt::BigInt(const std::vector<int>& vec, int sign = 0) : _num{ vec }, _sign{ sign } {
    bool flag = true;
    for (const auto& n : _num) {
        if (n != 0) {
            flag = false;
            break;
        }
    }
    if (flag) {
        _sign = 0;
    }
    if (abs(_sign) > 1) {
        _sign /= abs(_sign);
    }
    _init();
}

BigInt::BigInt(std::vector<int>&& vec, int sign = 0) noexcept : _num{ std::move(vec) }, _sign{ sign } {
    bool flag = true;
    for (const auto& n : _num) {
        if (n != 0) {
            flag = false;
            break;
        }
    }
    if (flag) {
        _sign = 0;
    }
    if (abs(_sign) > 1) {
        _sign /= abs(_sign);
    }
    _init();
}

BigInt::BigInt(std::integral auto number) {
    if (number == 0) {
        _num.push_back(0);
    }
    else if (number > 0) {
        _sign = 1;
    }
    else {
        _sign = -1;
    }
    number = std::abs(number);
    while (number != 0) {
        _num.push_back(number % _base);
        number /= _base;
    }
    _init();
}

BigInt::~BigInt() = default;

// bunch of methods here

int BigInt::sign() const {
    return _sign;
}

size_t BigInt::size() const { return _num.size(); }

std::string BigInt::to_string() const {
    std::string res{ sign() == -1 ? "-" : "" };
    bool first = true;
    for (auto it = _num.rbegin(); it != _num.rend(); ++it) {
        std::string part{};
        if (first) {
            part = std::format("{}", *it);
            first = false;
        }
        else {
            part = std::format(format_str, *it);
        }
        res += part;
    }
    return res;
}

void BigInt::print_inner_representation() const {
    if (_sign == 1) {
        std::cout << "+ ";
    }
    else if (_sign == -1) {
        std::cout << "- ";
    }
    std::cout << "{ ";

    bool first = true;
    for (const auto& n : _num) {
        if (!first) {
            std::cout << ", ";
        }
        else {
            first = false;
        }
        std::cout << n;
    }
    std::cout << " }\n";
}

void BigInt::print() const { std::print("{}", this->to_string()); }

void BigInt::println() const { std::println("{}", this->to_string()); }
// bunch of operators here:

BigInt& BigInt::operator=(const BigInt& other) {
    _num = other._num;
    _sign = other.sign();
    _init();
    return *this;
}

BigInt& BigInt::operator=(BigInt&& other) noexcept {
    _num = std::move(other._num);
    _sign = other.sign();
    _init();
    return *this;
}

bool operator==(const BigInt& N1, const BigInt& N2) {
    return (N1._num == N2._num) && (N1.sign() == N2.sign());
}

bool operator!=(const BigInt& N1, const BigInt& N2) {
    return !(N1 == N2);
}

bool operator<(const BigInt& N1, const BigInt& N2) {
    if (N1.sign() != N2.sign()) {
        return N1.sign() < N2.sign();
    }
    if (N1.size() != N2.size()) {
        return N1.size() < N2.size();
    }
    for (auto it1 = N1._num.rbegin(), it2 = N2._num.rbegin();
        it1 != N1._num.rend(); it1++, it2++) {
        if (*it1 != *it2) {
            if (N1.sign() == 1) {
                return *it1 < *it2;
            }
            else {
                return *it1 > *it2;
            }
        }
    }
    return false;
}

bool operator>(const BigInt& N1, const BigInt& N2) {
    return N2 < N1;
}

bool operator<=(const BigInt& N1, const BigInt& N2) {
    return (N1 < N2) || (N1 == N2);
}

bool operator>=(const BigInt& N1, const BigInt& N2) {
    return N2 <= N1;
}

BigInt operator+(const BigInt& N) {
    return BigInt(N);
}

BigInt operator-(const BigInt& N) {
    return BigInt(N._num, -N.sign());
}

BigInt operator+(const BigInt& N1, const BigInt& N2) {
    if (N1.sign() * N2.sign() == -1) {
        return operator-(N1, -N2);
    }

    std::vector<int> res;
    size_t N1_size = N1.size(), N2_size = N2.size(), res_size = std::max(N1_size, N2_size),
        res_reserve_value = std::max(BigInt::_reserve_value, res_size + 1);
    res.reserve(res_reserve_value);

    int sum{}, carry{}, sign{ N1.sign() ? N1.sign() : N2.sign() };

    for (size_t i = 0; i < res_size || carry; ++i) {
        sum = carry;
        if (i < N1_size) {
            sum += N1._num[i];
        }
        if (i < N2_size) {
            sum += N2._num[i];
        }
        res.push_back(sum % BigInt::_base);
        carry = sum / BigInt::_base;
    }

    if (carry) {
        res.push_back(carry);
    }


    return BigInt(std::move(res), sign);
}

BigInt operator-(const BigInt& N1, const BigInt& N2) {
    if (N1.sign() * N2.sign() == -1) {
        return N1 + (-N2);
    }
    if (std::abs(N1) == std::abs(N2)) {
        return BigInt(0);
    }

    bool abs_cmp = std::abs(N1) < std::abs(N2);
    const BigInt& larger = abs_cmp ? N2 : N1, & smaller = abs_cmp ? N1 : N2;

    std::vector<int> res;
    size_t larger_size = larger.size(), smaller_size = smaller.size(), res_size = larger_size, res_reserve_value = res_size;
    res.reserve(res_reserve_value);

    int diff{}, borrow{}, sign = abs_cmp ? -larger.sign() : larger.sign();

    for (size_t i = 0; i < res_size; ++i) {
        diff = -borrow;
        borrow = 0;
        if (i < larger_size) {
            diff += larger._num[i];
        }
        if (i < smaller_size) {
            diff -= smaller._num[i];
        }
        if (diff < 0) {
            borrow = 1;
            diff += BigInt::_base;
        }
        res.push_back(diff);
    }
    return BigInt(res, sign);
}

// to be added: operators(*, /, %, ++, --), methods: to_string(), constructors: BigInt(std::string number), pow(BigInt N, int n), pow_mod(BigInt N, int n, BigInt mod)

// other functions:

namespace std {

    const BigInt abs(const BigInt& N) {
        if (N.sign() > 0) {
            return +N;
        }
        else {
            return -N;
        }
    }

    std::string to_string(const BigInt& N) {
        return N.to_string();
    }
}



int main() {
    BigInt N{ 10000000 }, M{ -20 }, K{};
    K.print_inner_representation();
    K = N + M;
    K.print_inner_representation();
    K.println();
    std::println("{}", N != M);
    K = -N - (M - M);
    K.print_inner_representation();
    K.println();
    return 0;
}
