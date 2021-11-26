#include <locale>

#ifdef _WIN32
#pragma warning( disable : 4996 )
#endif
#include "config.h"
#include "exceptions.hpp"
#include "sstring.hpp"
#include "datetimebase.hpp"
#include "date.hpp"
#include "time.hpp"

#include "datetime.hpp"


using namespace std;

namespace NST {
class DateTime::DateTimeImpl {
public:
   DateTimeImpl() {
   }
   DateTimeImpl(sstring str) {
      vector<sstring> toks = str.tokenize(sstring("[ \t]{1}"));
      if (toks.size() > 2) throw new ToolsValueException(BAD_DATETIME, str.c_str());
      if (toks.size() == 2) {
          mDate = new Date(toks[0], time_base::dateorder::ymd);
          mTime = new Time(toks[1]);
      }
   }
   ~DateTimeImpl() {
   };
   DateTimeBase *getDTB() { return &dtb; }
   sstring     toString() { return dtb.format("%F %X");         }
private:
    DateTimeBase dtb = DateTimeBase();
    Date *mDate = nullptr;
    Time *mTime = nullptr; 
};
   DateTime::DateTime () : impl_(new DateTimeImpl(), [](DateTimeImpl *impl) { delete impl; }) {}
   DateTime::DateTime (sstring str) : impl_(new DateTimeImpl(str), [](DateTimeImpl *impl) { delete impl; }) {}
   DateTime::DateTime (const char * str) : DateTime(sstring(str)) {}
   sstring     DateTime::toString() { return impl_->toString(); } // dtb.format("%F %X");         }
   const char* DateTime::toChar()   { return impl_->toChar(); }    // strdup((dtb.format("%F %X")).c_str()); }
   DateTime::~DateTime() = default;
   const char* toChar()   { return strdup((dtb.format("%F %X")).c_str()); }
int DateTime::getYear   () { return impl_->getDTB()->getTM()->tm_year + 1900; }
int DateTime::getMonth  () { return impl_->getDTB()->getTM()->tm_mon  +    1; }
int DateTime::getDay    () { return impl_->getDTB()->getTM()->tm_mday;        }
int DateTime::getHour   () { return impl_->getDTB()->getTM()->tm_hour;        }
int DateTime::getMin    () { return impl_->getDTB()->getTM()->tm_min;         }
int DateTime::getSecond () { return impl_->getDTB()->getTM()->tm_sec;         }


}


