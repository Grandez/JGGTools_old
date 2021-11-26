#pragma once

#include <vector>
#include <string>
#include <memory>

using namespace std;

namespace NST {
class Date {
public:
   Date();
   Date(const Date& src);
   Date(string str);
   Date(const char *str);
   Date(int year, int month, int day);
   Date(long lvalue);
   struct tm*  getTM();
   long        asLong();
   int getYear();
   int getMonth();
   int getDay();
   int getJulianDay();

 //  string  toString(const char* fmt = "%X");
   char*   toChar  (char *ptr); // , size_t size, const char* fmt = "%X");
   Date& addYears        (int amount);
   Date& subtractYears   (int amount);
   Date& addMonths       (int amount);
   Date& subtractMonths  (int amount);
   Date& addDays         (int amount);
   Date& subtractDays    (int amount);
   Date& add             (const char *amount);
   Date& subtract        (const char *amount);
   Date& add             (string amount);
   Date& subtract        (string amount);
   Date& operator +=(Date&);
   Date& operator -=(Date&);
   Date  operator + (Date&);
   Date  operator - (Date&);

   bool operator==(Date&) ;
   bool operator!=(Date&) ;
   bool operator< (Date&) ;
   bool operator<=(Date&) ;
   bool operator> (Date&) ;
   bool operator>=(Date&) ;

   long  diffAsLong (Date& t);
   Date  diffAsDate (Date& t);
   
private:
   class DateBridge;
   unique_ptr<DateBridge, void (*)(DateBridge *)> _dtb;
};
}
