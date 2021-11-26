#pragma once

#include <vector>
#include <string>

using namespace std;

namespace NST {
class DateTime {
public:
   DateTime();
   DateTime(const DateTime& src);
   DateTime(string str);
   DateTime(const char *str);
   DateTime(int year, int month, int day, int hour, int min, int sec);
   DateTime(time_t lvalue);
   struct tm*  getTM();
   time_t      timet();
   int         getYear     ();
   int         getMonth    ();
   int         getDay      ();
   int         getJulianDay();
   int         getHour     ();
   int         getMinutes  ();
   int         getSeconds  ();

 //  string  toString(const char* fmt = "%X");
   char*   toChar  (char *ptr, size_t size); // , size_t size, const char* fmt = "%X");
   char*   format  (char *ptr, size_t size, const char *fmt);
   DateTime& addHours        (int amount);
   DateTime& subtractHours   (int amount);
   DateTime& addMinutes      (int amount);
   DateTime& subtractMinutes (int amount);
   DateTime& addSeconds      (int amount);
   DateTime& subtractSeconds (int amount);
   DateTime& add             (const char *amount);
   DateTime& subtract        (const char *amount);
   DateTime& add             (string amount);
   DateTime& subtract        (string amount);
   DateTime& operator +=(DateTime&);
   DateTime& operator -=(DateTime&);
   DateTime  operator + (DateTime&);
   DateTime  operator - (DateTime&);
   DateTime& operator +=(time_t);
   DateTime& operator -=(time_t);
   DateTime  operator + (time_t);
   DateTime  operator - (time_t);
   DateTime& operator +=(string);
   DateTime& operator -=(string);
   DateTime  operator + (string);
   DateTime  operator - (string);
   DateTime& operator +=(const char *);
   DateTime& operator -=(const char *);
   DateTime  operator + (const char *);
   DateTime  operator - (const char *);

   bool operator==(DateTime&) ;
   bool operator!=(DateTime&) ;
   bool operator< (DateTime&) ;
   bool operator<=(DateTime&) ;
   bool operator> (DateTime&) ;
   bool operator>=(DateTime&) ;

   long  diffAsLong (DateTime& t);
   DateTime  diffAsDateTime (DateTime& t);
   
private:
   class DateTimeBridge;
   unique_ptr<DateTimeBridge, void (*)(DateTimeBridge *)> _dtb;
};
}
