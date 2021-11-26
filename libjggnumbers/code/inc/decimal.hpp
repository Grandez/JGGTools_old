#pragma once
#include <memory>
#include <string>

#include "../../../libjggbase/include/config.h"

using namespace std;

namespace NST {
   class Decimal {
   public:
      Decimal() = delete;
      Decimal(string value);//  { Decimal(value.c_str()); }
      Decimal(const char* value);
      Decimal(float value);
      Decimal(double value);
      Decimal(int value);
      Decimal(long value);
      Decimal(long value, int scale);

      string     toString();
      char*       toChar();
      string     toStringRounded(int scale = 0);   
      char*       toCharRounded(int scale = 0);   
      float       toFloat();
      double      toDouble();
      long        toFloor();
      long        toCeil();
      long        getIntPart();
      long        getDecPart(); 
      Decimal     round(int scale = 0);
//      const char* format(int scale = -1, int fmt = -1);

      Decimal add     (Decimal& a, Decimal& b);
      Decimal subtract(Decimal& a, Decimal& b);
      Decimal multiply(Decimal& a, Decimal& b);
      Decimal divide  (Decimal& a, Decimal& b);

        Decimal operator+(Decimal&);
        Decimal operator-(Decimal&);
        Decimal operator*(Decimal&);
        Decimal operator/(Decimal&);

        Decimal operator +=(Decimal&);
        Decimal operator -=(Decimal&);
        Decimal operator *=(Decimal&);
        Decimal operator /=(Decimal&);
        Decimal operator +=(long);
        Decimal operator -=(long);
        Decimal operator *=(long);
        Decimal operator /=(long);
        Decimal operator +=(double);
        Decimal operator -=(double);
        Decimal operator *=(double);
        Decimal operator /=(double);

        Decimal operator+(long f);
        Decimal operator+(double f);
        Decimal operator-(long f);
        Decimal operator-(double f);
        Decimal operator*(long f);
        Decimal operator*(double f);
        Decimal operator/(long f);
        Decimal operator/(double f);

        bool operator==(Decimal&) ;
        bool operator!=(Decimal&) ;
        bool operator< (Decimal&) ;
        bool operator<=(Decimal&) ;
        bool operator> (Decimal&) ;
        bool operator>=(Decimal&) ;

private:
   class DecimalImpl;
   unique_ptr<DecimalImpl, void (*)(DecimalImpl *)> _decimalImpl;
};
/*
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
*/
}
