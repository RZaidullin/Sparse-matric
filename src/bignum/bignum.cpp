#include "bignum.h"

// ================================== CONSTRUCTORS ===================================

bignum::bignum (): isNegative(false), val(std::to_string(0)) {}

bignum::bignum (const bignum& BN): isNegative(BN.isNegative), val(BN.val) {}

bignum::bignum (bool isNeg, std::string value): isNegative(isNeg), val(value) {}

bignum::bignum (const std::string& number) {
    isNegative = number[0] == '-';
    val = isNegative ? number.substr(1, number.size()) : number;
}

bignum::bignum (const long long& number): isNegative(number < 0), val(std::to_string(llabs(number))) {}

bignum::bignum (const long int& number): isNegative(number < 0), val(std::to_string(llabs(number))) {}

bignum::bignum (const int& number): isNegative(number < 0), val(std::to_string(labs(number))) {}

bignum::bignum (const unsigned& number): isNegative(false), val(std::to_string(number)) {}

bignum::bignum (const unsigned long int& number): isNegative(false), val(std::to_string(number)) {}

bignum::bignum (const unsigned long long& number): isNegative(false), val(std::to_string(number)) {}

// ================================== COPY OPERATORS ===================================

bignum& bignum::operator= (const bignum& number) {
    val = number.val;
    isNegative = number.isNegative;
    return *this;
}

bignum& bignum::operator= (const std::string& number) {
    bignum res(number);
    *this = res;
    return *this;
}

bignum& bignum::operator= (const long long& number) {
    bignum res(number);
    *this = res;
    return *this;
}

bignum& bignum::operator= (const long int& number) {
    bignum res(number);
    *this = res;
    return *this;
}

bignum& bignum::operator= (const int& number) {
    bignum res(number);
    *this = res;
    return *this;
}

bignum& bignum::operator= (const unsigned& number) {
    bignum res(number);
    *this = res;
    return *this;
}

bignum& bignum::operator= (const unsigned long int& number) {
    bignum res(number);
    *this = res;
    return *this;
}

bignum& bignum::operator= (const unsigned long long& number) {
    bignum res(number);
    *this = res;
    return *this;
}

// ================================== SETTERS ===================================

void bignum::set_sign (bool isNeg) {
    isNegative = isNeg;
}

void bignum::set_val (std::string value) {
    val = value;
}

// ================================== GETTERS ===================================

bool bignum::get_sign () const{
    return isNegative;
}

std::string bignum::get_val () const{
    return val;
}

// ================================== ASSIGNING BINARY OPERATORS ===================================

bignum& bignum::operator+= (const bignum& value) {
    cmp_res abs_cmp_res = compare_values(val, value.val);
    if (isNegative == value.isNegative) {
        val = plus(val, value.val);
    } else {
        val = minus(val, value.val);
        if (abs_cmp_res == cmp_res::LESSER){
            isNegative = value.isNegative;
        }
    }
    remove_leading_zeros ();
    return *this;
}

bignum& bignum::operator-= (const bignum& value) {
    cmp_res abs_cmp_res = compare_values(val, value.val);
    if (isNegative != value.isNegative) {
        val = plus(val, value.val);
    } else {
        val = minus(val, value.val);
        if (abs_cmp_res == cmp_res::LESSER) {
            isNegative = value.isNegative;
        }
    }
    remove_leading_zeros ();
    return *this;
}

bignum& bignum::operator*= (const bignum& value) {
    val = multiply(val, value.val);
    isNegative = isNegative != value.isNegative;
    remove_leading_zeros ();
    return *this;
}

bignum& bignum::operator/= (const bignum& value) {
    if (value.val == "0") {
        throw;
    }
    std::string tmp = val;
    val = divide(val, value.val);
    isNegative = isNegative != value.isNegative;
    if (isNegative) {
        if (tmp != multiply(val, value.val)){
            val = plus(val, "1");
        }
    }
    remove_leading_zeros ();
    return *this;
}

// ================================== UNARY ===================================

bignum bignum::operator- () const {
    bignum tmp(this->isNegative ? false : true, this->val);
    return tmp;
}

bignum& bignum::operator++ () {
    *this += 1;
    return *this;
}

bignum& bignum::operator-- () {
    *this -= 1;
    return *this;
}

bignum bignum::operator++ (int) {
    bignum tmp(*this);
    *this += 1;
    return tmp;
}

bignum bignum::operator-- (int) {
    bignum tmp(*this);
    *this -= 1;
    return tmp;
}

// ================================== STREAMS ===================================

std::ostream& operator << (std::ostream& os, const bignum& bn) {
    os << to_string(bn);
    return os;
}

std::istream& operator >> (std::istream& is, bignum& bn) {
    std::string tmp;
    is >> tmp;
    bn = bignum(tmp);
    return is;
}

// ================================== COMPARATORS ===================================

bool operator== (const bignum& lhs, const bignum& rhs) {
    return lhs.val == rhs.val && (lhs.val == "0" || lhs.isNegative == rhs.isNegative);
}

bool operator!= (const bignum& lhs, const bignum& rhs) {
    return !(lhs == rhs);
}

bool operator< (const bignum& lhs, const bignum& rhs) {
    if (lhs.isNegative && !rhs.isNegative) {
        return true;
    } else if (!lhs.isNegative && rhs.isNegative) {
        return false;
    }
    bignum::cmp_res abs_cmp_res = bignum::compare_values(lhs.val, rhs.val);
    if ( (!lhs.isNegative && !rhs.isNegative && abs_cmp_res == bignum::cmp_res::LESSER) ||
         (lhs.isNegative && rhs.isNegative && abs_cmp_res == bignum::cmp_res::GREATER) ) {
            return true;
    }
    return false;
}

bool operator> (const bignum& lhs, const bignum& rhs) {
    return rhs < lhs;
}

bool operator<= (const bignum& lhs, const bignum& rhs) {
    return !(lhs > rhs);
}

bool operator>= (const bignum& lhs, const bignum& rhs) {
    return !(lhs < rhs);
}

// ================================== BOOLEAN OPERATORS ===================================

bool bignum::operator! () {
    return !(operator bool());
}

// ================================== CASTS ===================================

bignum::operator bool () {
    return val != "0";
}

bignum::operator char () {
    return (char) downcast("char", CHAR_MIN, CHAR_MAX);
}

bignum::operator short () {
    return (short) downcast("short", SHRT_MIN, SHRT_MAX);
}

bignum::operator int () {
    return (int) downcast("int", INT_MIN, INT_MAX);
}

bignum::operator long int () {
    return (long int) downcast("long int", LONG_MIN, LONG_MAX);
}

bignum::operator long long () const {
    return (long long) downcast("long long", LLONG_MIN, LLONG_MAX);
}

bignum::operator long double () const {
    if (static_cast<long long>(LDBL_MIN) > *this || *this > static_cast<long long>(LDBL_MAX)) {
        throw;
    }
    return (long double) ((long long) (*this));
}

long long bignum::downcast (const std::string& type_name, long long min, long long max) const{
    if (*this < min || *this > max) {
        throw;
    }
    long long res = 0;
    for (char digit: val) {
        res = res * 10 + digit - '0';
    }
    return res * (isNegative ? -1 : 1);
}

// ================================== BINARY ===================================

bignum operator+ (bignum lhs, const bignum& rhs) {
    return (lhs += rhs);
}

bignum operator- (bignum lhs, const bignum& rhs) {
    return (lhs -= rhs);
}

bignum operator* (bignum lhs, const bignum& rhs) {
    return (lhs *= rhs);
}

bignum operator/ (bignum lhs, const bignum& rhs) {
    return (lhs /= rhs);
}

bignum operator% (bignum lhs, const bignum& rhs) {
    if (lhs.isNegative == rhs.isNegative) {
        return lhs - rhs * (lhs / rhs);
    }
    return -1 * (rhs * (lhs / rhs) - lhs);
}

// ================================== PRIVATE METHODS ===================================

void bignum::remove_leading_zeros () {
    while (val.length() > 1 && val[0] == '0') {
        val.erase(0, 1);
    }
}

void bignum::remove_leading_zeros (std::string& num) {
    while (num.length() > 1 && num[0] == '0') {
        num.erase(0, 1);
    }
}

bignum::cmp_res bignum::compare_values (const std::string& lhs, const std::string& rhs) {
    if (lhs.empty() || rhs.empty()) {
        throw;
    }
    if (lhs.length() < rhs.length()) {
        return cmp_res::LESSER;
    } else if (lhs.length() > rhs.length()) {
        return cmp_res::GREATER;
    }
    for (long unsigned i = 0; i < lhs.length(); ++i){
        if (lhs[i] > rhs[i]){
            return cmp_res::GREATER;
        } else if (lhs[i] < rhs[i]){
            return cmp_res::LESSER;
        } 
    }
    return cmp_res::EQUAL;
}

char bignum::plus (char lhs, char rhs, int& overflow) {
    auto tmp = (lhs - '0') + (rhs - '0') + overflow;
    overflow = tmp / 10;
    return char(tmp % 10 + '0');
}

char bignum::minus (char lhs, char rhs, int& underflow) {
    auto tmp = (lhs - '0') - (rhs - '0') - underflow;
    if (tmp >= 0) {
        underflow = 0;
    } else {
        underflow = 1;
    }
    return char((10 + tmp) % 10 + '0');
}

char bignum::multiply (char lhs, char rhs, int& overflow) {
    auto tmp = (lhs - '0') * (rhs - '0') + overflow;
    overflow = tmp / 10;
    return char(tmp % 10 + '0');
}

std::string bignum::plus (const std::string& lhs, const std::string& rhs) {
    std::string res;
    auto max_length = std::max(lhs.length(), rhs.length());
    int overflow = 0;
    char dig1, dig2, dig3;
    for (long unsigned i = 0; i < max_length; ++i) {
        if (lhs.length() > i){
            dig1 = lhs[lhs.length() - i - 1];
        } else {
            dig1 = '0';
        }
        if (rhs.length() > i){
            dig2 = rhs[rhs.length() - i - 1];
        } else {
            dig2 = '0';
        }
        dig3 = plus(dig1, dig2, overflow);
        res = std::string(1, dig3).append(res);
    }
    if (overflow != 0) {
        res = std::string(1, char(overflow + '0')).append(res);
    }
    remove_leading_zeros(res);
    return res;
}

std::string bignum::minus (std::string lhs, std::string rhs) {
    if (lhs == rhs) {
        return "0";
    }
    std::string res;
    cmp_res tmp = compare_values(lhs, rhs);
    if (tmp == cmp_res::LESSER) {
        std::swap(lhs, rhs);
    }
    int underflow = 0;
    char dig1, dig2, dig3;
    for (long unsigned i = 0; i < lhs.length(); ++i){
        dig1 = lhs[lhs.length() - i - 1];
        if (rhs.length() > i){
            dig2 = rhs[rhs.length() - i - 1];
        } else {
            dig2 = '0';
        }
        dig3 = minus(dig1, dig2, underflow);
        res = std::string(1, dig3).append(res);
    }
    remove_leading_zeros(res);
    return res;
}

std::string bignum::multiply (std::string lhs, char multiplier) {
    if(lhs == "0" || multiplier == '0'){
        return "0";
    }
    std::string res;
    int overflow = 0;
    char dig;
    for (long unsigned i = 0; i < lhs.length(); ++i) {
        dig = multiply(lhs[lhs.length() - i - 1], multiplier, overflow);
        res = std::string(1, dig).append(res);
    }
    if (overflow != 0) {
        res = std::string(1, char(overflow + '0')).append(res);
    }
    remove_leading_zeros(res);
    return res;
}

std::string bignum::multiply (std::string lhs, std::string rhs) {
    if (lhs == "0" || rhs == "0") {
        return "0";
    }
    std::string shifting_zeros, res = "0", tmp;
    for (long unsigned i = 0; i < rhs.length(); ++i) {
        tmp = multiply(lhs, rhs[rhs.length() - i - 1]) + shifting_zeros;
        shifting_zeros += "0";
        res = plus(res, tmp);
    }
    remove_leading_zeros(res);
    return res;
}

std::string bignum::divide (std::string lhs, std::string rhs) {
    if (compare_values(lhs, rhs) == cmp_res::LESSER) return "0";
    std::string res, current = "", nearest_dividend;
    for (long unsigned int i = 0; i < lhs.size(); ++i) {
        current += lhs[i];
        if (compare_values(current, rhs) == cmp_res::LESSER) {
            res += "0";
            while (current[0] == '0') {
                current.erase(0,1);
            }
            continue;
        }
        nearest_dividend = rhs;
        for (int j = 1; j < 10; j++) {
            nearest_dividend = plus(nearest_dividend, rhs);
            if(compare_values(current, nearest_dividend) == cmp_res::LESSER) {
                res += std::to_string(j);
                break;
            }
        }
        nearest_dividend = minus(nearest_dividend, rhs);
        current = minus(current, nearest_dividend);
        while (current[0] == '0') {
            current.erase(0,1);
        }
    }
    while (res[0] == '0') {
       res.erase(0,1);
    }
    return res;
}


// ================================== UTILITY METHODS ===================================

std::string to_string (const bignum& bn) {
    return (bn.isNegative ? "-" : "") + bn.val;
}

bignum gcd (bignum lhs, bignum rhs) {
    lhs.isNegative = false;
    rhs.isNegative = false;
    while (lhs.val != "0" && rhs.val != "0") {
        if (bignum::compare_values(lhs.val, rhs.val) == bignum::cmp_res::LESSER) {
            std::swap(lhs, rhs);
        }
        lhs -= rhs;
    }
    if (lhs.val == "0"){
        return {false, rhs.val};
    }
    return {false, lhs.val};
}