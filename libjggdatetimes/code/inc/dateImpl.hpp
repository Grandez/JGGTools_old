#pragma once
#include <string>
#include <ctime>
#include <vector>

#include "../../../include/config.h"

namespace NST {
   class DateImpl {
   public:   
      const enum class Type {TMS, DATETIME, DATE, TIME};
      DateImpl();
      DateImpl(long lvalue);
      DateImpl(const char *str, int fmt = -1);
      DateImpl(int year, int month, int day);

     int getYear();
     int getMonth();
     int getDay();
     int getJulianDay();

      char*   toChar   (char *ptr);
      char*   format   (char* buff, size_t size, const char *fmt);
      //string      toString (const char* fmt);
      struct tm* getTM(struct tm* ptm);

      // Date
      long longValue     ();
      void addYears      (int   amount, bool last = true);
      void addMonths     (int   amount, bool last = true);
      void addDays       (int   amount);
      void addDate       (const char *amount, bool positive = true); 
      void addAmountDate (long amount);
      long addAmountDate (long ldate1, long ldate2);

//      void updateDate(long lvalue);
//      void updateDate(int hour, int min, int sec);
    private:
//      enum DateFormat{ dmy, myd, ymd}; 
      int jdays[2][13] = {
               { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 }
              ,{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
      };
      int days[13]  = { 0, 31, 28, 31,  30,  31,  30,  31,  31,  30,  31,  30,  31 };
      struct tm mtm;
      long ldate = 0l; 
 
      void calculateLongDate ();
      void calculateJulianDay(int year, int month, int day);
      void calculateJulianDay();
      bool isLeap            (int year);
      void validateDate      (const char* value, int fmt);
	  void validateDateValue (const char *value, std::vector<int> dt);
      void long2tm (long amount);
   };
}
