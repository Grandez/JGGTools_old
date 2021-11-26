#pragma once

#include <vector>
#include <string>

#include "config.h"
#include "sstring.hpp"
#include "datetimebase.hpp"
#include "time.hpp"

using namespace std;

namespace NST {
class Time {
public:
   Time() = default;
   Time(const Time& src);
   Time(string str);
   Time(const char *str);

   struct tm*  getTM();
   sstring     toString(const char* fmt = "%X");
   const char* toChar  (const char* fmt = "%X");
private:
   DateTimeBase dtb = DateTimeBase();
};
}
