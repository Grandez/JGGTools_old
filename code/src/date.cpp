#include <time.h>
#include <regex>
#include <cstring>

#include "config.h" 

#include "sstring.hpp"
#include "date.hpp"
#include "exceptions.hpp"

#ifdef _WIN32
#pragma warning( disable : 4996 )
#endif
using namespace std;

namespace NST {
class Date::DateImpl {
public:
   DateImpl() {}
   DateImpl(sstring str, int fmt) {
       free(ptm);
       dtb.validateDate(str.c_str(), fmt);
   }
   int         getYear()  { return ptm->tm_year + 1900; }
   int         getMonth() { return ptm->tm_mon  + 1;    }
   int         getDay()   { return ptm->tm_mday;        }
   struct tm*  getTM() { return ptm; }
   sstring     toString(const char *fmt) { return dtb.format(fmt);         }
   const char* toChar  (const char *fmt) { return strdup(dtb.format(fmt).c_str()); }
//   ~DateImpl() { free(ptm); }
private:
   DateTimeBase dtb = DateTimeBase();
   struct tm *ptm = dtb.getTM();
};
Date::Date()                 : impl_(new DateImpl()) {}
Date::Date(const Date& src) {
//      struct tm *tmp = src.ptm;
//      memcpy(ptm,src.getTM(),sizeof(struct tm)); 
}
   Date::Date(sstring str, int fmt)  : impl_(new DateImpl(str, fmt)) {}
//       free(ptm);
//       dtb.validateDate(str.c_str(), fmt);
//   }
   Date::Date(const char *str, int fmt) : Date (sstring(str), fmt) {}
   int         Date::getYear()  { return impl_->getYear(); } // ptm->tm_year + 1900; }
   int         Date::getMonth() { return impl_->getMonth(); } //ptm->tm_mon  + 1;    }
   int         Date::getDay()   { return impl_->getDay(); } //ptm->tm_mday;        }
   struct tm*  Date::getTM() { return impl_->getTM(); }
   sstring     Date::toString(const char *fmt) { return impl_->toString(fmt); } //dtb.format(fmt);         }
   const char* Date::toChar  (const char *fmt) { return impl_->toChar(fmt);   } //dtb.format(fmt).c_str(); }
               Date::~Date() = default;
}