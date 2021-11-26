#pragma once
#include <string>

#include "config.h"

using namespace std;

namespace NST {
   class BigDecimal {
   public:
      BigDecimal() = delete;
      BigDecimal(string value) { BigDecimal(value.c_str()); }
      BigDecimal(const char* value);
      BigDecimal(float value);
      BigDecimal(double value);
      BigDecimal(long double value);
      BigDecimal(int value);
      BigDecimal(long value);
      BigDecimal(long long value);
      string     toString();
      char*       toChar();
      string     toStringRounded(int scale = 0);   
      char*       toCharRounded(int scale = 0);   
      float       toFloat();
      double      toDouble();
      long double toLongDouble();
      long        toFloor();
      long        toCeil();
      BigDecimal     round(int scale = 0);
//      const char* format(int scale = -1, int fmt = -1);

        BigDecimal operator+(const BigDecimal&);
        BigDecimal operator-(const BigDecimal&);
        BigDecimal operator*(const BigDecimal&);
        BigDecimal operator/(const BigDecimal&);

        BigDecimal operator +=(const BigDecimal&);
        BigDecimal operator -=(const BigDecimal&);
        BigDecimal operator *=(const BigDecimal&);
        BigDecimal operator /=(const BigDecimal&);

        bool operator==(const BigDecimal&) ;
        bool operator!=(const BigDecimal&) ;
        bool operator<(const BigDecimal&) ;
        bool operator<=(const BigDecimal&) ;
        bool operator>(const BigDecimal&) ;
        bool operator>=(const BigDecimal&) ;
   private:
      BigDecimal(long long value, int scale); 
      int scale = 0;
      long long number = 0; 
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
      BigDecimal add        (BigDecimal& a, const BigDecimal&b);
      BigDecimal subtract   (BigDecimal& a, const BigDecimal& b);
      BigDecimal multiply   (BigDecimal& a, const BigDecimal& b);
      BigDecimal divide     (BigDecimal& a, const BigDecimal& b);
      string makeString (long long value, int scale);
      long long makeRound(int scale);
      void    setValues();  
   };
}
