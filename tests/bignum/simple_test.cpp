#include <gtest/gtest.h>
#include <iostream>
#include <string.h>

#include "../../src/bignum/bignum.h"

class bignum_test : public testing::Test {};

TEST(bignum_test, bignum_constructor_test){
    int signed_value = -12345;
	bignum from_string = bignum("-12345");
	bignum from_bignum = from_string;
    bignum from_signed_int = bignum(signed_value);
    bignum from_long_long = bignum(static_cast<long long>(signed_value));

    ASSERT_EQ(from_bignum, from_string) << "Should be equal as built from the same value " << signed_value;
	ASSERT_EQ(from_bignum, from_signed_int) << "Should be equal as built from the same value " << signed_value;
    ASSERT_EQ(from_bignum, from_long_long) << "Should be equal as built from the same value " << signed_value;
}

TEST(bignum_test, unsigned_constructor_test){
    unsigned unsigned_value = 12321;
    bignum from_char_string = bignum(false, std::to_string(unsigned_value));
    bignum from_unsigned = bignum(unsigned_value);
    bignum from_unsigned_long_long = bignum(static_cast<unsigned long long>(unsigned_value));

    ASSERT_EQ(from_unsigned, from_char_string) << "Should be equal as built from the same value " << unsigned_value;
    ASSERT_EQ(from_char_string, from_unsigned_long_long) << "Should be equal as built from the same value " << unsigned_value;
}

// int main(int argc, char *argv[])
// {
// 	::testing::InitGoogleTest(&argc, argv);
// 	return RUN_ALL_TESTS();
// }