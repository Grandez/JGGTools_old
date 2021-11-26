#include "pch.h"
#include <cstring>
#include <locale>

#include "../include/config.h"
#include "../include/exceptions.hpp"
#include "../libjggdatetimes/code/inc/date.hpp"

using namespace jggtools;

// Consructors
TEST(Date, date_now) {
  Date d;
  EXPECT_GT(d.asLong(), 0l);
}
TEST(Date, date_sep) {
  Date d(2020,1,1);
  EXPECT_EQ(d.asLong(), 43465l);
}
TEST(Date, date_long) {
  Date d(43465l);
  EXPECT_EQ(d.asLong(), 43465l);
}
TEST(Date, date_string) {
  setlocale(LC_ALL, "es_ES");
  Date d("01/02/2020");
  setlocale(LC_ALL, NULL);
  EXPECT_EQ(d.asLong(), 43465l);
}
TEST(Date, date_date) {
  setlocale(LC_ALL, "es_ES");
  Date d1("01/02/2020");
  Date d2(d1);
  setlocale(LC_ALL, NULL);
  EXPECT_EQ(d2.asLong(), 43465l);
}


