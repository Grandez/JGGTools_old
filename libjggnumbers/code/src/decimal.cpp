#include <regex>

#include "config.h" 
#include "sstring.hpp"
#include "exceptions.hpp"
#include "msg_locale.hpp"

#include "decimalImpl.hpp"
#include "decimal.hpp"

#ifdef _WIN32
#pragma warning( disable : 4996 )
#endif
using namespace std;

namespace NST {
   Decimal::Decimal(string      value)     : _decimalImpl(new DecimalImpl(value), [](DecimalImpl *impl) { delete impl; }) {}
   Decimal::Decimal(const char* value)     : _decimalImpl(new DecimalImpl(value), [](DecimalImpl *impl) { delete impl; }) {}
   Decimal::Decimal(float       value)     : _decimalImpl(new DecimalImpl(value), [](DecimalImpl *impl) { delete impl; }) {}
   Decimal::Decimal(double      value)     : _decimalImpl(new DecimalImpl(value), [](DecimalImpl *impl) { delete impl; }) {}
   Decimal::Decimal(int         value)     : _decimalImpl(new DecimalImpl(value), [](DecimalImpl *impl) { delete impl; }) {}
   Decimal::Decimal(long        value)     : _decimalImpl(new DecimalImpl(value), [](DecimalImpl *impl) { delete impl; }) {}
   Decimal::Decimal(long value, int scale) : _decimalImpl(new DecimalImpl(value, scale), [](DecimalImpl *impl) { delete impl; }) {}
   long Decimal::getIntPart() { return _decimalImpl->getIntPart(); } 
   long Decimal::getDecPart() { return _decimalImpl->getDecPart(); } 

   string  Decimal::toString() { return _decimalImpl->toString(); }
   float   Decimal::toFloat () { return _decimalImpl->toFloat(); }
   double  Decimal::toDouble() { return _decimalImpl->toDouble(); }
   long    Decimal::toFloor () { return _decimalImpl->toFloor(); }
   long    Decimal::toCeil  () { return _decimalImpl->toCeil(); }
   char*   Decimal::toChar  () { return strdup(this->toString().c_str()); }

   string  Decimal::toStringRounded (int scale) { return _decimalImpl->toStringRounded(scale); }
   char*   Decimal::toCharRounded   (int scale) { return _decimalImpl->toCharRounded(scale);   }

   Decimal Decimal::round(int scale) { return _decimalImpl->round(scale);   }
   Decimal Decimal::operator+  (Decimal& b) { return _decimalImpl->add     (*this, b);  }
   Decimal Decimal::operator+= (Decimal& b) { return _decimalImpl->add     (*this, b); }
   Decimal Decimal::operator-  (Decimal& b) { return _decimalImpl->subtract(*this, b); }
   Decimal Decimal::operator-= (Decimal& b) { return _decimalImpl->subtract(*this, b); }
   Decimal Decimal::operator*  (Decimal& b) { return _decimalImpl->multiply(*this, b); }
   Decimal Decimal::operator*= (Decimal& b) { return _decimalImpl->multiply(*this, b); }
   Decimal Decimal::operator/  (Decimal& b) { return _decimalImpl->divide  (*this, b); }
   Decimal Decimal::operator/= (Decimal& b) { return _decimalImpl->divide  (*this, b); }
   Decimal Decimal::operator +=(long   l) {Decimal d(l); return _decimalImpl->add     (*this, d); }
   Decimal Decimal::operator -=(long   l) {Decimal d(l); return _decimalImpl->subtract(*this, d); }
   Decimal Decimal::operator *=(long   l) {Decimal d(l); return _decimalImpl->multiply(*this, d); }
   Decimal Decimal::operator /=(long   l) {Decimal d(l); return _decimalImpl->divide  (*this, d); }
   Decimal Decimal::operator +=(double v) {Decimal d(v); return _decimalImpl->add     (*this, d); }
   Decimal Decimal::operator -=(double v) {Decimal d(v); return _decimalImpl->subtract(*this, d); }
   Decimal Decimal::operator *=(double v) {Decimal d(v); return _decimalImpl->multiply(*this, d); }
   Decimal Decimal::operator /=(double v) {Decimal d(v); return _decimalImpl->divide  (*this, d); }

   Decimal Decimal::operator+(long   v) { Decimal d(v); return _decimalImpl->add     (*this, d); }
   Decimal Decimal::operator+(double v) { Decimal d(v); return _decimalImpl->add     (*this, d); }
   Decimal Decimal::operator-(long   v) { Decimal d(v); return _decimalImpl->subtract(*this, d); }
   Decimal Decimal::operator-(double v) { Decimal d(v); return _decimalImpl->subtract(*this, d); }
   Decimal Decimal::operator*(long   v) { Decimal d(v); return _decimalImpl->multiply(*this, d); }
   Decimal Decimal::operator*(double v) { Decimal d(v); return _decimalImpl->multiply(*this, d); }
   Decimal Decimal::operator/(long   v) { Decimal d(v); return _decimalImpl->divide  (*this, d); }
   Decimal Decimal::operator/(double v) { Decimal d(v); return _decimalImpl->divide  (*this, d); }

   bool Decimal::operator==(Decimal& b) { return  _decimalImpl->equal(b); }
   bool Decimal::operator!=(Decimal& b) { return !_decimalImpl->equal(b); }
   bool Decimal::operator< (Decimal& b) { return  _decimalImpl->lt(b);    }
   bool Decimal::operator<=(Decimal& b) { return  _decimalImpl->le(b);    }
   bool Decimal::operator> (Decimal& b) { return  _decimalImpl->gt(b);    }
   bool Decimal::operator>=(Decimal& b) { return  _decimalImpl->ge(b);    }

   Decimal Decimal::add     (Decimal& a, Decimal& b) { return  _decimalImpl->add(a, b);      }
   Decimal Decimal::subtract(Decimal& a, Decimal& b) { return  _decimalImpl->subtract(a, b); }
   Decimal Decimal::multiply(Decimal& a, Decimal& b) { return  _decimalImpl->multiply(a, b); }
   Decimal Decimal::divide  (Decimal& a, Decimal& b) { return  _decimalImpl->divide(a, b);   }
   //TODO Check when number fit in float, double or not

}
