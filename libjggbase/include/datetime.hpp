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
      sstring     toString();
      const char* toChar();
   private:
      class DateTimeImpl;
      unique_ptr<DateTimeImpl, void (*)(DateTimeImpl *)> impl_;
   };
}
