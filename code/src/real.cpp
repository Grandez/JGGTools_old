#include <regex>

#include "config.h" 

#include "exceptions.hpp"
#include "real.hpp"

#ifdef _WIN32
#pragma warning( disable : 4996 )
#endif
using namespace std;

namespace NST {
   Real::Real(float       value)  { validateReal((long double) value); }
   Real::Real(double      value)  { validateReal((long double) value); }
   Real::Real(long double value)  { validateReal((long double) value); }
   Real::Real(const char* value)  {
        regex pat{"^[+-]?[0-9][.]?[0-9]*+$"};
		bool match = regex_search(value, pat);
		if (!match) throw new ToolsValueException(BAD_REAL, value);
        bool dec = false;
        int  scale = 0;
        long double res = 0.0;
        int i = (value[0] == '+' || value[0] == '-') ? 1 : 0;
        for (i; i < strlen(value); i++) {
            if (value[i] == '.') dec = true;
            res = (res * 10) + value[i];
            if (dec) scale++;
        } 
        if (value[0] == '-') res *= -1;
        res = res / (10 ^ scale);
        validateReal(res);
   }

   void Real::validateReal(long long value)  {
      if (value > DBL_MAX || value < DBL_MIN) mask |= 0x04;
      if (value > FLT_MAX || value < FLT_MIN) mask |= 0x02;
   }
}
