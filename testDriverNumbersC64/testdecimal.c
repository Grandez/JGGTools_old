#include "../libjggnumbers/code/inc/decimal.h"
#include "messages.h"
#include "testdecimal.h"

/*
decimal *decimalChar (char *str);
decimal *decimalFloat(float f);
decimal *decimalLong (long l);
decimal *decimalInt  (int i);
*/
#define CREATE "%3d - Creating decimal %s\t"

void decimal_char_1_23() {
   test(CREATE, 1, "1.23");
   decimal *dec = decimalChar ("1.23");
   check(dec, 1, 23);
}
void decimal_char_123 () {
   test(CREATE, 2, "123");
   decimal *dec = decimalChar ("123");
   check(dec, 123, 0);
}
void decimal_char_1point() {
   test(CREATE, 3, "1.");
   decimal *dec = decimalChar ("1.");
   check(dec, 1, 0);
}
void decimal_char_dec() {
   test(CREATE, 4, ".123");
   decimal *dec = decimalChar (".123");
   check(dec, 0, 123);
}
void decimal_char_1_23_plus() {
   test(CREATE, 5, "+1.23");
   decimal *dec = decimalChar ("+1.23");
   check(dec, 1, 23);
}
void decimal_char_123_plus() {
   test(CREATE, 6, "+123");
   decimal *dec = decimalChar ("+123");
   check(dec, 123, 0);
}
void decimal_char_1point_plus() {
   test(CREATE, 7, "+1.");
   decimal *dec = decimalChar ("+1.");
   check(dec, 1, 0);
}
void decimal_char_dec_plus() {
   test(CREATE, 8, "+.123");
   decimal *dec = decimalChar ("+.123");
   check(dec, 0, 123);
}
void decimal_char_minus_1_23() {
   test(CREATE, 9, "-1.23");
   decimal *dec = decimalChar ("-1.23");
   check(dec, -1, 23);
}
void decimal_char_123_minus() {
   test(CREATE, 10, "-123");
   decimal *dec = decimalChar ("-123");
   check(dec, -123, 0);
}
void decimal_char_1point_minus() {
   test(CREATE, 11, "-1.");
   decimal *dec = decimalChar ("-1.");
   check(dec, -1, 0);
}
void decimal_char_dec_minus() {
   test(CREATE, 12, "-.123");
   decimal *dec = decimalChar ("-.123");
   check(dec, 0, 123);
}
void decimal_integer() {
   test(CREATE, 13, "123");
   decimal *dec = decimalInt (123);
   check(dec, 123, 0);
}
void decimal_long() {
   test(CREATE, 14, "123l");
   decimal *dec = decimalLong (123l);
   check(dec, 123, 0);
}
void decimal_integer_minus() {
   test(CREATE, 15, "-123");
   decimal *dec = decimalInt (-123);
   check(dec, -123, 0);
}
void decimal_long_minus() {
   test(CREATE, 16, "-123l");
   decimal *dec = decimalLong (-123l);
   check(dec, -123, 0);
}
void decimal_float_number() {
   test(CREATE, 17, "1.23f");
   decimal *dec = decimalFloat (1.23f);
   check(dec, 1, 23);
}
void decimal_float_number_neg() {
   test(CREATE, 18, "-1.23f");
   decimal *dec = decimalFloat (-1.23f);
   check(dec, -1, 23);
}
void decimal_signed_float() {
   test(CREATE, 19, "+1.23f");
   decimal *dec = decimalFloat (+1.23f);
   check(dec, 1, 23);
}
void decimal_double_number() {
   test(CREATE, 20, "1.23l");
   decimal *dec = decimalDouble (1.23l);
   check(dec, 1, 23);
}
void decimal_signed_Double() {
   test(CREATE, 21, "+1.23l");
   decimal *dec = decimalDouble (+1.23l);
   check(dec, 1, 23);
}
void decimal_double_minus() {
   test(CREATE, 22, "-1.23l");
   decimal *dec = decimalDouble (-1.23l);
   check(dec, -1, 23);
}
void decimal_no_int() {
   test(CREATE, 23, ".23");
   decimal *dec = decimalFloat (.23);
   check(dec, 0, 23);
}
void decimal_negative_no_int() {
   test(CREATE, 24, "-.23");
   decimal *dec = decimalFloat (-.23);
   check(dec, 0, 23);
}


/*

/////////////////////////////////////////
// Constructor numbers
/////////////////////////////////////////

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

*/
void testDecimal() {
   decimal_char_1_23();
   decimal_char_1_23();
   decimal_char_123 ();
   decimal_char_1point();
   decimal_char_dec();
   decimal_char_1_23_plus();
   decimal_char_123_plus();
   decimal_char_1point_plus();
   decimal_char_dec_plus();
   decimal_char_minus_1_23();
   decimal_char_123_minus();
   decimal_char_1point_minus();
   decimal_char_dec_minus();
   decimal_integer();
   decimal_long();
   decimal_integer_minus();
   decimal_long_minus();
   decimal_float_number();
   decimal_float_number_neg();
   decimal_signed_float();
   decimal_double_number();
   decimal_signed_Double();
   decimal_double_minus();
   decimal_no_int();
   decimal_negative_no_int();

}

