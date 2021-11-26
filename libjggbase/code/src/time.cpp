#include "time.hpp"
#include <time.h>
#include <regex>

#ifdef _WIN32
#pragma warning( disable : 4996 )
#endif

#include "config.h"
#include "sstring.hpp"
#include "time.hpp"

namespace NST {
   Time::Time(string str)      { Time(str.c_str());     }
   Time::Time(const char *str) { dtb.validateTime(str); }
   Time::Time(const Time& src) { dtb = src.dtb;         }

   struct tm*  Time::getTM   ()                { return dtb.getTM(); }
   sstring     Time::toString(const char *fmt) { return dtb.format(fmt);         }
   const char* Time::toChar  (const char *fmt) { return dtb.format(fmt).c_str(); }
}