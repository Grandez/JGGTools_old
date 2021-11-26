#include "pch.h"
#include <cstring>

#include "../include/config.h"
#include "../include/exceptions.hpp"
#include "../libjggdatetimes/code/inc/time.hpp"

using namespace jggtools;

// Consructors
TEST(Time, time_now) {
  Time t;
  EXPECT_GT(t.asLong(), 0l);
}
TEST(Time, time_sep) {
  Time t(1,2,3);
  EXPECT_EQ(t.asLong(), 3723l);
}
TEST(Time, time_long) {
  Time t(3723);
  EXPECT_EQ(t.asLong(), 3723l);
}
TEST(Time, time_string_01) {
  Time t(string("1:2:3"));
  EXPECT_EQ(t.asLong(), 3723l);
}
TEST(Time, time_string_02) {
  Time t(string("01:02:03"));
  EXPECT_EQ(t.asLong(), 3723l);
}
TEST(Time, time_char_01) {
  const char *ptr = "1:2:3";
  Time t(ptr);
  EXPECT_EQ(t.asLong(), 3723l);
}
TEST(Time, time_char_02) {
  const char *ptr = "01:02:03";
  Time t(ptr);
  EXPECT_EQ(t.asLong(), 3723l);
}
TEST(Time, time_copy) {
  const char *ptr = "01:02:03";
  Time t1(ptr);
  Time t2(t1); 
  EXPECT_EQ(t2.asLong(), 3723l);
}

// ERRORS

TEST(Time, except_01) {
  EXPECT_THROW(Time t(-1,2,3), ToolsValueException *);
}
TEST(Time, except_02) {
  EXPECT_THROW(Time t(1,-2,3), ToolsValueException *);
}
TEST(Time, except_03) {
  EXPECT_THROW(Time t(1,2,-3), ToolsValueException *);
}
TEST(Time, except_04) {
  EXPECT_THROW(Time t(24,2,3), ToolsValueException *);
}
TEST(Time, except_05) {
  EXPECT_THROW(Time t(1,60,3), ToolsValueException *);
}
TEST(Time, except_06) {
  EXPECT_THROW(Time t(1,2,60), ToolsValueException *);
}

// RETRIEVING DATA

TEST(Time, struct_tm) {
  const char *ptr = "1:2:3";
  Time t(ptr);
  struct tm *ptm = t.getTM();
  EXPECT_EQ(ptm->tm_hour, 1);
  EXPECT_EQ(ptm->tm_min,  2);
  EXPECT_EQ(ptm->tm_sec,  3);
}
TEST(Time, fmt_default_01) {
  char szTime[32];
  Time t(3723);
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "01:02:03"), 0);
}
TEST(Time, fmt_default_02) {
  char szTime[32];
  char *ptr; 
  Time t(3723);
  ptr = t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(ptr, "01:02:03"), 0);
}
TEST(Time, fmt_custom_01) {
  char szTime[32];
  char *ptr; 
  Time t(3723);
  ptr = t.format(szTime, 32, "%r");
  EXPECT_EQ(strcmp(ptr, "01:02:03 AM"), 0);
}

// ARITHMETIC

TEST(Time, add_hour_01) {
  char szTime[32];
  Time t(3723);
  t.addHours(1);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "02:02:03"), 0);
}
TEST(Time, add_hour_23) {
  char szTime[32];
  Time t(86399); // 23:59:59
  t.addHours(1);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "00:59:59"), 0);
  EXPECT_EQ(lvalue, 3599);
}
TEST(Time, add_hour_day) {
  char szTime[32];
  Time t(86399); // 23:59:59
  t.addHours(24);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "23:59:59"), 0);
  EXPECT_EQ(lvalue, 86399);
}
TEST(Time, add_hour_days) {
  char szTime[32];
  Time t(86399); // 23:59:59
  t.addHours(48);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "23:59:59"), 0);
  EXPECT_EQ(lvalue, 86399);
}
TEST(Time, add_hour_days_plus_1) {
  char szTime[32];
  Time t(86399); // 23:59:59
  t.addHours(25);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "00:59:59"), 0);
  EXPECT_EQ(lvalue, 3599);
}
TEST(Time, add_hour_days_2) {
  char szTime[32];
  Time t(86399); // 23:59:59
  t.addHours(2);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "01:59:59"), 0);
  EXPECT_EQ(lvalue, 7199);
}
TEST(Time, add_hour_minus_1) {
  char szTime[32];
  Time t(0l); // 00:00:00
  t.addHours(-1);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "23:00:00"), 0);
  EXPECT_EQ(lvalue, 82800);
}
TEST(Time, add_hour_minus_2) {
  char szTime[32];
  Time t(0l); // 00:00:00
  t.addHours(-2);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "22:00:00"), 0);
  EXPECT_EQ(lvalue, 79200);
}
TEST(Time, subtract_hour_01) {
  char szTime[32];
  Time t(3723); // 01:02:03
  t.subtractHours(1);
  long lvalue = t.asLong();
  t.toChar(szTime, 123);
  EXPECT_EQ(strcmp(szTime, "00:02:03"), 0);
}
TEST(Time, subtract_hour_23) {
  char szTime[32];
  Time t(86399); // 23:59:59
  t.subtractHours(1);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "22:59:59"), 0);
  EXPECT_EQ(lvalue, 82799);
}
TEST(Time, subtract_hour_day) {
  char szTime[32];
  Time t(86399); // 23:59:59
  t.subtractHours(24);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "23:59:59"), 0);
  EXPECT_EQ(lvalue, 86399);
}
TEST(Time, subtract_hour_days) {
  char szTime[32];
  Time t(86399); // 23:59:59
  t.subtractHours(48);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "23:59:59"), 0);
  EXPECT_EQ(lvalue, 86399);
}
TEST(Time, subtract_hour_days_plus_1) {
  char szTime[32];
  Time t(86399); // 23:59:59
  t.subtractHours(25);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "22:59:59"), 0);
  EXPECT_EQ(lvalue, 82799);
}
TEST(Time, subtract_hour_days_2) {
  char szTime[32];
  Time t(7199); // 01:59:59
  t.subtractHours(2);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "23:59:59"), 0);
  EXPECT_EQ(lvalue, 86399);
}
TEST(Time, subtract_hour_minus_1) {
  char szTime[32];
  Time t(0l); // 00:00:00
  t.subtractHours(-1);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "01:00:00"), 0);
  EXPECT_EQ(lvalue, 3600);
}
TEST(Time, subtract_hour_minus_0) {
  char szTime[32];
  Time t(82800l); // 23:00:00
  t.subtractHours(-1);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "00:00:00"), 0);
  EXPECT_EQ(lvalue, 0);
}

TEST(Time, subtract_hour_minus_2) {
  char szTime[32];
  Time t(0l); // 00:00:00
  t.subtractHours(-2);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "02:00:00"), 0);
  EXPECT_EQ(lvalue, 7200);
}
TEST(Time, add_minute_01) {
  char szTime[32];
  Time t(86399); // 23:59:59
  t.addMinutes(1);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "00:00:59"), 0);
  EXPECT_EQ(lvalue, 59);
}
TEST(Time, add_minute_hour) {
  char szTime[32];
  Time t(86399); // 23:59:59
  t.addMinutes(60);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "00:59:59"), 0);
  EXPECT_EQ(lvalue, 3599);
}
TEST(Time, add_minute_hours) {
  char szTime[32];
  Time t(86399); // 23:59:59
  t.addMinutes(120);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "01:59:59"), 0);
  EXPECT_EQ(lvalue, 7199);
}
TEST(Time, add_minute_0) {
  char szTime[32];
  Time t(86340); // 23:59:00
  t.addMinutes(1);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "00:00:00"), 0);
  EXPECT_EQ(lvalue, 0);
}
TEST(Time, add_minute_minus_1) {
  char szTime[32];
  Time t(60); // 00:01:00
  t.addMinutes(-1);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "00:00:00"), 0);
  EXPECT_EQ(lvalue, 0);
}
TEST(Time, add_minute_minus_1_minus_day) {
  char szTime[32];
  Time t(0l); // 00:00:00
  t.addMinutes(-1);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "23:59:00"), 0);
  EXPECT_EQ(lvalue, 86340);
}
TEST(Time, subtract_minute_01) {
  char szTime[32];
  Time t(86399); // 23:59:59
  t.subtractMinutes(1);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "23:58:59"), 0);
  EXPECT_EQ(lvalue, 86339);
}
TEST(Time, subtract_minute_hour) {
  char szTime[32];
  Time t(86399); // 23:59:59
  t.subtractMinutes(60);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "22:59:59"), 0);
  EXPECT_EQ(lvalue, 82799);
}
TEST(Time, subtract_minute_hours) {
  char szTime[32];
  Time t(7199); // 01:59:59
  t.subtractMinutes(120);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "23:59:59"), 0);
  EXPECT_EQ(lvalue, 86399);
}
TEST(Time, subtract_minute_0) {
  char szTime[32];
  Time t(60); // 00:01:00
  t.subtractMinutes(1);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "00:00:00"), 0);
  EXPECT_EQ(lvalue, 0);
}
TEST(Time, subtract_minute_minus_1) {
  char szTime[32];
  Time t(0l); // 00:00:00
  t.subtractMinutes(-1);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "00:01:00"), 0);
  EXPECT_EQ(lvalue, 60);
}
TEST(Time, subtract_minute_minus_1_minus_day) {
  char szTime[32];
  Time t(0l); // 00:00:00
  t.subtractMinutes(1);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "23:59:00"), 0);
  EXPECT_EQ(lvalue, 86340);
}
TEST(Time, add_second_01) {
  char szTime[32];
  Time t(86399); // 23:59:59
  t.addSeconds(1);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "00:00:00"), 0);
  EXPECT_EQ(lvalue, 0);
}
TEST(Time, add_second_02) {
  char szTime[32];
  Time t(86399); // 23:59:59
  t.addSeconds(2);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "00:00:01"), 0);
  EXPECT_EQ(lvalue, 1);
}
TEST(Time, add_second_min) {
  char szTime[32];
  Time t(86399); // 23:59:59
  t.addSeconds(60);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "00:00:59"), 0);
  EXPECT_EQ(lvalue, 59);
}
TEST(Time, add_second_hour) {
  char szTime[32];
  Time t(0l);
  t.addSeconds(3600);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "01:00:00"), 0);
  EXPECT_EQ(lvalue, 3600);
}

TEST(Time, subtract_second_minus_1) {
  char szTime[32];
  Time t(0l); 
  t.addSeconds(-1);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "23:59:59"), 0);
  EXPECT_EQ(lvalue, 86399);
}

TEST(Time, subtract_second_01) {
  char szTime[32];
  Time t(0l); // 23:59:59
  t.subtractSeconds(1);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "23:59:59"), 0);
  EXPECT_EQ(lvalue, 86399);
}
TEST(Time, subtract_second_plus_1) {
  char szTime[32];
  Time t(86399); // 23:59:59
  t.subtractSeconds(-1);
  long lvalue = t.asLong();
  t.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "00:00:00"), 0);
  EXPECT_EQ(lvalue, 86399);
}

// Operators

TEST(Time, operator_plus_eq_sec_01) {
  char szTime[32];
  Time t1(86399); // 23:59:59
  Time t2(1);     // 00:00:01
  t1 += t2;
  long lvalue = t1.asLong();
  t1.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "00:00:00"), 0);
  EXPECT_EQ(lvalue, 0);
}
TEST(Time, operator_plus_eq_min_01) {
  char szTime[32];
  Time t1(86340); // 23:59:00
  Time t2(60);    // 00:01:00
  t1 += t2;
  long lvalue = t1.asLong();
  t1.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "00:00:00"), 0);
  EXPECT_EQ(lvalue, 0);
}
TEST(Time, operator_plus_eq_hour_01) {
  char szTime[32];
  Time t1(82800); // 23:00:00
  Time t2(3600);  // 01:00:00
  t1 += t2;
  long lvalue = t1.asLong();
  t1.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "00:00:00"), 0);
  EXPECT_EQ(lvalue, 0);
}
TEST(Time, operator_minus_eq_sec_01) {
  char szTime[32];
  Time t1(1);     // 00:00:01
  Time t2(1);     // 00:00:01
  t1 -= t2;
  long lvalue = t1.asLong();
  t1.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "00:00:00"), 0);
  EXPECT_EQ(lvalue, 0);
}
TEST(Time, operator_minus_eq_min_01) {
  char szTime[32];
  Time t1(60);  // 00:01:00
  Time t2(60);  // 00:01:00
  t1 -= t2;
  long lvalue = t1.asLong();
  t1.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "00:00:00"), 0);
  EXPECT_EQ(lvalue, 0);
}
TEST(Time, operator_minus_eq_hour_01) {
  char szTime[32];
  Time t1(3600);  // 01:00:00
  Time t2(3600);  // 01:00:00
  t1 -= t2;
  long lvalue = t1.asLong();
  t1.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "00:00:00"), 0);
  EXPECT_EQ(lvalue, 0);
}

TEST(Time, operator_plussec_01) {
  char szTime[32];
  Time t1(86399); // 23:59:59
  Time t2(1);     // 00:00:01
  Time t3 = t1 + t2;
  long lvalue = t3.asLong();
  t3.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "00:00:00"), 0);
  EXPECT_EQ(lvalue, 0);
  EXPECT_EQ(t1.asLong(), 86399);
  EXPECT_EQ(t2.asLong(),     1);
}
TEST(Time, operator_plus_min_01) {
  char szTime[32];
  Time t1(60);    // 00:01:00
  Time t2(60);    // 00:01:00
  Time t3 = t1 - t2;
  long lvalue = t3.asLong();
  t3.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "00:00:00"), 0);
  EXPECT_EQ(lvalue, 0);
  EXPECT_EQ(t1.asLong(), 60);
  EXPECT_EQ(t2.asLong(), 60);
}
TEST(Time, operator_plus_hour_01) {
  char szTime[32];
  Time t1(82800); // 23:00:00
  Time t2(3600);  // 01:00:00
  Time t3 = t1 + t2;
  long lvalue = t3.asLong();
  t3.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "00:00:00"), 0);
  EXPECT_EQ(lvalue, 0);
  EXPECT_EQ(t1.asLong(), 82800);
  EXPECT_EQ(t2.asLong(), 3600);
}
TEST(Time, operator_minus_sec_01) {
  char szTime[32];
  Time t1(1);     // 00:00:01
  Time t2(1);     // 00:00:01
  Time t3 = t1 - t2;
  long lvalue = t3.asLong();
  t3.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "00:00:00"), 0);
  EXPECT_EQ(lvalue, 0);
  EXPECT_EQ(t1.asLong(), 1);
  EXPECT_EQ(t2.asLong(), 1);
}
TEST(Time, operator_minus_min_01) {
  char szTime[32];
  Time t1(60);  // 00:01:00
  Time t2(60);  // 00:01:00
  Time t3 = t1 - t2;
  long lvalue = t3.asLong();
  t3.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "00:00:00"), 0);
  EXPECT_EQ(lvalue, 0);
  EXPECT_EQ(t1.asLong(), 60);
  EXPECT_EQ(t2.asLong(), 60);
}
TEST(Time, operator_minus_hour_01) {
  char szTime[32];
  Time t1(3600);  // 01:00:00
  Time t2(3600);  // 01:00:00
  Time t3 = t1 - t2;
  long lvalue = t3.asLong();
  t3.toChar(szTime, 32);
  EXPECT_EQ(strcmp(szTime, "00:00:00"), 0);
  EXPECT_EQ(lvalue, 0);
  EXPECT_EQ(t1.asLong(), 3600);
  EXPECT_EQ(t2.asLong(), 3600);
}

// Comparators

TEST(Time, comp_eq_01) {
  Time t1(86399); // 23:59:59
  Time t2(1);     // 00:00:01
  bool res = (t1 == t2);
  EXPECT_FALSE(res);
}
TEST(Time, comp_eq_02) {
  Time t1(86399); // 23:59:59
  Time t2(86399); 
  bool res = (t1 == t2);
  EXPECT_TRUE(res);
}
TEST(Time, comp_eq_03) {
  Time t1(86399); // 23:59:59
  Time t2(1);     // 00:00:01
  bool res = (t1 != t2);
  EXPECT_TRUE(res);
}
TEST(Time, comp_eq_04) {
  Time t1(86399); // 23:59:59
  Time t2(86399); 
  bool res = (t1 != t2);
  EXPECT_FALSE(res);
}
TEST(Time, comp_gt_01) {
  Time t1(86399); // 23:59:59
  Time t2(1);     // 00:00:01
  bool res = (t1 > t2);
  EXPECT_TRUE(res);
}
TEST(Time, comp_gt_02) {
  Time t1(86399); // 23:59:59
  Time t2(1);     // 00:00:01
  bool res = (t2 > t1);
  EXPECT_FALSE(res);
}
TEST(Time, comp_gt_03) {
  Time t1(86399); // 23:59:59
  Time t2(1);     // 00:00:01
  bool res = (t2 > t1);
  EXPECT_FALSE(res);
}
TEST(Time, comp_gt_04) {
  Time t1(86399); // 23:59:59
  Time t2(1);     // 00:00:01
  bool res = (t1 > t2);
  EXPECT_TRUE(res);
}
TEST(Time, comp_ge_01) {
  Time t1(86399); // 23:59:59
  Time t2(1);     // 00:00:01
  bool res = (t1 >= t2);
  EXPECT_TRUE(res);
}
TEST(Time, comp_ge_02) {
  Time t1(86399); // 23:59:59
  Time t2(86399);   
  bool res = (t1 >= t2);
  EXPECT_TRUE(res);
}
TEST(Time, comp_ge_03) {
  Time t1(86399); // 23:59:59
  Time t2(1);     // 00:00:01
  bool res = (t2 >= t1);
  EXPECT_FALSE(res);
}
TEST(Time, comp_ge_04) {
  Time t1(86399); // 23:59:59
  Time t2(86399);   
  bool res = (t2 >= t1);
  EXPECT_TRUE(res);
}
TEST(Time, comp_lt_01) {
  Time t1(86399); // 23:59:59
  Time t2(1);     // 00:00:01
  bool res = (t1 < t2);
  EXPECT_FALSE(res);
}
TEST(Time, comp_lt_02) {
  Time t1(86399); // 23:59:59
  Time t2(1);     // 00:00:01
  bool res = (t2 < t1);
  EXPECT_TRUE(res);
}
TEST(Time, comp_lt_03) {
  Time t1(86399); // 23:59:59
  Time t2(1);     // 00:00:01
  bool res = (t2 < t1);
  EXPECT_TRUE(res);
}
TEST(Time, comp_lt_04) {
  Time t1(86399); // 23:59:59
  Time t2(1);     // 00:00:01
  bool res = (t1 < t2);
  EXPECT_FALSE(res);
}
TEST(Time, comp_le_01) {
  Time t1(86399); // 23:59:59
  Time t2(1);     // 00:00:01
  bool res = (t1 <= t2);
  EXPECT_FALSE(res);
}
TEST(Time, comp_le_02) {
  Time t1(86399); // 23:59:59
  Time t2(86399);   
  bool res = (t1 <= t2);
  EXPECT_TRUE(res);
}
TEST(Time, comp_le_03) {
  Time t1(86399); // 23:59:59
  Time t2(1);     // 00:00:01
  bool res = (t2 <= t1);
  EXPECT_TRUE(res);
}
TEST(Time, comp_le_04) {
  Time t1(86399); // 23:59:59
  Time t2(86399);   
  bool res = (t2 <= t1);
  EXPECT_TRUE(res);
}

