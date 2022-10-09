#ifndef _rational_H_
#define _rational_H_

#include <string>
#include <cmath>
#include <climits>
#include <cfloat>
#include <iostream>

#include "bignum.h"

class rational_number {
private: 
    bignum num;      // числитель

    bignum denom;    // знаменатель

    bignum cast_to_integer (const std::string& type_name, const bignum& min, const bignum& max) const;

    long double cast_to_floating (const std::string& type_name, const long double& min, const long double& max) const;

public:
    rational_number ();

    rational_number (const bignum& num, const bignum& denom);

    rational_number (const bignum& num);

    rational_number (const signed& num, const unsigned& denom);

    rational_number (const signed long long& num, const unsigned long long& denom);

    rational_number (const std::string& num, const std::string& denom);

    rational_number (const std::string& num);

    rational_number (const int& num);

    rational_number (const long int& num);

    rational_number (const long long int& num);

    rational_number (const long double& num);

    rational_number (const double& num);

    rational_number (const float& num);

    //@return string
    bignum get_Numerator ();

    //@return string
    bignum get_Denominator ();

    void set_Numerator (const bignum& new_num);

    void set_Denominator (const bignum& new_denom);

    rational_number& operator= (const rational_number& number);

    rational_number& operator= (const long long& num);

    rational_number& operator= (const long int& num);

    rational_number& operator= (const int& num);

    rational_number& operator= (const long double& num);

    rational_number& operator= (const double& num);

    rational_number& operator= (const float& num);

    rational_number& operator= (const std::string& num);

    friend std::ostream& operator << (std::ostream& os, const rational_number& bn);

    friend std::istream& operator >> (std::istream& is, rational_number& bn);

    friend bool operator== (const rational_number& lhs, const rational_number& rhs);

    friend bool operator<= (const rational_number& lhs, const rational_number& rhs);

    friend bool operator>= (const rational_number& lhs, const rational_number& rhs);

    friend bool operator!= (const rational_number& lhs, const rational_number& rhs);

    friend bool operator> (const rational_number& lhs, const rational_number& rhs);

    friend bool operator< (const rational_number& lhs, const rational_number& rhs);

    bool operator! ();

    rational_number& operator+= (const rational_number& value);

    rational_number& operator-= (const rational_number& value);

    rational_number& operator*= (const rational_number& value);

    rational_number& operator/= (const rational_number& value);

    rational_number operator- () const;

    rational_number& operator++ ();

    rational_number& operator-- ();

    rational_number operator++ (int);

    rational_number operator-- (int);

    explicit operator bool ();

    explicit operator char () const;

    explicit operator short () const;

    explicit operator int () const;

    explicit operator long int () const;

    explicit operator long long () const;

    explicit operator long double () const;

    explicit operator double () const;

    explicit operator float () const;

    friend rational_number operator+ (rational_number lhs, const rational_number& rhs);

    friend rational_number operator- (rational_number lhs, const rational_number& rhs);

    friend rational_number operator* (rational_number lhs, const rational_number& rhs);

    friend rational_number operator/ (rational_number lhs, const rational_number& rhs);

    // ====== USEFUL METHODS ======

    friend std::string to_string (const rational_number& bn);

    bignum floor () const;

    bignum round () const;

    rational_number& make_canonical ();
};

std::string to_string (const rational_number& bn);

rational_number operator+ (rational_number lhs, const rational_number& rhs);

rational_number operator- (rational_number lhs, const rational_number& rhs);

rational_number operator* (rational_number lhs, const rational_number& rhs);

rational_number operator/ (rational_number lhs, const rational_number& rhs);

std::ostream& operator << (std::ostream& os, const rational_number& bn);

std::istream& operator >> (std::istream& is, rational_number& bn);

#endif