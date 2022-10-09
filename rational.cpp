#include "rational.h"

// ================================== CONSTRUCTORS ===================================

rational_number::rational_number () : num(0), denom(0) {}

rational_number::rational_number (const bignum& num, const bignum& denom) : num(num), denom(denom) {}

rational_number::rational_number (const bignum& num) : num(num), denom(1) {}

rational_number::rational_number (const signed& num, const unsigned& denom) : num(num), denom(denom) {}

rational_number::rational_number (const signed long long& num, const unsigned long long& denom) : num(num), denom(denom) {}

rational_number::rational_number (const long long int& num) : num(num), denom(1) {}

rational_number::rational_number (const long int& num) : num(num), denom(1) {}

rational_number::rational_number (const int& num) : num(num), denom(1) {}

rational_number::rational_number (const std::string& num, const std::string& denom) : num(num), denom(denom) {}

rational_number::rational_number (const std::string& num) {
    auto number = num;
    if (number.empty()) {
        throw;
    }
    // bool isNeg = number[0] == '-';
    // if (number[0] == '+' || number[0] == '-') {
    //     number.erase(0, 1);
    // }
    auto dot_pos = number.find('.'), slash_pos = number.find('/');
    if (slash_pos == std::string::npos) {
        if (dot_pos == std::string::npos) {
            set_Numerator(number);
            set_Denominator(1);
        } else {
            auto power = number.substr(dot_pos).size() - 1;
            number.erase(dot_pos, 1);
            set_Numerator(number);
            std::string tmp = "1";
            for (long unsigned int i = 0; i < power; ++i) {
                tmp += "0";
            }
            set_Denominator(tmp);
        }
    } else {
        std::string sign = number[0] == '-' ? "-" : "";
        if (number[0] == '-' || number[0] == '+') {
            number.erase(0, 1);
        }
        slash_pos = number.find('/');
        if (slash_pos + 1 < number.length()) {
            auto denom_tmp = number.substr(slash_pos+1);
            if (denom_tmp[0] == '-') {
                sign = sign == "-" ? "" : "-";
                denom_tmp = denom_tmp.erase(0, 1);
            } else if (denom_tmp[0] == '+') {
                denom_tmp = denom_tmp.erase(0, 1);
            }
            set_Denominator(denom_tmp);
        }
        set_Numerator(sign + number.substr(0, slash_pos));
    }
    if (num == "0") {
        set_Denominator (1);
    }
}

rational_number::rational_number (const long double& num){
    rational_number res = rational_number(std::to_string(num));
    set_Numerator(res.num);
    set_Denominator(res.denom);
}

rational_number::rational_number (const double& num){
    rational_number res = rational_number(std::to_string(num));
    set_Numerator(res.num);
    set_Denominator(res.denom);
}

rational_number::rational_number (const float& num){
    rational_number res = rational_number(std::to_string(num));
    set_Numerator(res.num);
    set_Denominator(res.denom);
}

// ================================== GETTERS ===================================

bignum rational_number::get_Numerator () {
    return this->num;
}

bignum rational_number::get_Denominator () {
    return this->denom;
}

// ================================== SETTERS ===================================

void rational_number::set_Numerator (const bignum& new_num) {
    num = new_num;
}

void rational_number::set_Denominator (const bignum& new_denom) {
    if (new_denom == 0){
        throw;
    } else if (new_denom.get_sign()) {
        throw;
    } else {
        denom = new_denom;
    }
}

// ================================== COPY OPERATORS ===================================

rational_number& rational_number::operator= (const rational_number& number) {
    this->num = number.num;
    this->denom = number.denom;
    return *this;
}

rational_number& rational_number::operator= (const long long& num) {
    rational_number res(num);
    *this = res;
    return *this;
}

rational_number& rational_number::operator= (const long int& num) {
    rational_number res(num);
    *this = res;
    return *this;
}

rational_number& rational_number::operator= (const int& num) {
    rational_number res(num);
    *this = res;
    return *this;
}

rational_number& rational_number::operator= (const long double& num) {
    rational_number res(num);
    *this = res;
    return *this;
}

rational_number& rational_number::operator= (const double& num) {
    rational_number res(num);
    *this = res;
    return *this;
}

rational_number& rational_number::operator= (const float& num) {
    rational_number res(num);
    *this = res;
    return *this;
}

rational_number& rational_number::operator= (const std::string& num) {
    rational_number res(num);
    *this = res;
    return *this;
}

// ================================== STREAMS ===================================

std::ostream& operator << (std::ostream& os, const rational_number& bn) {
    os << to_string(bn);
    return os;
}

std::istream& operator >> (std::istream& is, rational_number& bn) {
    std::string tmp;
    is >> tmp;
    bn = rational_number(tmp);
    return is;
}

// ================================== COMPARATORS ===================================

bool operator== (const rational_number& lhs, const rational_number& rhs) {
    rational_number simplified_lhs = lhs, simplified_rhs = rhs;
    simplified_lhs.make_canonical();
    simplified_rhs.make_canonical();
    return simplified_lhs.num == simplified_rhs.num && simplified_lhs.denom == simplified_rhs.denom;
}

bool operator!= (const rational_number& lhs, const rational_number& rhs) {
    return !(lhs == rhs);
}

bool operator< (const rational_number& lhs, const rational_number& rhs) {
    return lhs.num * rhs.denom < lhs.denom * rhs.num;
}

bool operator> (const rational_number& lhs, const rational_number& rhs) {
    return rhs < lhs;
}

bool operator<= (const rational_number& lhs, const rational_number& rhs) {
    return !(lhs > rhs);
}

bool operator>= (const rational_number& lhs, const rational_number& rhs) {
    return !(lhs < rhs);
}

// ================================== BOOLEAN OPERATORS ===================================

bool rational_number::operator! () {
    return !(operator bool());
}

// ================================== CASTS ===================================

rational_number::operator bool () {
    return num == 0;
}

rational_number::operator char () const {
    return (char) cast_to_integer("char", CHAR_MIN, CHAR_MAX);
}

rational_number::operator short () const {
    return (short) cast_to_integer("short", SHRT_MIN, SHRT_MAX);
}

rational_number::operator int () const {
    return (int) cast_to_integer("int", INT_MIN, INT_MAX);
}

rational_number::operator long int () const {
    return (long int) cast_to_integer("long int", LONG_MIN, LONG_MAX);
}

rational_number::operator long long () const {
    return (long long) cast_to_integer("long long", LONG_LONG_MIN + 5, LLONG_MAX);
}

rational_number::operator long double () const {
    return (int) cast_to_floating("long double", LDBL_MIN, LDBL_MAX);
}

rational_number::operator double () const {
    return (int) cast_to_floating("double", DBL_MIN, DBL_MAX);
}

rational_number::operator float () const {
    return (int) cast_to_floating("float", FLT_MIN, FLT_MAX);
}

// ================================== ASSIGNING BINARY OPERATORS ===================================

rational_number& rational_number::operator+= (const rational_number& value) {
    bignum greatest_common_divider = gcd(num, value.denom);
    bignum left_multiplier = value.denom / greatest_common_divider;
    bignum right_multiplier = denom / greatest_common_divider;
    bignum left_num = num * left_multiplier;
    bignum right_num = value.num * right_multiplier;
    num = left_num + right_num;
    denom *= left_multiplier;
    make_canonical ();
    return *this;
}

rational_number& rational_number::operator-= (const rational_number& value) {
    bignum greatest_common_divider = gcd(num, value.denom);
    bignum left_multiplier = value.denom / greatest_common_divider;
    bignum right_multiplier = denom / greatest_common_divider;
    bignum left_num = num * left_multiplier;
    bignum right_num = value.num * right_multiplier;
    num = left_num - right_num;
    denom *= left_multiplier;
    make_canonical ();
    return *this;
}

rational_number& rational_number::operator*= (const rational_number& value) {
    num *= value.num;
    denom *= value.denom;
    make_canonical ();
    return *this;
}

rational_number& rational_number::operator/= (const rational_number& value) {
    if (value.num == 0) {
        throw;
    }
    num.set_sign(num.get_sign() != value.num.get_sign());
    num *= value.denom;
    denom *= value.num;
    make_canonical ();
    return *this;
}

// ================================== UNARY ===================================

rational_number rational_number::operator- () const {
    rational_number tmp({!num.get_sign(), num.get_val()}, denom);
    // tmp.num.set_sign(!tmp.num.get_sign());
    return tmp;
}

rational_number& rational_number::operator++ () {
    *this += 1;
    return *this;
}

rational_number& rational_number::operator-- () {
    *this -= 1;
    return *this;
}

rational_number rational_number::operator++ (int) {
    rational_number tmp(*this);
    *this += 1;
    return tmp;
}

rational_number rational_number::operator-- (int) {
    rational_number tmp(*this);
    *this -= 1;
    return tmp;
}

// ================================== ASSIGNING BINARY OPERATORS ===================================

rational_number operator+ (rational_number lhs, const rational_number& rhs) {
    return lhs += rhs;
}

rational_number operator- (rational_number lhs, const rational_number& rhs) {
    return lhs -= rhs;
}

rational_number operator* (rational_number lhs, const rational_number& rhs) {
    return lhs *= rhs;
}

rational_number operator/ (rational_number lhs, const rational_number& rhs) {
    return lhs /= rhs;
}

// ================================== UTILITY METHODS ===================================

std::string to_string (const rational_number& bn) {
    return to_string(bn.num) + "/" + to_string(bn.denom);
}

rational_number& rational_number::make_canonical () {
    if (num == 0) {
        num.set_sign(false);
        denom = 1;
    } else {
        bignum greatest_common_divider = gcd(num, denom);
        num /= greatest_common_divider;
        denom /= greatest_common_divider;
    }
    return *this;
}

bignum rational_number::floor () const {
    return num / denom;
}

bignum rational_number::round () const {
    rational_number tmp = num / denom, buf(*this);
    bignum res = num / denom;
    if (buf - tmp >= rational_number(0.5)) {
        res += 1;
    }
    return res;
}

// ================================== PRIVATE METHODS ===================================

bignum rational_number::cast_to_integer (const std::string& type_name, const bignum& min, const bignum& max) const{
    if (rational_number(min) > *this || rational_number(max) < *this) {
        throw;
    }
    auto res = num / denom;
    if (*this != res * denom) {
        throw;
    }
    return res;
}

long double rational_number::cast_to_floating (const std::string& type_name, const long double& min, const long double& max) const{
    // std::cout<<min<<std::endl;
    // std::cout<<rational_number(min)<<std::endl;
    if (rational_number(min) > *this || rational_number(max) < *this) {
        throw;
    }
    // rational_number int_num = *this;
    // bignum power = 1;
    // for (int i = 0; i < LDBL_DECIMAL_DIG; ++i) {
    //     int_num *= 10;
    //     power *= 10;
    // }
    // bignum 
    return (long double) (num) / (long double) (denom);
}