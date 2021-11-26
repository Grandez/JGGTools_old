#pragma once

#include <vector>
#include <string>

using namespace std;

namespace NST {
class Time {
public:
   Time();
   Time(const Time& src);
   Time(string str);
   Time(const char *str);
   Time(int hour, int min, int sec);
   Time(long lvalue);
   struct tm*  getTM();
   long        asLong();
   int         getHour();
   int         getMinutes();
   int         getSeconds();
 //  string  toString(const char* fmt = "%X");
   char*   toChar  (char *ptr, size_t size); // , size_t size, const char* fmt = "%X");
   char*   format  (char *ptr, size_t size, const char *fmt);
   Time& addHours        (int amount);
   Time& subtractHours   (int amount);
   Time& addMinutes      (int amount);
   Time& subtractMinutes (int amount);
   Time& addSeconds      (int amount);
   Time& subtractSeconds (int amount);
   Time& add             (const char *amount);
   Time& subtract        (const char *amount);
   Time& add             (string amount);
   Time& subtract        (string amount);
   Time& operator +=(Time&);
   Time& operator -=(Time&);
   Time  operator + (Time&);
   Time  operator - (Time&);

   bool operator==(Time&) ;
   bool operator!=(Time&) ;
   bool operator< (Time&) ;
   bool operator<=(Time&) ;
   bool operator> (Time&) ;
   bool operator>=(Time&) ;

   long  diffAsLong (Time& t);
   Time  diffAsTime (Time& t);
   
private:
   class TimeBridge;
   unique_ptr<TimeBridge, void (*)(TimeBridge *)> _dtb;
};
}
