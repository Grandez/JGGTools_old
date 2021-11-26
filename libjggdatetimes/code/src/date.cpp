#include <string>
#include <time.h>
#include <regex>

#ifdef _WIN32
#pragma warning( disable : 4996 )
#endif
#include "config.h"

#include "dateImpl.hpp"
#include "date.hpp"

namespace NST {
   class Date::DateBridge : public DateImpl {
   public:
     DateBridge()                           : DateImpl(){}
     DateBridge(const char *str)            : DateImpl(str) {}
     DateBridge(int year,int month,int day) : DateImpl(year, month, day) {}
     DateBridge(long lvalue)                : DateImpl(lvalue) {}
//     string      toString (const char* fmt) { return DateDateBase::toString(fmt); }
//     char*       toChar   (char* ptr) { return DateImpl::toChar(ptr);  }

   };

   Date::Date()                : _dtb(new DateBridge(),            [](DateBridge *dtb) { delete dtb; }) {}  
   Date::Date(string str)      : _dtb(new DateBridge(str.c_str()), [](DateBridge *dtb) { delete dtb; }) {}  
   Date::Date(const char *str) : _dtb(new DateBridge(str),         [](DateBridge *dtb) { delete dtb; }) {}  
   Date::Date(long lvalue)     : _dtb(new DateBridge(lvalue),      [](DateBridge *dtb) { delete dtb; }) {}
   Date::Date(const Date& t)   : Date(t._dtb->longValue()) {}
   Date::Date(int year,int month,int day) : _dtb(new DateBridge(year, month, day), [](DateBridge *dtb) { delete dtb; }) {}  
//   string     Date::toString(const char* fmt)                         { return _dtb->toString(fmt); }
   char*      Date::toChar  (char *ptr)       { return _dtb->toChar(ptr);    }
   struct tm* Date::getTM   (struct tm* ptm)  { return _dtb->getTM(ptm);     }
   long       Date::asLong  ()                { return _dtb->longValue();    }
   int        Date::getYear ()                { return _dtb->getYear();      }
   int        Date::getMonth()                { return _dtb->getMonth();     }
   int        Date::getDay  ()                { return _dtb->getDay();       }
   int        Date::getJulianDay ()           { return _dtb->getJulianDay(); }
   Date& Date::addYears        (int amount)         { _dtb->addYears  (amount)        ; return *this; }
   Date& Date::subtractYears   (int amount)         { _dtb->addYears  (amount * -1)   ; return *this; }
   Date& Date::addMonths       (int amount)         { _dtb->addMonths (amount)        ; return *this; }
   Date& Date::subtractMonths  (int amount)         { _dtb->addMonths (amount * -1)   ; return *this; }
   Date& Date::addDays         (int amount)         { _dtb->addDays   (amount)        ; return *this; }
   Date& Date::subtractDays    (int amount)         { _dtb->addDays   (amount * -1)   ; return *this; }
   Date& Date::add             (const char *amount) { _dtb->addDate   (amount)        ; return *this; }
   Date& Date::subtract        (const char *amount) { _dtb->addDate   (amount, false) ; return *this; }
   Date& Date::add             (string amount)      { return add(amount.c_str());      };
   Date& Date::subtract        (string amount)      { return subtract(amount.c_str()); };

   long  Date::diffAsLong      (Date& t)            { return t.asLong() - asLong();    };
   Date  Date::diffAsDate      (Date& t)            { 
      long src = asLong();
      long dst = t.asLong();
      if (src > dst) return Date(src - dst);  
      return Date(dst - src);
    };

   Date& Date::operator += (Date& t) { 
      _dtb->addAmountDate(t._dtb->longValue());
      return *this;
   };
   Date& Date::operator -= (Date& t) { 
      _dtb->addAmountDate(t._dtb->longValue() * -1);
      return *this;
   };
   Date  Date::operator +  (Date& t) { 
      long lvalue = _dtb->addAmountDate(_dtb->longValue(),t._dtb->longValue());
      return Date(lvalue);
   };
   Date  Date::operator -  (Date& t){ 
      long lvalue = _dtb->addAmountDate(_dtb->longValue(),t._dtb->longValue() * -1);
      return Date(lvalue);
   };
   bool  Date::operator==  (Date& t) { return   _dtb->longValue() == t._dtb->longValue();  }
   bool  Date::operator!=  (Date& t) { return !(_dtb->longValue() == t._dtb->longValue()); }
   bool  Date::operator<   (Date& t) { return   _dtb->longValue() <  t._dtb->longValue();  }
   bool  Date::operator<=  (Date& t) { return   _dtb->longValue() <= t._dtb->longValue();  }
   bool  Date::operator>   (Date& t) { return   _dtb->longValue() >  t._dtb->longValue();  }
   bool  Date::operator>=  (Date& t) { return !(_dtb->longValue() >= t._dtb->longValue()); }

}