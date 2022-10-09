#include <iostream>
#include <climits>
#include <cfloat>
#include "rational/rational.h"
#include "bignum/bignum.h"

// divide должен бы по-хорошему пару выдавать

// ошибка с 0 в знаменателе в конструкторе

int main()
{
    // bignum q1("1234"), q2(1234), q3, q4, q5 ,q6, q7;
    // q1 = 1245;
    // q2 += 12;
    // q3 = 5;
    // q3 *= q2;
    // q4 = q3 * 2;
    // q5 = 1244;
    // q5 /= 2;
    // q6 = -23 % 5;
    // q7 = -23;
    // q7 = q7 % 5;
    // std::cout<<q1<<std::endl;
    // std::cout<<q2<<std::endl;
    // std::cout<<q3<<std::endl;
    // std::cout<<q4<<std::endl;
    // std::cout<<"    "<<q5<<std::endl;
    // std::cout<<q6<<std::endl;
    // std::cout<<q7<<std::endl;

    // q7 = gcd(64, 16);
    // std::cout<<q7<<std::endl;

    // std::cout<<std::endl;
    // std::cout<<std::endl;
    // std::cout<<std::endl;
    // std::cout<<std::endl;

    // rational_number x1("+1234", "4567");
    // rational_number x2("13", "12");
    // rational_number x3(-1324);
    // rational_number x4("1244/2");
    // float kk = -3.00, f=0000.4563;
    // rational_number k(kk), q(1234.0001), w(f);

    // w = q;

    // w = ("1234/123");
    // w = ("1234123");

    // std::cout<<x1<<std::endl;
    // std::cout<<x2<<std::endl;
    // std::cout<<x3<<std::endl;
    // std::cout<<x4<<std::endl;

    // x4 += 1;
    // std::cout<<x4<<std::endl;

    // x4 += 5;
    // std::cout<<x4<<std::endl;

    // x4 -= 2;
    // std::cout<<x4<<std::endl;

    // x4 *= 4;
    // std::cout<<x4<<std::endl;

    // x4 /= 2;
    // std::cout<<x4<<std::endl;

    // // x4 /= -x4;
    // // std::cout<<x4<<std::endl;

    // x4 = -x4;
    // std::cout<<x4<<std::endl;

    // x4++;
    // std::cout<<x4<<std::endl;

    // x4--;
    // std::cout<<x4<<std::endl;

    bignum q8 = 1234567891231;
    std::cout<<q8<<std::endl;

    std::cout<<LONG_LONG_MIN<<std::endl;
    std::cout<<LONG_LONG_MAX<<std::endl;

    rational_number x5("134/45");

    std::cout<<x5<<std::endl;
    std::cout<<std::endl;
    // std::cout<<(long long)(x5)<<std::endl;
    std::cout<<(long double)(x5)<<std::endl;

    // std::cout<<std::to_string(-1234)<<std::endl;
    // std::cout<<std::to_string(1234)<<std::endl;
    // std::cout<<std::to_string(+1234)<<std::endl;
    // std::cout<<std::to_string((long double)+346341234.13415637)<<std::endl;
    return 0;
}