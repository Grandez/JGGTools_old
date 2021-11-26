#include <ctime>
#include <cstring>

#include "config.h"

#include "sstring.hpp"
#include "exceptions.hpp"
#include "datetimebase.hpp"
#include <locale>

#ifdef _WIN32
#pragma warning( disable : 4996 )
#endif

namespace NST {
   DateTimeBase::DateTimeBase() {
      time_t now = time(0);
      memcpy(&mtm, localtime(&now), sizeof(struct tm));
   }
   DateTimeBase& DateTimeBase::setTM(struct tm *ptm) {
      memcpy(&mtm, ptm, sizeof(struct tm));
      return *this;
   }
   struct tm* DateTimeBase::getTM() { return &mtm; }
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
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if ( mtm.tm_year < 0)                        throw new ToolsValueException(BAD_DATE, str);
		if ((mtm.tm_mon  < 0) || (mtm.tm_mon  > 11)) throw new ToolsValueException(BAD_DATE, str);
		if ((mtm.tm_mday < 1) || (mtm.tm_mday > 31)) throw new ToolsValueException(BAD_DATE, str);
        if ( mtm.tm_mon != 2) {
             if (mtm.tm_mday > days[mtm.tm_mon])               throw new ToolsValueException(BAD_DATE, str);
             else if (isLeap(mtm.tm_year) && mtm.tm_mday > 29) throw new ToolsValueException(BAD_DATE, str);
        }
	}
   void DateTimeBase::validateTime(const char *str) {
//	  char strDate[11];
//	  time_base::dateorder d;
	  vector<int> toks= sstring(str).tokenizeNumber("^[0-9]+[:][0-9]+[:][0-9]+$");
	  if (toks.size() != 3) throw new ToolsValueException(BAD_TIME, str);
      fillTmTime(toks);
      validateTimeValues(str);
   }
   void DateTimeBase::fillTmTime(vector<int> toks) {
           mtm.tm_hour = toks[0];
           mtm.tm_min  = toks[1];
           mtm.tm_sec  = toks[2];
   }
   void DateTimeBase::validateTimeValues(sstring str) {
       if ((mtm.tm_hour < 0) || (mtm.tm_hour > 23) ||
           (mtm.tm_min  < 0) || (mtm.tm_min  > 59) ||
           (mtm.tm_sec  < 0) || (mtm.tm_sec  > 59))
            throw new ToolsValueException(BAD_TIME, str.c_str());
      }

    sstring DateTimeBase::format(const char *fmt) {
       char data[27];
       strftime(data, 27, fmt, &mtm);
       return sstring(data); 
    }


}
