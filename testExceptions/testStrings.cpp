#include "pch.h"
#include <iostream>

#include "../libjggtools/include/sstring.hpp"

using namespace NST;

TEST(String, ltrim) {
   sstring str(" test ");
   EXPECT_EQ(str.ltrim().compare("test "), 0);
}
TEST(String, rtrim) {
   sstring str(" test ");
   EXPECT_EQ(str.rtrim().compare(" test"), 0);
}
TEST(String, trim) {
   sstring str(" test ");
   EXPECT_EQ(str.trim().compare("test"), 0);
}
TEST(String, toChar) {
   sstring str("test");
   EXPECT_EQ(strcmp(str.toChar(),"test"), 0);
}
TEST(String, contains_space) {
   sstring str("one test");
   EXPECT_TRUE(str.contains(" "));
}
TEST(String, contains_word) {
   sstring str("one test");
   EXPECT_TRUE(str.contains("test"));
}
TEST(String, contains_pattern) {
   sstring str("one ttest");
   EXPECT_TRUE(str.contains("[t]+"));
}
TEST(String, tokenize) {
   sstring str("one test");
   vector<sstring> res = str.tokenize(string(" "));
   EXPECT_EQ(res.size(),2);
}
TEST(String, toUpper) {
   sstring str("test");
   str.toUpper();
   EXPECT_EQ(str.compare("TEST"),0);
}
TEST(String, tolower) {
   sstring str("TEST");
   str.toLower();
   EXPECT_EQ(str.compare("test"),0);
}
TEST(String, boolean_true_1) {
   sstring str("TEST");
   EXPECT_TRUE(str.makeBoolean());
}
TEST(String, boolean_true_2) {
   sstring str("yes");
   EXPECT_TRUE(str.makeBoolean());
}
TEST(String, boolean_true_3) {
   sstring str("1");
   EXPECT_TRUE(str.makeBoolean());
}
TEST(String, boolean_false_1) {
   sstring str("0");
   EXPECT_FALSE(str.makeBoolean());
}
TEST(String, boolean_false_2) {
   sstring str("f");
   EXPECT_FALSE(str.makeBoolean());
}
TEST(String, boolean_false_3) {
   sstring str("N");
   EXPECT_FALSE(str.makeBoolean());
}
TEST(String, boolean_true_4) {
   sstring str("test");
   EXPECT_TRUE(str.makeBoolean());
}

