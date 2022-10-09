#ifndef _bignum_H_
#define _bignum_H_

#include <string>
#include <cmath>
#include <climits>
#include <cfloat>
#include <iostream>

class bignum {
private:

    bool isNegative;

    std::string val;

    enum class cmp_res {
        
        LESSER = -1,

        EQUAL = 0,

        GREATER = 1,

    };

    static cmp_res compare_values (const std::string& lhs, const std::string& rhs);

    char plus (char lhs, char rhs, int& overflow);

    char minus (char lhs, char rhs, int& underflow);

    char multiply (char lhs, char rhs, int& overflow);

    std::string plus (const std::string& lhs, const std::string& rhs);

    std::string minus (std::string lhs, std::string rhs);

    std::string multiply (std::string lhs, char multiplier);

    std::string multiply (std::string lhs, std::string rhs);

    std::string divide (std::string lhs, std::string rhs);

    void remove_leading_zeros ();

    void remove_leading_zeros (std::string& val);

    long long downcast (const std::string& type_name, long long min, long long max) const;

public:
    bignum ();

    bignum (const bignum& BN);

    bignum (bool isNeg, std::string value);

    bignum (const std::string& number);

    bignum (const long long& number);

    bignum (const long int& number);

    bignum (const int& number);

    bignum (const unsigned& number);

    bignum (const unsigned long int& number);

    bignum (const unsigned long long& number);

    bignum& operator= (const bignum& number);

    bignum& operator= (const std::string& number);

    bignum& operator= (const long long& number);

    bignum& operator= (const long int& number);

    bignum& operator= (const int& number);

    bignum& operator= (const unsigned& number);

    bignum& operator= (const unsigned long int& number);

    bignum& operator= (const unsigned long long& number);

    void set_sign (bool isNeg);

    void set_val (std::string value);

    bool get_sign () const;

    std::string get_val () const;

    friend std::ostream& operator << (std::ostream& os, const bignum& bn);

    friend std::istream& operator >> (std::istream& is, bignum& bn);

    friend bool operator== (const bignum& lhs, const bignum& rhs);

    friend bool operator<= (const bignum& lhs, const bignum& rhs);

    friend bool operator>= (const bignum& lhs, const bignum& rhs);

    friend bool operator!= (const bignum& lhs, const bignum& rhs);

    friend bool operator> (const bignum& lhs, const bignum& rhs);

    friend bool operator< (const bignum& lhs, const bignum& rhs);

    bool operator! ();

    bignum& operator+= (const bignum& value);

    bignum& operator-= (const bignum& value);

    bignum& operator*= (const bignum& value);

    bignum& operator/= (const bignum& value);

    bignum operator- () const;

    bignum& operator++ ();

    bignum& operator-- ();

    bignum operator++ (int);

    bignum operator-- (int);

    explicit operator bool ();

    explicit operator char ();

    explicit operator short ();

    explicit operator int ();

    explicit operator long int ();

    explicit operator long long () const;

    explicit operator long double () const;

    friend bignum operator+ (bignum lhs, const bignum& rhs);

    friend bignum operator- (bignum lhs, const bignum& rhs);

    friend bignum operator* (bignum lhs, const bignum& rhs);

    friend bignum operator/ (bignum lhs, const bignum& rhs);

    friend bignum operator% (bignum lhs, const bignum& rhs);

    // ====== USEFUL METHODS ======

    friend std::string to_string (const bignum& bn);

    friend bignum gcd(bignum lhs, bignum rhs);

};

std::string to_string (const bignum& bn);

bignum gcd(bignum lhs, bignum rhs);

bignum operator+ (bignum lhs, const bignum& rhs);

bignum operator- (bignum lhs, const bignum& rhs);

bignum operator* (bignum lhs, const bignum& rhs);

bignum operator/ (bignum lhs, const bignum& rhs);

bignum operator% (bignum lhs, const bignum& rhs);

std::ostream& operator << (std::ostream& os, const bignum& bn);

std::istream& operator >> (std::istream& is, bignum& bn);

#endif