/**
* datetime es la clase base
*  manejamos time_t
*/
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <locale>
#include <regex>
#include <string>

#include "config.h"
#include "sstring.hpp"
#include "msg_locale.hpp"
#include "exceptions.hpp"
#include "date.hpp"
//#include "time.hpp"
#include "datetimeImpl.hpp"

#ifdef _WIN32
#pragma warning( disable : 4996 )
#endif
#include <chrono>

using namespace std;

namespace NST {
   DateTimeImpl::DateTimeImpl()                {
      time_t now = time(0);
      memcpy(&mtm, localtime(&now), sizeof(struct tm));
      lvalue = now;
   }
   DateTimeImpl::DateTimeImpl(const char *str) {
      regex pat{ "^[0-9]{4}[/-]{1}[0-9]{1,2}[/-]{1}[0-9]{1,2}[/-]{1}[/- ]{1}[0-9]{1,2}:[0-9]{1,2}:[0-9]{1,2}$" };
	  bool match = regex_search(str, pat);
	  if (!match) throw new ToolsCastException(BAD_DATETIME, str);
	  vector<int> res = sstring(str).tokenizeNumber("[/-:]");
      date = new Date(res[0], res[1], res[2]);
      time = new Time(res[3], res[4], res[5]);
      fillTM();
   }
   DateTimeImpl::DateTimeImpl(int year, int month, int day, int hour, int minutes, int seconds) : DateTimeImpl() {
        date = new Date(year, month, day);
        time = new Time(hour, minutes, seconds);
        fillTM();
   }
   DateTimeImpl::DateTimeImpl(time_t lvalue) : DateTimeImpl() { 
       lvalue = lvalue;
       const time_t *tt = &lvalue;
       memcpy(&mtm, localtime(tt), sizeof(struct tm));
   }
   char* DateTimeImpl::toChar   (char *ptr, size_t size) { return format(ptr, size, "%X"); }
   char* DateTimeImpl::format   (char* buff, size_t size, const char *fmt) {
        strftime (buff, size, fmt, &mtm);
        return buff;
   }
   int DateTimeImpl::getYear()      { return mtm.tm_year + 1900; }
   int DateTimeImpl::getMonth()     { return mtm.tm_mon  +    1; }
   int DateTimeImpl::getDay()       { return mtm.tm_mday;        }
   int DateTimeImpl::getJulianDay() { return mtm.tm_yday;        }
   int DateTimeImpl::getHour()      { return mtm.tm_hour;        }
   int DateTimeImpl::getMinutes()   { return mtm.tm_min;         }
   int DateTimeImpl::getSeconds()   { return mtm.tm_sec;         }

   struct tm*  DateTimeImpl::getTM()     { return &mtm;  }
   time_t        DateTimeImpl::timet() { return lvalue; }

   void DateTimeImpl::addHours      (int amount)  { addAmountDateTime(amount * 3600); }
   void DateTimeImpl::addMinutes    (int amount)  { addAmountDateTime(amount *   60); }
   void DateTimeImpl::addSeconds    (int amount)  { addAmountDateTime(amount       ); }
   void DateTimeImpl::addAmountDateTime (time_t amount) {
       lvalue += amount;
       memcpy(&mtm, localtime(&lvalue), sizeof(struct tm));
    }
   time_t DateTimeImpl::addAmountDateTime (time_t t1, time_t t2) {
       lvalue = t1 + t2;
    }
   void DateTimeImpl::addDateTime       (const char *amount, bool positive) {
       sstring str = sstring(amount).toUpper();
       string sz = str.toString(); 
       char * pEnd;
       long val = strtol (sz.c_str(), &pEnd, 10);
       if (!positive) val *= -1;
       if (strcmp(pEnd, "H") == 0) {
           addHours(val);
       } else if (strcmp(pEnd, "M") == 0) {
           addMinutes(val);
       } else if (strcmp(pEnd, "S") == 0) {
           addSeconds(val);
       } else {
           throw new ToolsValueException(BAD_FORMAT, amount);
       }
    }
    void DateTimeImpl::addTimeT (time_t t) {
        lvalue += t;
        memcpy(&mtm, localtime(&now), sizeof(struct tm));
    } 
    void DateTimeImpl::updateDateTime(unsigned long lvalue) {
       mtm.tm_hour =  lvalue / 3600; 
       lvalue %= 3600;
       mtm.tm_min =  lvalue / 60; 
       mtm.tm_sec =  lvalue % 60; 
    }
   void DateTimeImpl::updateDateTime(int hour, int min, int sec) {
       mtm.tm_hour = hour;
       mtm.tm_min  = min;
       mtm.tm_sec  = sec;
   }
    void DateTimeImpl::fillTM() {
      struct tm *tmDate = date->getTM();
      struct tm *tmTime = time->getTM();
      memcpy(&mtm, tmDate, sizeof(struct tm));
      mtm.tm_hour = tmTime->tm_hour;
      mtm.tm_min  = tmTime->tm_min;
      mtm.tm_sec  = tmTime->tm_sec;
      lvalue = mktime(&mtm);
    }
    void DateTimeImpl::addString  (long amount, char type) { 
         char szType[2] = " ";
         szType[0] = type;
         szType[1] = 0x0;
         switch (type) { 
             case 'Y': break;
             case 'M': break;
             case 'D': break;
             case 'h': break;
             case 'm': break;
             case 's': break;
             default:  throw new ToolsValueException(szType);
         }
         if (type == 0x0 || strlen(type) > 1) throw new ToolsValueException(type);
         addString(amount, type[0]); 
    }

    void DateTimeImpl::addString  (long amount, const char *type) { 
         if (type == 0x0 || strlen(type) > 1) throw new ToolsValueException(type);
         addString(amount, type[0]); 
    }
    void DateTimeImpl::addString  (long amount, string type) { addString(amount, type.c_str()); }
}
