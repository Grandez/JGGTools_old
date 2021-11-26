#pragma once

#include "config.h"
#include "sstring.hpp"

using namespace std;

namespace NST {
   class Decimal {
   public:
      Decimal() = delete;
      Decimal(sstring value) { Decimal(value.c_str()); }
      Decimal(const char* value);
      Decimal(float value);
      Decimal(double value);
      Decimal(long double value);
      Decimal(int value);
      Decimal(long value);
      Decimal(long long value);
      sstring     toString();
      char*       toChar();
      sstring     toStringRounded(int scale = 0);   
      char*       toCharRounded(int scale = 0);   
      float       toFloat();
      double      toDouble();
      long double toLongDouble();
      long        toFloor();
      long        toCeil();
      Decimal     round(int scale = 0);
//      const char* format(int scale = -1, int fmt = -1);

        Decimal operator+(const Decimal&);
        Decimal operator-(const Decimal&);
        Decimal operator*(const Decimal&);
        Decimal operator/(const Decimal&);

        Decimal operator +=(const Decimal&);
        Decimal operator -=(const Decimal&);
        Decimal operator *=(const Decimal&);
        Decimal operator /=(const Decimal&);

        bool operator==(const Decimal&) ;
        bool operator!=(const Decimal&) ;
        bool operator<(const Decimal&) ;
        bool operator<=(const Decimal&) ;
        bool operator>(const Decimal&) ;
        bool operator>=(const Decimal&) ;
   private:
      Decimal(long long value, int scale); 
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
      Decimal add        (Decimal& a, const Decimal&b);
      Decimal subtract   (Decimal& a, const Decimal& b);
      Decimal multiply   (Decimal& a, const Decimal& b);
      Decimal divide     (Decimal& a, const Decimal& b);
      sstring makeString (long long value, int scale);
      long long makeRound(int scale);
      void    setValues();  
   };
}
