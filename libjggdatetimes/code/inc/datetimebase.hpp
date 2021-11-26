#pragma once
#include <string>
#include <ctime>

#include "../../../include/config.h"

namespace NST {
   class DateTimeBase {
   public:   
      const enum class Type {TMS, DATETIME, DATE, TIME};
      DateTimeBase();
      DateTimeBase(int type);
      DateTimeBase(int type, long lvalue);
      DateTimeBase(int type, const char *str);
      DateTimeBase(int type, int d1, int d2, int d3);


      char*       toChar   (char* ptr, size_t size, const char *fmt);
      //string      toString (const char* fmt);
      struct tm* getTM();

      // Time
      long timeValue     ();
      void addHours      (int   amount);
      void addMinutes    (int   amount);
      void addSeconds    (int   amount);
      void addTime       (const char *amount, bool positive = true); 
      void addAmountTime (long amount);
      long addAmountTime (long ltime1, long ltime2);

      void updateTime(long lvalue);
      void updateTime(int hour, int min, int sec);

      // Date
      long dateValue     ();
      void addYears      (int   amount);
      void addMonths    (int   amount);
      void addDays    (int   amount);
      void addDate       (const char *amount, bool positive = true); 
      void addAmountDate (long amount);
      long addAmountDate (long ltime1, long ltime2);

      void updateDate(long lvalue);
      void updatedate(int hour, int min, int sec);
    private:
      struct tm mtm;
      long ltime = 0l; 
      long ldate = 0l; 
      int type = -1;
      void  validateString    (int type, const char * value);
	  void  validateDate      (const char* value);
	  const int days [12] = { 31, 28, 31,  30,  31,  30,  31,  31,  30,  31,  30,  31 };
      const int jdays[12] = { 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
      const int bdays[12] = { 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };
      void  fillTmDate(const char *str, int fmt);
      bool  isLeap(int year);
      void  validateDateValues (const char *str);

      void validateTimeAndFillTM(int d1,int d2,int d3);
      void long2time(long lvalue);
      void setLongTime();

/*
      void       validateDateValues (const char *str);
      void       validateTimeValues (string str);
      void       fillTmDate(const char *str, int fmt);
      void       fillTmTime(vector<int> toks);
*/
   };
}
