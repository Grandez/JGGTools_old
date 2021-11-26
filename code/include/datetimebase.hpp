#pragma once
#include <ctime>

#include "config.h"

namespace NST {
   class DateTimeBase {
   public:   
      DateTimeBase();
      struct tm* getTM();
      void validateDate(const char *str, int fmt = -1);
      void  validateTime(const char *str);
      bool       isLeap(int year);


      sstring    format(const char *fmt);
      DateTimeBase& setTM(struct tm *ptm);
    private:
      struct tm mtm;
      void       validateDateValues (const char *str);
      void       validateTimeValues (sstring str);
      void       fillTmDate(const char *str, int fmt);
      void       fillTmTime(vector<int> toks);
   };
}
