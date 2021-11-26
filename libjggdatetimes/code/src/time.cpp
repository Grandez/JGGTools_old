#include <string>
#include <time.h>
#include <regex>

#ifdef _WIN32
#pragma warning( disable : 4996 )
#endif
#include "config.h"

#include "timeImpl.hpp"
#include "time.hpp"

namespace NST {
   class Time::TimeBridge : public TimeImpl {
   public:
     TimeBridge()                           : TimeImpl(){}
     TimeBridge(const char *str)            : TimeImpl(str) {}
     TimeBridge(int hour, int min, int sec) : TimeImpl(hour, min, sec) {}
     TimeBridge(long lvalue)                : TimeImpl(lvalue) {}
//     string      toString (const char* fmt) { return DateTimeBase::toString(fmt); }
     char*   toChar   (char* ptr, size_t size)                   { return TimeImpl::toChar(ptr, size); }
     char*   format   (char *ptr, size_t size, const char *fmt)  { return TimeImpl::format(ptr, size, fmt); }
   };

   Time::Time()                : _dtb(new TimeBridge(),            [](TimeBridge *dtb) { delete dtb; }) {}  
   Time::Time(string str)      : _dtb(new TimeBridge(str.c_str()), [](TimeBridge *dtb) { delete dtb; }) {}  
   Time::Time(const char *str) : _dtb(new TimeBridge(str),         [](TimeBridge *dtb) { delete dtb; }) {}  
   Time::Time(long lvalue)     : _dtb(new TimeBridge(lvalue),      [](TimeBridge *dtb) { delete dtb; }) {}
   Time::Time(int hour, int min, int sec) : _dtb(new TimeBridge(hour, min, sec), [](TimeBridge *dtb) { delete dtb; }) {}  
   Time::Time(const Time& t) : Time(t._dtb->longValue()) {}

   int Time::getHour()     { return _dtb->getHour();    }
   int Time::getMinutes()  { return _dtb->getMinutes(); }
   int Time::getSeconds()  { return _dtb->getSeconds(); }

//   string     Time::toString(const char* fmt)                         { return _dtb->toString(fmt); }
   char*      Time::toChar  (char *ptr, size_t size)       { return _dtb->toChar(ptr, size); }
   char*      Time::format  (char *ptr, size_t size, const char *fmt)       { return _dtb->format(ptr, size, fmt); }
   struct tm* Time::getTM   ()                { return _dtb->getTM();     }
   long       Time::asLong  ()                { return _dtb->longValue(); }

   Time& Time::addHours        (int amount)         { _dtb->addHours   (amount)        ; return *this; }
   Time& Time::subtractHours   (int amount)         { _dtb->addHours   (amount * -1)   ; return *this; }
   Time& Time::addMinutes      (int amount)         { _dtb->addMinutes (amount)        ; return *this; }
   Time& Time::subtractMinutes (int amount)         { _dtb->addMinutes (amount * -1)   ; return *this; }
   Time& Time::addSeconds      (int amount)         { _dtb->addSeconds (amount)        ; return *this; }
   Time& Time::subtractSeconds (int amount)         { _dtb->addSeconds (amount * -1)   ; return *this; }
   Time& Time::add             (const char *amount) { _dtb->addTime    (amount)        ; return *this; }
   Time& Time::subtract        (const char *amount) { _dtb->addTime    (amount, false) ; return *this; }
   Time& Time::add             (string amount)      { return add(amount.c_str());      };
   Time& Time::subtract        (string amount)      { return subtract(amount.c_str()); };

   long  Time::diffAsLong      (Time& t)            { return t.asLong() - asLong();    };
   Time  Time::diffAsTime      (Time& t)            { 
      long src = asLong();
      long dst = t.asLong();
      if (src > dst) return Time(src - dst);  
      return Time(dst - src);
    };

   Time& Time::operator += (Time& t) { 
      _dtb->addAmountTime(t._dtb->longValue());
      return *this;
   };
   Time& Time::operator -= (Time& t) { 
      _dtb->addAmountTime(t._dtb->longValue() * -1);
      return *this;
   };
   Time  Time::operator +  (Time& t) { 
      long lvalue = _dtb->addAmountTime(_dtb->longValue(),t._dtb->longValue());
      return Time(lvalue);
   };
   Time  Time::operator -  (Time& t){ 
      long lvalue = _dtb->addAmountTime(_dtb->longValue(),t._dtb->longValue() * -1);
      return Time(lvalue);
   };
   bool  Time::operator==  (Time& t) { return   _dtb->longValue() == t._dtb->longValue();  }
   bool  Time::operator!=  (Time& t) { return !(_dtb->longValue() == t._dtb->longValue()); }
   bool  Time::operator<   (Time& t) { return   _dtb->longValue() <  t._dtb->longValue();  }
   bool  Time::operator<=  (Time& t) { return   _dtb->longValue() <= t._dtb->longValue();  }
   bool  Time::operator>   (Time& t) { return   _dtb->longValue() >  t._dtb->longValue();  }
   bool  Time::operator>=  (Time& t) { return !(_dtb->longValue() >= t._dtb->longValue()); }

}