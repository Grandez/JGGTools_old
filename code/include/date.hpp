#pragma once

#include <vector>
#include <string>
#include <memory>

#include "config.h"
#include "datetimebase.hpp"

using namespace std;

namespace NST {
class Date {
public:
   Date() = default;
   Date(const Date& src);
   Date(sstring str     , int fmt = -1);
   Date(const char *str, int fmt = -1);
   ~Date();
   struct tm *getTM();
   int getYear  ();
   int getMonth ();
   int getDay   ();
   sstring      toString (const char *fmt = "%F");
   const char * toChar   (const char *fmt = "%F");
private:
   class DateImpl;
   unique_ptr<DateImpl> impl_;
//   DateTimeBase dtb = DateTimeBase();
//   struct tm *ptm = dtb.getTM();
};
}
