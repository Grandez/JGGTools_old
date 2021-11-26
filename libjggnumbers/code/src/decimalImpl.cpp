#include <regex>
#include "config.h"

#include "sstring.hpp"
#include "exceptions.hpp"
#include "msg_locale.hpp"
#include "decimal.hpp"
#include "decimalImpl.hpp"

#ifdef _WIN32
#pragma warning( disable : 4996 4244 )
#endif

namespace NST {
   Decimal::DecimalImpl::DecimalImpl(string value) { DecimalImpl(value.c_str()); }
   Decimal::DecimalImpl::DecimalImpl(const char* value)  {
        regex pat{"^[+-]?[0-9]*[\\.,]?[0-9]*$"};
		bool match = regex_search(value, pat);
		if (!match) throw new ToolsValueException(BAD_DECIMAL, value);
        vector<char *> data = (sstring(value)).tokenize("[\\.,]");
        if (data.size() > 2 || data.size() == 0) throw new ToolsValueException(BAD_DECIMAL, value);
        long aux = atol(data[0]);
        number = abs(aux);
        scale = 0;
        if (data.size() == 2) {
            scale  = (unsigned int) strlen(data[1]);
            number *= pow(10,scale);
            number += atol(data[1]);
        }
        if (aux < 0) number *= -1;
        // When using char *, those are allocated
        for (unsigned int i = 0; i < data.size(); i++) free(data[i]);
   }
   Decimal::DecimalImpl::DecimalImpl(float  value) { 
       sprintf(buffer, "%f", value); 
       setValues();
   }
   Decimal::DecimalImpl::DecimalImpl(double value) { 
       sprintf(buffer, "%lf", value); 
       setValues();
   }
   Decimal::DecimalImpl::DecimalImpl(int    value) {  this->number = value;            }
   Decimal::DecimalImpl::DecimalImpl(long   value) {  this->number = value;            }
   Decimal::DecimalImpl::DecimalImpl(long   value, int scale) {
         this->number = value;
         this->scale  = scale;
   }

   long    Decimal::DecimalImpl::getIntPart() { 
        if (scale == 0) return number;
        return number / pow(10, scale);
   }
   long    Decimal::DecimalImpl::getDecPart() { 
        if (scale == 0) return 0;
        long rem = pow(10, scale);
        long res = (number % rem);
        if (res < 0) res *= -1;
        return res;
    }
   string  Decimal::DecimalImpl::toString() {
       string str = to_string(number);
       int len = str.length();
       int diff = len - scale;
       string str1 = str.substr(0, diff);
       if (str1.length() == 0) str1 = string("0");
       if (str1.length() == 1 && str1[0] == '-') str1 = string("-0");
       string str2 = str.substr(diff, len);
       if (str2.length() == 0) return str1;
       return str1.append(".").append(str2);
   }
   char*   Decimal::DecimalImpl::toChar() {
      sstring str(this->toString());
      return strdup(str.toChar());
   }
   sstring Decimal::DecimalImpl::toStringRounded(int scale) {
       Decimal dec = round(scale);
       return dec.toString();
   }
   char*   Decimal::DecimalImpl::toCharRounded(int scale) {
       return strdup(toStringRounded(scale).toChar());
   }
   float   Decimal::DecimalImpl::toFloat() {
         float f = number;
         return f / (10 ^ scale);
   }
   double  Decimal::DecimalImpl::toDouble() {
         double d = number;
         return d / (10 ^ scale);
   }
   long    Decimal::DecimalImpl::toFloor() {
        long value = number / (10 ^ scale);
        return value + 1;
   }
   long    Decimal::DecimalImpl::toCeil() {
        return number / (10 ^ scale);
   }
   Decimal Decimal::DecimalImpl::round(int scale) {
       int remove = this->scale - scale;
       long p =  pow(10, remove - 1);
       p *= 5;  
       if (number < 0) p *= -1;
       long value = number + p;
       long p2 = pow(10, this->scale - scale);
       return Decimal(value / p2, scale);
   }
   void Decimal::DecimalImpl::adjustScales(struct opers * op) {
      int diff = op->scale1 - op->scale2;
      if (diff < 0) op->number1 *= (10 * diff);
      if (diff > 0) op->number2 *= (10 * diff);
      op->scale1 += diff;
   }
   void Decimal::DecimalImpl::calculateScale(struct opers *op) {
       char m[64];
       int modulus = op->number1 % (10 ^ op->scale1);
       sprintf(m, "%d", modulus);
       op->scale1 = (unsigned int) strlen(m) - 1;
       op->number1 /= (10 ^ op->scale1);
   }
   Decimal Decimal::DecimalImpl::add(Decimal& a, Decimal& b) {
      struct opers beg = {a.getIntPart(), b.getIntPart(), a.getDecPart(), b.getDecPart()};
      adjustScales(&beg);
      beg.number1 += beg.number2;
      calculateScale(&beg);
      return Decimal(beg.number1, beg.scale1);
   }
   Decimal Decimal::DecimalImpl::subtract(Decimal& a, Decimal& b) {
      struct opers beg = {a.getIntPart(), b.getIntPart(), a.getDecPart(), b.getDecPart()};
      adjustScales(&beg);
      beg.number1 -= beg.number2;
      calculateScale(&beg);
      return Decimal(beg.number1, beg.scale1);
   }
   Decimal Decimal::DecimalImpl::multiply(Decimal& a, Decimal& b) {
      struct opers beg = {a.getIntPart(), b.getIntPart(), a.getDecPart(), b.getDecPart()};
      adjustScales(&beg);
      beg.number1 *= beg.number2;
      beg.scale1 *= 2;
      calculateScale(&beg);
      return Decimal(beg.number1, beg.scale1);
   }
   Decimal Decimal::DecimalImpl::divide(Decimal& a, Decimal& b) {
      struct opers beg = {a.getIntPart(), b.getIntPart(), a.getDecPart(), b.getDecPart()};
      adjustScales(&beg);
      beg.number1 /= beg.number2;
      beg.scale1 *= 2;
      calculateScale(&beg);
      return Decimal(beg.number1, beg.scale1);
   }
   bool Decimal::DecimalImpl::equal(Decimal& b) {
      struct opers beg = {this->getIntPart(), b.getIntPart(), this->getDecPart(), b.getDecPart()};
      adjustScales(&beg);
      return beg.number1 == beg.number2;
   }
   bool Decimal::DecimalImpl::gt(Decimal& b) {
      struct opers beg = {this->getIntPart(), b.getIntPart(), this->getDecPart(), b.getDecPart()};
      adjustScales(&beg);
      return beg.number1 > beg.number2;
   }
   bool Decimal::DecimalImpl::lt(Decimal& b) {
      struct opers beg = {this->getIntPart(), b.getIntPart(), this->getDecPart(), b.getDecPart()};
      adjustScales(&beg);
      return beg.number1 < beg.number2;
   }
   bool Decimal::DecimalImpl::ge(Decimal& b) {
      if (equal(b)) return true;
      return gt(b); 
   }
   bool Decimal::DecimalImpl::le(Decimal& b) {
      if (equal(b)) return true;
      return lt(b); 
   }

   sstring Decimal::DecimalImpl::makeString(long long value, int scale) {
       string str = to_string(value * 10);
       int idx = (int) str.length() - 2;
       for (int i = 0; i < scale; i++) str[idx + 1] = str[idx];
       str[idx] = '.';
       return sstring(str);
   }

   void Decimal::DecimalImpl::setValues() {
       vector<char *> toks = sstring(buffer).tokenize("\\.");
       unsigned int i = (int) strlen(toks[1]) - 1;
      while (toks[1][i] == '0') {
             toks[1][i--] = 0x0;
             if (i == 0) break;
      }
       sstring str = sstring(toks[0]);
       str.append(toks[1]);
       scale = (int) strlen(toks[1]);
       number = stol(str);
       for (i = 0; i < toks.size(); i++) free(toks[i]);
   }
/*
   void Decimal::DecimalImpl::calculateScale(struct opers *op) {
       char m[64];
       int modulus = op->number1 % (10 ^ op->scale1);
       sprintf(m, "%d", modulus);
       op->scale1 = (unsigned int) strlen(m) - 1;
       op->number1 /= (10 ^ op->scale1);
   }
*/
   //TODO Check when number fit in float, double or not
}