#include <regex>

#include "config.h" 
#include "sstring.hpp"
#include "exceptions.hpp"
#include "msg_locale.hpp"

#include "decimal.hpp"
#include "decimalImpl.hpp"

#ifdef _WIN32
#pragma warning( disable : 4996 )
#endif
using namespace std;

namespace NST {
/*
class Decimal::DecimalImpl {
public:
   DecimalImpl() {}
   DecimalImpl(const char* value)  {
        regex pat{"^[+-]?[0-9]*[\\.,]?[0-9]*$"};
		bool match = regex_search(value, pat);
		if (!match) throw new ToolsValueException(BAD_DECIMAL, value);
        vector<char *> data = (sstring(value)).tokenize("[\\.,]");
        if (data.size() > 2 || data.size() == 0) throw new ToolsValueException(BAD_DECIMAL, value);
        number = atol(data[0]);
        scale = 0;
        if (data.size() == 2) {
            scale  = (unsigned int) strlen(data[1]);
            number *= pow(10,scale);
            number += atol(data[1]);
        }
        // When using char *, those are allocated
        for (unsigned int i = 0; i < data.size(); i++) free(data[i]);
   }
   private:
      Decimal(long value, int scale); 
      int scale = 0;
      long number = 0; 
      char buffer[512] = {0x0}; // Common bufffer
      // Store values for binary operations 
      struct opers {
         long long number1;
         long long number2;
         int       scale1;
         int       scale2;
      };
      void    adjustScales(struct opers *);
      void    calculateScale(struct opers *);
      Decimal add        (Decimal& a, const Decimal&b);
      Decimal subtract   (Decimal& a, const Decimal& b);
      Decimal multiply   (Decimal& a, const Decimal& b);
      Decimal divide     (Decimal& a, const Decimal& b);
      sstring makeString (long long value, int scale);
      long long makeRound(int scale);
      void    setValues();  
   };


}
*/
   Decimal::Decimal(string value)     : _decimalImpl(new DecimalImpl(value), [](DecimalImpl *impl) { delete impl; })) {}
   Decimal::Decimal(const char* value)     : _decimalImpl(new DecimalImpl(value), [](DecimalImpl *impl) { delete impl; })) {}
   Decimal::Decimal(float       value) : _decimalImpl(new DecimalImpl(value), [](DecimalImpl *impl) { delete impl; })) {}
   Decimal::Decimal(double      value) : _decimalImpl(new DecimalImpl(value), [](DecimalImpl *impl) { delete impl; })) {}
   Decimal::Decimal(int         value) : _decimalImpl(new DecimalImpl(value), [](DecimalImpl *impl) { delete impl; })) {}
   Decimal::Decimal(long        value) : _decimalImpl(new DecimalImpl(value), [](DecimalImpl *impl) { delete impl; })) {}
   Decimal::Decimal(long value, int scale) : _decimalImpl(new DecimalImpl(value), [](DecimalImpl *impl) { delete impl; })) {}

   sstring Decimal::toString() { return _decimalImpl->toString(); }
   char* Decimal::toChar()     { return strdup(this->toString().toChar()); }
   sstring  Decimal::toStringRounded(int scale) {
       Decimal dec = round(scale);
       return dec.toString();
   }
   char* Decimal::toCharRounded(int scale) {
       return strdup(toStringRounded(scale).toChar());
   }
   float Decimal::toFloat() {
         float f = number;
         return f / (10 ^ scale);
   }
   double  Decimal::toDouble() {
         double d = number;
         return d / (10 ^ scale);
   }
   long Decimal::toFloor() {
        long value = number / (10 ^ scale);
        return value + 1;
   }
   long Decimal::toCeil() {
        return number / (10 ^ scale);
   }
   Decimal Decimal::round(int scale) {
       int remove = this->scale - scale;
       long p =  pow(10, remove - 1);
       p *= 5;  
       if (number < 0) p *= -1;
       long value = number + p;
       long p2 = pow(10, this->scale - scale);
       return Decimal(value / p2, scale);
   }
   Decimal Decimal::operator+  (const Decimal& b) { return add(*this, b); }
   Decimal Decimal::operator+= (const Decimal& b) {
      Decimal res = add(*this, b); 
      this->number = res.number;
      this->scale  = res.scale;
      return *this;
   }
   Decimal Decimal::operator-  (const Decimal& b) { return subtract(*this, b); }
   Decimal Decimal::operator-= (const Decimal& b) {
      Decimal res = add(*this, b); 
      this->number = res.number;
      this->scale  = res.scale;
      return *this;
   }
   Decimal Decimal::operator*  (const Decimal& b) { return multiply(*this, b); }
   Decimal Decimal::operator*= (const Decimal& b) {
      Decimal res  = multiply(*this, b); 
      this->number = res.number;
      this->scale  = res.scale;
      return *this;
   }
   Decimal Decimal::operator/  (const Decimal& b) { return divide(*this, b); }
   Decimal Decimal::operator/= (const Decimal& b) {
      Decimal res  = divide(*this, b); 
      this->number = res.number;
      this->scale  = res.scale;
      return *this;
   }
   bool Decimal::operator==(const Decimal& b) {
      struct opers beg = {this->number, b.number, this->scale, b.scale};
      adjustScales(&beg);
      return beg.number1 == beg.number2;
   }
   bool Decimal::operator!=(const Decimal& b) {
      struct opers beg = {this->number, b.number, this->scale, b.scale};
      adjustScales(&beg);
      return beg.number1 != beg.number2;
   }
   bool Decimal::operator<(const Decimal& b) {
      struct opers beg = {this->number, b.number, this->scale, b.scale};
      adjustScales(&beg);
      return beg.number1 < beg.number2;
   }
   bool Decimal::operator<=(const Decimal& b) {
      struct opers beg = {this->number, b.number, this->scale, b.scale};
      adjustScales(&beg);
      return beg.number1 <= beg.number2;
   }
  bool Decimal::operator>(const Decimal& b) {
      struct opers beg = {this->number, b.number, this->scale, b.scale};
      adjustScales(&beg);
      return beg.number1 > beg.number2;
  }
  bool Decimal::operator>=(const Decimal& b) {
      struct opers beg = {this->number, b.number, this->scale, b.scale};
      adjustScales(&beg);
      return beg.number1 >= beg.number2;
  }

   void Decimal::adjustScales(struct opers * op) {
      int diff = op->scale1 - op->scale2;
      if (diff < 0) op->number1 *= (10 * diff);
      if (diff > 0) op->number2 *= (10 * diff);
      op->scale1 += diff;
   }
   void Decimal::calculateScale(struct opers *op) {
       char m[64];
       int modulus = op->number1 % (10 ^ op->scale1);
       sprintf(m, "%d", modulus);
       op->scale1 = (unsigned int) strlen(m) - 1;
       op->number1 /= (10 ^ op->scale1);
   }
   Decimal Decimal::add(Decimal& a, const Decimal& b) {
      struct opers beg = {a.number, b.number, a.scale, b.scale};
      adjustScales(&beg);
      beg.number1 += beg.number2;
      calculateScale(&beg);
      return Decimal(beg.number1, beg.scale1);
   }
   Decimal Decimal::subtract(Decimal& a, const Decimal& b) {
      struct opers beg = {a.number, b.number, a.scale, b.scale};
      adjustScales(&beg);
      beg.number1 -= beg.number2;
      calculateScale(&beg);
      return Decimal(beg.number1, beg.scale1);
   }
   Decimal Decimal::multiply(Decimal& a, const Decimal& b) {
      struct opers beg = {a.number, b.number, a.scale, b.scale};
      adjustScales(&beg);
      beg.number1 *= beg.number2;
      beg.scale1 *= 2;
      calculateScale(&beg);
      return Decimal(beg.number1, beg.scale1);
   }
   Decimal Decimal::divide(Decimal& a, const Decimal& b) {
      struct opers beg = {a.number, b.number, a.scale, b.scale};
      adjustScales(&beg);
      beg.number1 /= beg.number2;
      beg.scale1 *= 2;
      calculateScale(&beg);
      return Decimal(beg.number1, beg.scale1);
   }
   sstring Decimal::makeString(long long value, int scale) {
       string str = to_string(value * 10);
       int idx = (int) str.length() - 2;
       for (int i = 0; i < scale; i++) str[idx + 1] = str[idx];
       str[idx] = '.';
       return sstring(str);
   }
   void Decimal::setValues() {
       vector<char *> toks = sstring(buffer).tokenize("\\.");
       unsigned int i = (int) strlen(toks[1]) - 1;
       while (i > -1 && toks[1][i] == '0') toks[1][i--] = 0x0;
       sstring str = sstring(toks[0]);
       str.append(toks[1]);
       scale = (int) strlen(toks[1]);
       number = stoll(str);
       for (i = 0; i < toks.size(); i++) free(toks[i]);
   }
   //TODO Check when number fit in float, double or not
}
