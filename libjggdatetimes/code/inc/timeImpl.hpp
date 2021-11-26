#pragma once
#include <string>
#include <ctime>

#include "../../../include/config.h"

using namespace std;

namespace NST {
   class TimeImpl {
   public:   
      const enum class Type {TMS, DATETIME, DATE, TIME};
      TimeImpl();
      TimeImpl(long lvalue);
      TimeImpl(const char *str);
      TimeImpl(int hour, int minutes, int seconds);
      int   getHour();
      int   getMinutes();
      int   getSeconds();

      char*   toChar   (char *ptr, size_t size);
      char*   format   (char* buff, size_t size, const char *fmt);
      string  toString (const char *fmt);
      struct tm*  getTM(struct tm*);

      // Time
      long longValue     ();
      void addHours      (int   amount);
      void addMinutes    (int   amount);
      void addSeconds    (int   amount);
      void addTime       (const char *amount, bool positive = true); 
      void addAmountTime (long amount);
      long addAmountTime (long ltime1, long ltime2);

      void updateTime(long lvalue);
      void updateTime(int hour, int min, int sec);
    private:
      struct tm mtm;
      long ltime = 0l; 
      void setStructTm();
      void setLongTime();
      void setLongTime(long lvalue);
   };
}
