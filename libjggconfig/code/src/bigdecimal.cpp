#include <regex>

#include "config.h" 
#include "exceptions.hpp"
#include "bigdecimal.hpp"
#include "msg_locale.hpp"
#include "sstring.hpp"

#ifdef _WIN32
#pragma warning( disable : 4996 )
#endif
using namespace std;

namespace NST {
   BigDecimal::BigDecimal(const char* value)  {
        regex pat{"^[+-]?[0-9]*[\\.,]?[0-9]*$"};
		bool match = regex_search(value, pat);
		if (!match) throw new ToolsValueException(BAD_DECIMAL, value);
        vector<char *> data = (sstring(value)).tokenize("[\\.,]");
        if (data.size() > 2 || data.size() == 0) throw new ToolsValueException(BAD_DECIMAL, value);
        number = atoll(data[0]);
        scale = 0;
        if (data.size() == 2) {
            scale  = (unsigned int) strlen(data[1]);
            number *= pow(10,scale);
            number += atol(data[1]);
        }
        // When using char *, those are allocated
        for (int i = 0; i < data.size(); i++) free(data[i]);
   }
   BigDecimal::BigDecimal(float       value) { 
       sprintf(buffer, "%f", value); 
       setValues();
   }
   BigDecimal::BigDecimal(double      value) { 
       sprintf(buffer, "%lf", value); 
       setValues();
   }
   BigDecimal::BigDecimal(long double value) { 
       sprintf(buffer, "%Lf", value); 
       setValues();
    }
   BigDecimal::BigDecimal(int value)         { 
this->number = value;            }
   BigDecimal::BigDecimal(long value)        { 
this->number = value;            }
   BigDecimal::BigDecimal(long long value)   { 
this->number = value;            }

   BigDecimal::BigDecimal(long long value, int scale) {
         this->number = value;
         this->scale  = scale;
   }
   string BigDecimal::toString() {
       string str = to_string(number);
       int len = (int) str.length();
       int diff = len - scale;
       string str1 = str.substr(0, diff);
       if (str1.length() == 0) str1 = string("0");
       if (str1.length() == 1 && str1[0] == '-') str1 = string("-0");
       string str2 = str.substr(diff, len);
       if (str2.length() == 0) return str1;
       return str1.append(".").append(str2);
   }
   char* BigDecimal::toChar() {
      return strdup((char *) this->toString().c_str());
   }
   string  BigDecimal::toStringRounded(int scale) {
       BigDecimal dec = round(scale);
       return dec.toString();
   }
   char* BigDecimal::toCharRounded(int scale) {
       return strdup(toStringRounded(scale).c_str());
   }
   float BigDecimal::toFloat() {
         float f = number;
         return f / (10 ^ scale);
   }
   double  BigDecimal::toDouble() {
         double d = number;
         return d / (10 ^ scale);
   }
   long double BigDecimal::toLongDouble() {
         long double ld = number;
         return ld / (10 ^ scale);
   }
   long BigDecimal::toFloor() {
        long value = number / (10 ^ scale);
        return value + 1;
   }
   long BigDecimal::toCeil() {
        return number / (10 ^ scale);
   }
   BigDecimal BigDecimal::round(int scale) {
       int remove = this->scale - scale;
       long p =  pow(10, remove - 1);
       p *= 5;  
       if (number < 0) p *= -1;
       long long value = number + p;
       long p2 = pow(10, this->scale - scale);
       return BigDecimal(value / p2, scale);
   }
   BigDecimal BigDecimal::operator+  (const BigDecimal& b) { return add(*this, b); }
   BigDecimal BigDecimal::operator+= (const BigDecimal& b) {
      BigDecimal res = add(*this, b); 
      this->number = res.number;
      this->scale  = res.scale;
      return *this;
   }
   BigDecimal BigDecimal::operator-  (const BigDecimal& b) { return subtract(*this, b); }
   BigDecimal BigDecimal::operator-= (const BigDecimal& b) {
      BigDecimal res = add(*this, b); 
      this->number = res.number;
      this->scale  = res.scale;
      return *this;
   }
   BigDecimal BigDecimal::operator*  (const BigDecimal& b) { return multiply(*this, b); }
   BigDecimal BigDecimal::operator*= (const BigDecimal& b) {
      BigDecimal res  = multiply(*this, b); 
      this->number = res.number;
      this->scale  = res.scale;
      return *this;
   }
   BigDecimal BigDecimal::operator/  (const BigDecimal& b) { return divide(*this, b); }
   BigDecimal BigDecimal::operator/= (const BigDecimal& b) {
      BigDecimal res  = divide(*this, b); 
      this->number = res.number;
      this->scale  = res.scale;
      return *this;
   }
   bool BigDecimal::operator==(const BigDecimal& b) {
      struct opers beg = {this->number, b.number, this->scale, b.scale};
      adjustScales(&beg);
      return beg.number1 == beg.number2;
   }
   bool BigDecimal::operator!=(const BigDecimal& b) {
      struct opers beg = {this->number, b.number, this->scale, b.scale};
      adjustScales(&beg);
      return beg.number1 != beg.number2;
   }
   bool BigDecimal::operator<(const BigDecimal& b) {
      struct opers beg = {this->number, b.number, this->scale, b.scale};
      adjustScales(&beg);
      return beg.number1 < beg.number2;
   }
   bool BigDecimal::operator<=(const BigDecimal& b) {
      struct opers beg = {this->number, b.number, this->scale, b.scale};
      adjustScales(&beg);
      return beg.number1 <= beg.number2;
   }
  bool BigDecimal::operator>(const BigDecimal& b) {
      struct opers beg = {this->number, b.number, this->scale, b.scale};
      adjustScales(&beg);
      return beg.number1 > beg.number2;
  }
  bool BigDecimal::operator>=(const BigDecimal& b) {
      struct opers beg = {this->number, b.number, this->scale, b.scale};
      adjustScales(&beg);
      return beg.number1 >= beg.number2;
  }

   void BigDecimal::adjustScales(struct opers * op) {
      int diff = op->scale1 - op->scale2;
      if (diff < 0) op->number1 *= (10 * diff);
      if (diff > 0) op->number2 *= (10 * diff);
      op->scale1 += diff;
   }
   void BigDecimal::calculateScale(struct opers *op) {
       char m[64];
       int modulus = op->number1 % (10 ^ op->scale1);
       sprintf(m, "%d", modulus);
       op->scale1 = (unsigned int) strlen(m) - 1;
       op->number1 /= (10 ^ op->scale1);
   }
   BigDecimal BigDecimal::add(BigDecimal& a, const BigDecimal& b) {
      struct opers beg = {a.number, b.number, a.scale, b.scale};
      adjustScales(&beg);
      beg.number1 += beg.number2;
      calculateScale(&beg);
      return BigDecimal(beg.number1, beg.scale1);
   }
   BigDecimal BigDecimal::subtract(BigDecimal& a, const BigDecimal& b) {
      struct opers beg = {a.number, b.number, a.scale, b.scale};
      adjustScales(&beg);
      beg.number1 -= beg.number2;
      calculateScale(&beg);
      return BigDecimal(beg.number1, beg.scale1);
   }
   BigDecimal BigDecimal::multiply(BigDecimal& a, const BigDecimal& b) {
      struct opers beg = {a.number, b.number, a.scale, b.scale};
      adjustScales(&beg);
      beg.number1 *= beg.number2;
      beg.scale1 *= 2;
      calculateScale(&beg);
      return BigDecimal(beg.number1, beg.scale1);
   }
   BigDecimal BigDecimal::divide(BigDecimal& a, const BigDecimal& b) {
      struct opers beg = {a.number, b.number, a.scale, b.scale};
      adjustScales(&beg);
      beg.number1 /= beg.number2;
      beg.scale1 *= 2;
      calculateScale(&beg);
      return BigDecimal(beg.number1, beg.scale1);
   }
   string BigDecimal::makeString(long long value, int scale) {
       string str = to_string(value * 10);
       int idx = (int) str.length() - 2;
       for (int i = 0; i < scale; i++) str[idx + 1] = str[idx];
       str[idx] = '.';
       return sstring(str);
   }
   void BigDecimal::setValues() {
       vector<char *> toks = sstring(buffer).tokenize("\\.");
       int i = strlen(toks[1]) - 1;
       while (i > -1 && toks[1][i] == '0') toks[1][i--] = 0x0;
       sstring str = sstring(toks[0]);
       str.append(toks[1]);
       scale = strlen(toks[1]);
       number = stoll(str);
       for (i = 0; i < toks.size(); i++) free(toks[i]);
   }
   //TODO Check when number fit in float, double or not
}
