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

      char*   toChar   (char *ptr, size_t size);
      char*   format   (char* buff, size_t size, const char *fmt);
      //string      toString (const char* fmt);
      struct tm* getTM();

      // DateTime
      time_t timet     ();

      void addYears        (int   amount, bool last = true);
      void addMonths       (int   amount, bool last = true);
      void addDays         (int   amount);
      void addHours        (int   amount);
      void addMinutes      (int   amount);
      void addSeconds      (int   amount);
      void addTime         (long  amount);
      void addDateTime       (const char *amount, bool positive = true); 
      void addAmountDateTime (std::time_t amount);
      std::time_t addAmountDateTime (std::time_t ltime1, std::time_t ltime2);
      void addString         (const char *amount);
      void addString         (long amount, string type);
      void addString         (long amount, char   type);
      void addString         (long amount, const char *type);
      void updateDateTime(long lvalue);
      void updateDateTime(int hour, int min, int sec);
      void addTimeT        (std::time_t t);
    private:
      struct tm mtm;
      std::time_t lvalue = 0l; 
      Date *date;
      Time *time;
      void fillTM();
   };
}
