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
#include "timeImpl.hpp"

#ifdef _WIN32
#pragma warning( disable : 4996 )
#endif

namespace NST {
   TimeImpl::TimeImpl()                {
      time_t now = time(0);
      memcpy(&mtm, localtime(&now), sizeof(struct tm));
      setLongTime();
   }
   TimeImpl::TimeImpl(const char *str) {
      regex pat{ "^[0-9]{1,2}:[0-9]{1,2}:[0-9]{1,2}$" };
	  bool match = regex_search(str, pat);
	  if (!match) throw new ToolsCastException(BAD_TIME, str);
	  vector<int> res = sstring(str).tokenizeNumber(":");
	  if (res[0] < 0 || res[0] > 23) throw new ToolsCastException(BAD_TIME, str);
	  for (int i = 1; i < 3; i++) {
		  if (res[i] < 0 || res[i] > 59) throw new ToolsCastException(BAD_TIME, str);
      }
      ltime = (res[0] * 3600) + (res[1] * 60) + res[2];
      setStructTm();
   }
   TimeImpl::TimeImpl(int hour, int minutes, int seconds) : TimeImpl() {
        if (hour < 0    || hour > 23)    throw new ToolsValueException(BAD_VALUE, hour);
        if (minutes < 0 || minutes > 59) throw new ToolsValueException(BAD_VALUE, minutes);
        if (seconds < 0 || seconds > 59) throw new ToolsValueException(BAD_VALUE, seconds);
        ltime = (hour * 3600) + (minutes * 60) + seconds;
        setStructTm();
   }
   TimeImpl::TimeImpl(long lvalue) : TimeImpl() { setLongTime(lvalue); }
   char* TimeImpl::toChar   (char *ptr, size_t size) { return format(ptr, size, "%X"); }
   char* TimeImpl::format   (char* buff, size_t size, const char *fmt) {
        strftime (buff, size, fmt, &mtm);
        return buff;
   }
   int TimeImpl::getHour()     { return mtm.tm_hour; }
   int TimeImpl::getMinutes()  { return mtm.tm_min;  }
   int TimeImpl::getSeconds()  { return mtm.tm_sec;  }

   struct tm*  TimeImpl::getTM()     { return &mtm;  }
   long        TimeImpl::longValue() { return ltime; }

   void TimeImpl::addHours      (int amount)  { addAmountTime(amount * 3600); }
   void TimeImpl::addMinutes    (int amount)  { addAmountTime(amount *   60); }
   void TimeImpl::addSeconds    (int amount)  { addAmountTime(amount       ); }
   void TimeImpl::addAmountTime (long amount) {
       ltime += amount;
       ltime %= 86400;  // 24:00:00
       if (ltime < 0) ltime += 86400;
       setStructTm();
    }
   long TimeImpl::addAmountTime (long t1, long t2) {
       ltime = t1 + t2;
       ltime %= 86400;  // 24:00:00
       if (ltime < 0) ltime += 86400;
       return ltime;
    }
   void TimeImpl::addTime       (const char *amount, bool positive) {
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
    void TimeImpl::updateTime(long lvalue) {
       mtm.tm_hour =  lvalue / 3600; 
       lvalue %= 3600;
       mtm.tm_min =  lvalue / 60; 
       mtm.tm_sec =  lvalue % 60; 
    }
   void TimeImpl::updateTime(int hour, int min, int sec) {
       mtm.tm_hour = hour;
       mtm.tm_min  = min;
       mtm.tm_sec  = sec;
   }

    void TimeImpl::setStructTm() {
       mtm.tm_hour = ltime / 3600;
       long rem = ltime % 3600;
       mtm.tm_min = rem / 60;
       mtm.tm_sec = rem % 60;
    }
    void TimeImpl::setLongTime(long lvalue) {
       this->ltime = lvalue % 86400;
    }
    void TimeImpl::setLongTime() {
        ltime = (mtm.tm_hour * 3600) + (mtm.tm_min * 60) + mtm.tm_sec;
    }
}






