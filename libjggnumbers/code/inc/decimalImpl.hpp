#pragma once

#include "config.h"
#include "decimal.hpp"

using namespace std;

namespace NST {
   class Decimal::DecimalImpl {
   public:
      DecimalImpl(string      value);
      DecimalImpl(const char* value);
      DecimalImpl(float       value);
      DecimalImpl(double      value);
      DecimalImpl(int value);
      DecimalImpl(long value);
      DecimalImpl(long value, int scale);
      long    getIntPart();
      long    getDecPart();
      string  toString();
      char*   toChar();
      sstring toStringRounded(int scale);
      char*   toCharRounded(int scale);
      float   toFloat();
      double  toDouble();
      long    toFloor();
      long    toCeil();
      Decimal round(int scale);
      Decimal add       (Decimal& a, Decimal&b);
      Decimal subtract  (Decimal& a, Decimal& b);
      Decimal multiply  (Decimal& a, Decimal& b);
      Decimal divide    (Decimal& a, Decimal& b);
      bool    equal     (Decimal& b);
      bool    gt        (Decimal& b);
      bool    lt        (Decimal& b);
      bool    ge        (Decimal& b);
      bool    le        (Decimal& b);

   private:
      long scale = 0;
      long number = 0; 
      char buffer[512] = {0x0}; // Common bufffer
      // Store values for binary operations 
      struct opers {
         long number1;
         long number2;
         long scale1;
         long scale2;
      };
      void    adjustScales(struct opers *);
      void    calculateScale(struct opers *);
      void    setValues();  
      sstring makeString (long long value, int scale);
   };
}