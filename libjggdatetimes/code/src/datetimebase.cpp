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
#include "datetimebase.hpp"

#ifdef _WIN32
#pragma warning( disable : 4996 )
#endif

namespace NST {
   DateTimeBase::DateTimeBase() {
      time_t now = time(0);
      memcpy(&mtm, localtime(&now), sizeof(struct tm));
      setLongTime();
   }

   DateTimeBase::DateTimeBase(int type) : DateTimeBase() {
      this->type = type; 
   }
   DateTimeBase::DateTimeBase(int type, const char *str) : DateTimeBase(type) {
      validateString(type, str);
   }
   DateTimeBase::DateTimeBase(int type, int d1, int d2, int d3) : DateTimeBase(type) {
      switch (type) {
         case 2: validateTimeAndFillTM(d1,d2,d3); break;

      }
   }
   DateTimeBase::DateTimeBase(int type, long lvalue) : DateTimeBase(type) {
      switch (type) {
         case 2: long2time(lvalue); break;

      }
   }
   struct tm*  DateTimeBase::getTM()     { return &mtm; }
   long        DateTimeBase::timeValue() { 
       ltime = (mtm.tm_hour * 3600) + (mtm.tm_min * 60) + mtm.tm_sec;
       return ltime; 
   } 
/*
   string      DateTimeBase::toString (const char* fmt) {
       char buff[64];
       toChar(buff, 64, fmt);
       return string(buff);
   }
*/
   char* DateTimeBase::toChar   (char* buff, size_t size, const char *fmt) {
        strftime (buff, size, fmt, &mtm);
        return buff;
   }

/*
   string DateTimeBase::format (const char *fmt) {
     return string("");
   }
*/
// //////////////////////////////////
// TIME
// //////////////////////////////////
/*
   void DateTimeBase::fillTmTime(vector<int> toks) {
           mtm.tm_hour = toks[0];
           mtm.tm_min  = toks[1];
           mtm.tm_sec  = toks[2];
   }
*/
    void DateTimeBase::addHours      (int amount) { addAmountTime(amount * 3600); }
    void DateTimeBase::addMinutes    (int amount) { addAmountTime(amount *   60); }
    void DateTimeBase::addSeconds    (int amount) { addAmountTime(amount       ); }
    void DateTimeBase::addAmountTime (long amount) {
       ltime += amount;
       ltime %= 86400;  // 24:00:00
       if (ltime < 0) ltime += 86400;
       long2time(ltime);
    }
    long DateTimeBase::addAmountTime (long t1, long t2) {
       ltime = t1 + t2;
       ltime %= 86400;  // 24:00:00
       if (ltime < 0) ltime += 86400;
       return ltime;
    }


    void DateTimeBase::addTime(const char *amount, bool positive) {
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
/*
    string DateTimeBase::format(const char *fmt) {
       char data[27];
       strftime(data, 27, fmt, &mtm);
       return sstring(data); 
    }
*/
    void DateTimeBase::updateTime(long lvalue) {
       mtm.tm_hour =  lvalue / 3600; 
       lvalue %= 3600;
       mtm.tm_min =  lvalue / 60; 
       mtm.tm_sec =  lvalue % 60; 
    }
   void DateTimeBase::updateTime(int hour, int min, int sec) {
       mtm.tm_hour = hour;
       mtm.tm_min  = min;
       mtm.tm_sec  = sec;
   }

    void DateTimeBase::validateString(int type, const char *str) {
       switch (type) {
          case 2: validateTime(str); break;
       }

    }
	void  DateTimeBase::validateTime      (const char* value) {
		regex pat{ "^[0-9]{1,2}:[0-9]{1,2}:[0-9]{1,2}$" };
		bool match = regex_search(value, pat);
		if (!match) throw new ToolsCastException(BAD_TIME, value);
		vector<int> res = sstring(value).tokenizeNumber(":");
		if (res[0] < 0 || res[0] > 23) throw new ToolsCastException(BAD_TIME, value);
		for (int i = 1; i < 3; i++) 
			if (res[i] < 0 || res[i] > 59) throw new ToolsCastException(BAD_TIME, value);
        mtm.tm_hour = res[0];
        mtm.tm_min  = res[1];
        mtm.tm_sec  = res[2];
        setLongTime();
	}
    void DateTimeBase::validateDate(const char *str, int fmt) {
//	  time_base::dateorder d;
	  vector<int> res = sstring(str).tokenizeNumber("^[0-9]+[/-][0-9]+[/-][0-9]+$");
	  if (res.size() != 3) throw new ToolsValueException(BAD_DATE, str);
      fillTmDate(str, fmt);
      validateDateValues(str);
      // return &mtm;
    }
   void DateTimeBase::fillTmDate(const char *str, int fmt) {
       vector<int> res = sstring(str).tokenizeNumber((const char*)"[/-]");
       time_base::dateorder d;
	   d = (fmt == -1) ? use_facet<time_get<char>>(locale()).date_order() 
		               : static_cast<time_base::dateorder>(fmt);

	   switch (d) {
	       case time_base::dmy: mtm.tm_mday = res[0]; mtm.tm_mon = res[1] - 1; mtm.tm_year = res[2] - 1900; break;
	       case time_base::mdy: mtm.tm_mday = res[1]; mtm.tm_mon = res[0] - 1; mtm.tm_year = res[2] - 1900; break;
	       case time_base::ymd: mtm.tm_mday = res[2]; mtm.tm_mon = res[1] - 1; mtm.tm_year = res[2] - 1900; break;
	       case time_base::ydm: mtm.tm_mday = res[2]; mtm.tm_mon = res[2] - 1; mtm.tm_year = res[0] - 1900; break;
	       default:             mtm.tm_mday = res[0]; mtm.tm_mon = res[1] - 1; mtm.tm_year = res[2] - 1900;
	   }
   }
   bool  DateTimeBase::isLeap(int year) {
        if (year < 100) year += 1900; // Control full year or tm year
        if (year % 4)  return false;
		return (year % 400) ? false : true;
	}
   void  DateTimeBase::validateDateValues (const char *str) {
//		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if ( mtm.tm_year < 0)                        throw new ToolsValueException(BAD_DATE, str);
		if ((mtm.tm_mon  < 0) || (mtm.tm_mon  > 11)) throw new ToolsValueException(BAD_DATE, str);
		if ((mtm.tm_mday < 1) || (mtm.tm_mday > 31)) throw new ToolsValueException(BAD_DATE, str);
        if ( mtm.tm_mon != 2) {
             if (mtm.tm_mday > days[mtm.tm_mon])               throw new ToolsValueException(BAD_DATE, str);
             else if (isLeap(mtm.tm_year) && mtm.tm_mday > 29) throw new ToolsValueException(BAD_DATE, str);
        }
	}
    void DateTimeBase::addYears(int amount) {
       mtm.tm_year += amount;
       if (mtm.tm_mon == 1 && mtm.tm_mday > 27) {
           mtm.tm_mday = isLeap(mtm.tm_year + 1900) ? 29 : 28;
       }
    }
    void DateTimeBase::addMonths(int amount, bool last) {
       bool isLast = (mtm.tm_mday == days[mtm.tm_mon]);
       mtm.tm_mon += (amount + 1);
       int nyears = mtm.tm_mon / 12;
       mtm.tm_mon = (mtm.tm_mon & 12) - 1;
       mtm.tm_year += nyears;
       if (mtm.tm_mon == 1 && mtm.tm_mday > 27) {
           mtm.tm_mday = isLeap(mtm.tm_year + 1900) ? 29 : 28;
       }
       if (isLast) mtm.tm_mday = days[mtm.tm_mon];
    }
    void DateTimeBase::addDays(int amount) {
    }

    void DateTimeBase::addDate(char *amount, bool positive) {
       sstring str = sstring(amount).toUpper();
       string sz = str.toString(); 
       char * pEnd;
       long val = strtol (sz.c_str(), &pEnd, 10);
       if (!positive) val *= -1;
       if (strcmp(pEnd, "Y") == 0) {
           addYears(val);
       } else if (strcmp(pEnd, "M") == 0) {
           addMonths(val);
       } else if (strcmp(pEnd, "D") == 0) {
           addDays(val);
       } else {
           throw new ToolsValueException(BAD_FORMAT, amount);
       }
    }
    void DateTimeBase::validateTimeAndFillTM(int d1,int d2,int d3) {
        if (d1 < 0 || d1 > 23) throw new ToolsValueException(BAD_VALUE, d1);
        if (d2 < 0 || d2 > 59) throw new ToolsValueException(BAD_VALUE, d2);
        if (d3 < 0 || d3 > 59) throw new ToolsValueException(BAD_VALUE, d3);
        mtm.tm_hour = d1;
        mtm.tm_min  = d2;
        mtm.tm_sec  = d3;
        setLongTime();
    }
    void DateTimeBase::long2time(long lvalue) {
       this->ltime = lvalue;
       mtm.tm_hour = lvalue / 3600;
       long rem = lvalue % 3600;
       mtm.tm_min = rem / 60;
       mtm.tm_sec = rem % 60;
    }
    void DateTimeBase::setLongTime() {
      
        ltime = (mtm.tm_hour * 3600) + (mtm.tm_min * 60) + mtm.tm_sec;
    }
}






