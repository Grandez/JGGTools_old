#pragma once
#include <string>
#include <ctime>

#include "../../../include/config.h"
#include "date.hpp"
#include "time.hpp"

using namespace std;

namespace NST {
   class DateTimeImpl {
   public:   
      const enum class Type {TMS, DATETIME, DATE, TIME};
      DateTimeImpl();
      DateTimeImpl(time_t lvalue);
      DateTimeImpl(const char *str);
      DateTimeImpl(int year, int month, int day, int hour, int minutes, int seconds);
      int   getYear     ();
      int   getMonth    ();
      int   getDay      ();
      int   getJulianDay();
      int   getHour     ();
      int   getMinutes  ();
      int   getSeconds  ();

      char*   toChar   (char *ptr);
      string  toString ();
      time_t  timet    ();
      struct tm* getTM ();

      void addYears        (int   amount);
      void addMonths       (int   amount, bool last = true);
      void addDays         (int   amount);
      void addHours        (int   amount);
      void addMinutes      (int   amount);
      void addSeconds      (int   amount);
      void addTime         (long  amount);
      void addFromString   (const char *amount);
      void add         (long amount, string type);
      void add         (long amount, char   type);
      void add         (long amount, const char *type);
      void addTime_t        (std::time_t t);
    private:
      struct tm mtm;
      std::time_t lvalue = 0l; 
      Date *pDate;
      Time *pTime;
      void fillTM();
   };
}
