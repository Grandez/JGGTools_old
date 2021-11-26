#include <string>
#include <time.h>
#include <regex>
#include <ctime>

#ifdef _WIN32
#pragma warning( disable : 4996 )
#endif
#include "config.h"

#include "datetimeImpl.hpp"
#include "datetime.hpp"

using namespace std;

namespace NST {
   class DateTime::DateTimeBridge : public DateTimeImpl {
   public:
     DateTimeBridge()                           : DateTimeImpl(){}
     DateTimeBridge(const char *str)            : DateTimeImpl(str) {}
     DateTimeBridge(std::time_t lvalue)              : DateTimeImpl(lvalue) {}
     DateTimeBridge(int year, int month, int day, int hour, int min, int sec) 
                                                : DateTimeImpl(year, month, day, hour, min, sec) {}

//     string      toString (const char* fmt) { return DateDateTimeBase::toString(fmt); }
     char*   toChar   (char* ptr, size_t size)                   { return DateTimeImpl::toChar(ptr, size); }
     char*   format   (char *ptr, size_t size, const char *fmt)  { return DateTimeImpl::format(ptr, size, fmt); }
   };

   DateTime::DateTime()                : _dtb(new DateTimeBridge(),            [](DateTimeBridge *dtb) { delete dtb; }) {}  
   DateTime::DateTime(string str)      : _dtb(new DateTimeBridge(str.c_str()), [](DateTimeBridge *dtb) { delete dtb; }) {}  
   DateTime::DateTime(const char *str) : _dtb(new DateTimeBridge(str),         [](DateTimeBridge *dtb) { delete dtb; }) {}  
   DateTime::DateTime(time_t lvalue)   : _dtb(new DateTimeBridge(lvalue),      [](DateTimeBridge *dtb) { delete dtb; }) {}
   DateTime::DateTime(int year, int month, int day, int hour, int min, int sec) 
                                       : _dtb(new DateTimeBridge(year, month, day, hour, min, sec), [](DateTimeBridge *dtb) { delete dtb; }) {}  
   DateTime::DateTime(const DateTime& t) : DateTime(t._dtb->timet()) {}

   int DateTime::getYear()      { return _dtb->getYear();      }
   int DateTime::getMonth()     { return _dtb->getMonth();     }
   int DateTime::getDay()       { return _dtb->getDay();       }
   int DateTime::getJulianDay() { return _dtb->getJulianDay(); }
   int DateTime::getHour()      { return _dtb->getHour();      }
   int DateTime::getMinutes()   { return _dtb->getMinutes();   }
   int DateTime::getSeconds()   { return _dtb->getSeconds();   }

//   string     DateTime::toString(const char* fmt)                         { return _dtb->toString(fmt); }
   char*      DateTime::toChar  (char *ptr, size_t size)       { return _dtb->toChar(ptr, size); }
   char*      DateTime::format  (char *ptr, size_t size, const char *fmt)       { return _dtb->format(ptr, size, fmt); }
   struct tm* DateTime::getTM   ()                { return _dtb->getTM();     }
   time_t     DateTime::timet()                  { return _dtb->timet(); }

   DateTime& DateTime::addHours        (int amount)         { _dtb->addHours   (amount)        ; return *this; }
   DateTime& DateTime::subtractHours   (int amount)         { _dtb->addHours   (amount * -1)   ; return *this; }
   DateTime& DateTime::addMinutes      (int amount)         { _dtb->addMinutes (amount)        ; return *this; }
   DateTime& DateTime::subtractMinutes (int amount)         { _dtb->addMinutes (amount * -1)   ; return *this; }
   DateTime& DateTime::addSeconds      (int amount)         { _dtb->addSeconds (amount)        ; return *this; }
   DateTime& DateTime::subtractSeconds (int amount)         { _dtb->addSeconds (amount * -1)   ; return *this; }
   DateTime& DateTime::add             (const char *amount) { _dtb->addDateTime    (amount)        ; return *this; }
   DateTime& DateTime::subtract        (const char *amount) { _dtb->addDateTime    (amount, false) ; return *this; }
   DateTime& DateTime::add             (string amount)      { return add(amount.c_str());      };
   DateTime& DateTime::subtract        (string amount)      { return subtract(amount.c_str()); };

   long  DateTime::diffAsLong      (DateTime& t)            { return t.timet() - timet();    };
   DateTime  DateTime::diffAsDateTime      (DateTime& t)            { 
      long src = timet();
      long dst = t.timet();
      if (src > dst) return DateTime(src - dst);  
      return DateTime(dst - src);
    };

   DateTime& DateTime::operator += (DateTime& t) { 
      _dtb->addAmountDateTime(t._dtb->timet());
      return *this;
   };
   DateTime& DateTime::operator -= (DateTime& t) { 
      _dtb->addAmountDateTime(t._dtb->timet() * -1);
      return *this;
   };
   DateTime  DateTime::operator +  (DateTime& t) { 
      long lvalue = _dtb->timet() + t.timet();
      return DateTime(lvalue);
   };
   DateTime  DateTime::operator -  (DateTime& t){ 
      long lvalue = _dtb->timet() - t.timet();
      return DateTime(lvalue);
   };
   DateTime& DateTime::operator +=(time_t t) { _dtb->addTimeT(t)     ; return *this; }
   DateTime& DateTime::operator -=(time_t t) { _dtb->addTimeT(t * -1); return *this; }
   DateTime  operator + (time_t t) { 
      long lvalue = _dtb->timet() + t;
      return DateTime(lvalue);
   };
   DateTime  operator - (time_t t){ 
      long lvalue = _dtb->timet() + t;
      return DateTime(lvalue);
   };
   DateTime& DateTime::operator +=(string str) { 
     addTime(str.c_str()); 
     return *this; 
    }
   DateTime& DateTime::operator -=(string str) {
      string tmp = str;
      if (str.at(0) != '+' && str.at(0) != '-') {
          tmp = string("-").append(str);
      }
      addTime(tmp.c_str()); 
      return *this;
   }
   DateTime  operator + (string);
   DateTime  operator - (string);
   DateTime& DateTime::operator +=(const char *str) {
      return *this;
   }
   DateTime& DateTime::operator -=(const char *str) {
      return *this;
   }
   DateTime  operator + (const char *str);
   DateTime  operator - (const char *str);

   bool  DateTime::operator==  (DateTime& t) { return   _dtb->timet() == t._dtb->timet();  }
   bool  DateTime::operator!=  (DateTime& t) { return !(_dtb->timet() == t._dtb->timet()); }
   bool  DateTime::operator<   (DateTime& t) { return   _dtb->timet() <  t._dtb->timet();  }
   bool  DateTime::operator<=  (DateTime& t) { return   _dtb->timet() <= t._dtb->timet();  }
   bool  DateTime::operator>   (DateTime& t) { return   _dtb->timet() >  t._dtb->timet();  }
   bool  DateTime::operator>=  (DateTime& t) { return !(_dtb->timet() >= t._dtb->timet()); }

}