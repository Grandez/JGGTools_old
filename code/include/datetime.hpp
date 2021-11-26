#pragma once 
#include <memory>

#include "config.h"

namespace NST {
   class DateTime {
   public:
      DateTime();
      DateTime(sstring str);
      DateTime(const char *str);
      ~DateTime();
      int getYear   ();
      int getMonth  ();
      int getDay    ();
      int getHour   ();
      int getMin    ();
      int getSecond ();
      sstring     toString();
      const char* toChar();
   private:
      class DateTimeImpl;
      unique_ptr<DateTimeImpl, void (*)(DateTimeImpl *)> impl_;
   };
}
