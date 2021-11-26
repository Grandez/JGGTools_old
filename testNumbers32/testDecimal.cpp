#include "pch.h"
#include <iostream>
#include <cstring>
#include "../include/config.h"
#include "../libjggnumbers/code/inc/decimal.hpp"

using namespace jggtools;
/////////////////////////////////////////
// Constructor const char *value
/////////////////////////////////////////
TEST(Decimal, char_1_23) {
   EXPECT_NO_THROW(Decimal("1.23"));
}
TEST(Decimal, char_123) {
   EXPECT_NO_THROW(Decimal("123"));
}
TEST(Decimal, char_1point) {
   EXPECT_NO_THROW(Decimal("1."));
}
TEST(Decimal, char_dec) {
   EXPECT_NO_THROW(Decimal(".123"));
}
TEST(Decimal, char_1_23_plus) {
   EXPECT_NO_THROW(Decimal("+1.23"));
}
TEST(Decimal, char_123_plus) {
   EXPECT_NO_THROW(Decimal("+123"));
}
TEST(Decimal, char_1point_plus) {
   EXPECT_NO_THROW(Decimal("+1."));
}
TEST(Decimal, char_dec_plus) {
   EXPECT_NO_THROW(Decimal("+.123"));
}
TEST(Decimal, char_minus_1_23) {
   EXPECT_NO_THROW(Decimal("-1.23"));
}
TEST(Decimal, char_123_minus) {
   EXPECT_NO_THROW(Decimal("-123"));
}
TEST(Decimal, char_1point_minus) {
   EXPECT_NO_THROW(Decimal("-1."));
}
TEST(Decimal, char_dec_minus) {
   EXPECT_NO_THROW(Decimal("-.123"));
}
/////////////////////////////////////////
// Constructor sstring
/////////////////////////////////////////

TEST(Decimal, str_1_23) {
   EXPECT_NO_THROW(Decimal(string("1.23")));
}
TEST(Decimal, str_123) {
   EXPECT_NO_THROW(Decimal(string("123")));
}
TEST(Decimal, str_1point) {
   EXPECT_NO_THROW(Decimal(string("1.")));
}
TEST(Decimal, str_dec) {
   EXPECT_NO_THROW(Decimal(string(".123")));
}
TEST(Decimal, str_1_23_plus) {
   EXPECT_NO_THROW(Decimal(string("+1.23")));
}
TEST(Decimal, str_123_plus) {
   EXPECT_NO_THROW(Decimal(string("+123")));
}
TEST(Decimal, str_1point_plus) {
   EXPECT_NO_THROW(Decimal(string("+1.")));
}
TEST(Decimal, str_dec_plus) {
   EXPECT_NO_THROW(Decimal(string("+.123")));
}
TEST(Decimal, str_minus_1_23) {
   EXPECT_NO_THROW(Decimal(string("-1.23")));
}
TEST(Decimal, str_123_minus) {
   EXPECT_NO_THROW(Decimal(string("-123")));
}
TEST(Decimal, str_1point_minus) {
   EXPECT_NO_THROW(Decimal(string("-1.")));
}
TEST(Decimal, str_dec_minus) {
   EXPECT_NO_THROW(Decimal(string("-.123")));
}

/////////////////////////////////////////
// Constructor string
/////////////////////////////////////////

TEST(Decimal, string) {
   EXPECT_NO_THROW(Decimal(string("-.123")));
}

/////////////////////////////////////////
// Constructor numbers
/////////////////////////////////////////

TEST(Decimal, integer) {
   EXPECT_NO_THROW(Decimal(123));
}
TEST(Decimal, long_number) {
   EXPECT_NO_THROW(Decimal(123l));
}
TEST(Decimal, float_number) {
   EXPECT_NO_THROW(Decimal(1.23f));
}
TEST(Decimal, double_number) {
   EXPECT_NO_THROW(Decimal(1.23));
}
TEST(Decimal, signed_float) {
   EXPECT_NO_THROW(Decimal(+1.23));
}
TEST(Decimal, minus_float) {
   EXPECT_NO_THROW(Decimal(-1.23));
}
TEST(Decimal, no_int) {
   EXPECT_NO_THROW(Decimal(.23));
}
TEST(Decimal, negative_no_int) {
   EXPECT_NO_THROW(Decimal(-.23));
}

/////////////////////////////////////////
// TO xxx
/////////////////////////////////////////

TEST(Decimal, toString_01) {
   Decimal dec = Decimal(12.345);
   string str = dec.toString();
   EXPECT_EQ(str, "12.345");
}
TEST(Decimal, toString_02) {
   Decimal dec = Decimal(+12.345);
   string str = dec.toString();
   EXPECT_EQ(str, "12.345");
}
TEST(Decimal, toString_03) {
   Decimal dec = Decimal(-12.345);
   string str = dec.toString();
   EXPECT_EQ(str, "-12.345");
}
TEST(Decimal, toString_04) {
   Decimal dec = Decimal(.12345);
   string str = dec.toString();
   EXPECT_EQ(str, "0.12345");
}
TEST(Decimal, toString_05) {
   Decimal dec = Decimal(-.12345);
   string str = dec.toString();
   EXPECT_EQ(str, "-0.12345");
}
TEST(Decimal, toString_06) {
   Decimal dec = Decimal(-0.12345);
   string str = dec.toString();
   EXPECT_EQ(str, "-0.12345");
}
TEST(Decimal, toChar_01) {
   Decimal dec = Decimal(12.345);
   char * str = dec.toChar();
   EXPECT_EQ(strcmp(str, "12.345"), 0);
   free(str);
}
TEST(Decimal, toChar_02) {
   Decimal dec = Decimal(+12.345);
   char * str = dec.toChar();
   EXPECT_EQ(strcmp(str, "12.345"), 0);
   free(str);
}
TEST(Decimal, toChar_03) {
   Decimal dec = Decimal(-12.345);
   char * str = dec.toChar();
   EXPECT_EQ(strcmp(str, "-12.345"), 0);
   free(str);
}
TEST(Decimal, toChar_04) {
   Decimal dec = Decimal(.12345);
   char * str = dec.toChar();
   EXPECT_EQ(strcmp(str, "0.12345"), 0);
   free(str);
}
TEST(Decimal, toChar_05) {
   Decimal dec = Decimal(-.12345);
   char * str = dec.toChar();
   EXPECT_EQ(strcmp(str, "-0.12345"), 0);
   free(str);
}
TEST(Decimal, toChar_06) {
   Decimal dec = Decimal(-0.12345);
   char * str = dec.toChar();
   EXPECT_EQ(strcmp(str, "-0.12345"), 0);
   free(str);
}
TEST(Decimal, toString_rounded) {
   Decimal dec = Decimal(12.345);
   string str = dec.toStringRounded();
   EXPECT_EQ(str, "12");
}
TEST(Decimal, toString_rounded_1) {
   Decimal dec = Decimal(12.345);
   string str = dec.toStringRounded(1);
   EXPECT_EQ(str, "12.3");
}
TEST(Decimal, toString_rounded_2) {
   Decimal dec = Decimal(12.345);
   string str = dec.toStringRounded(2);
   EXPECT_EQ(str, "12.35");
}
TEST(Decimal, toString_rounded_neg) {
   Decimal dec = Decimal(-12.345);
   string str = dec.toStringRounded();
   EXPECT_EQ(str, "-12");
}
TEST(Decimal, toString_rounded_neg_1) {
   Decimal dec = Decimal(-12.345);
   string str = dec.toStringRounded(1);
   EXPECT_EQ(str, "-12.3");
}
TEST(Decimal, toString_rounded_neg_2) {
   Decimal dec = Decimal(-12.345);
   string str = dec.toStringRounded(2);
   EXPECT_EQ(str, "-12.35");
}
TEST(Decimal, toChar_rounded) {
   Decimal dec = Decimal(12.345);
   char * str = dec.toCharRounded();
   EXPECT_EQ(strcmp(str, "12"), 0);
   free(str);
}
TEST(Decimal, toChar_rounded_1) {
   Decimal dec = Decimal(12.345);
   char * str = dec.toCharRounded(1);
   EXPECT_EQ(strcmp(str, "12.3"), 0);
   free(str);
}
TEST(Decimal, toChar_rounded_2) {
   Decimal dec = Decimal(12.345);
   char * str = dec.toCharRounded(2);
   EXPECT_EQ(strcmp(str, "12.35"), 0);
   free(str);
}
TEST(Decimal, toChar_rounded_neg) {
   Decimal dec = Decimal(-12.345);
   char * str = dec.toCharRounded();
   EXPECT_EQ(strcmp(str, "-12"), 0);
   free(str);
}
TEST(Decimal, toChar_rounded_neg_1) {
   Decimal dec = Decimal(-12.345);
   char * str = dec.toCharRounded(1);
   EXPECT_EQ(strcmp(str, "-12.3"), 0);
   free(str);
}
TEST(Decimal, toChar_rounded_neg_2) {
   Decimal dec = Decimal(-12.345);
   char * str = dec.toCharRounded(2);
   EXPECT_EQ(strcmp(str, "-12.35"), 0);
   free(str);
}
/////////////////////////////////////////
// Round
/////////////////////////////////////////
TEST(Round, round_0) {
   Decimal dec = Decimal(12.345);
   Decimal res = dec.round();
   EXPECT_EQ(res.toString(), "12");
}
TEST(Round, round_1) {
   Decimal dec = Decimal(12.345);
   Decimal res = dec.round(1);
   EXPECT_EQ(res.toString(), "12.3");
}
TEST(Round, round_2) {
   Decimal dec = Decimal(12.345);
   Decimal res = dec.round(2);
   EXPECT_EQ(res.toString(), "12.35");
}
TEST(Round, round_3) {
   Decimal dec = Decimal(12.345);
   Decimal res = dec.round(3);
   EXPECT_EQ(res.toString(), "12.345");
}
TEST(Round, round_minus_0) {
   Decimal dec = Decimal(12.345);
   Decimal res = dec.round();
   EXPECT_EQ(res.toString(), "12");
}
TEST(Round, round_minus_1) {
   Decimal dec = Decimal(-12.345);
   Decimal res = dec.round(1);
   EXPECT_EQ(res.toString(), "-12.3");
}
TEST(Round, round_minus_2) {
   Decimal dec = Decimal(-12.345);
   Decimal res = dec.round(2);
   EXPECT_EQ(res.toString(), "-12.35");
}
TEST(Round, round_minus_3) {
   Decimal dec = Decimal(-12.345);
   Decimal res = dec.round(3);
   EXPECT_EQ(res.toString(), "-12.345");
}

