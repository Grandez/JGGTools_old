#include <regex>

#include "config.h" 

#include "exceptions.hpp"
#include "integer.hpp"

#ifdef _WIN32
#pragma warning( disable : 4996 )
#endif
using namespace std;

namespace NST {
   Integer::Integer(short       value)  { validateInteger((long long) value); }
   Integer::Integer(int         value)  { validateInteger((long long) value); }
   Integer::Integer(long        value)  { validateInteger((long long) value); }
   Integer::Integer(long long   value)  { validateInteger((long long) value); }
   Integer::Integer(const char* value)  {
        regex pat{"^[+-]?[^0-9]+$"};
		bool match = regex_search(value, pat);
		if (!match) throw new ToolsValueException(BAD_NATURAL, value);
        long long res = 0;
        int i = (value[0] == '+' || value[0] == '-') ? 1 : 0;
        for (i; i < strlen(value); i++) res = (res * 10) + value[i];
        if (value[0] == '-') res *= -1;
        validateInteger(res);
   }

   void Integer::validateInteger(long long value)  {
      if (value > LONG_MAX || value < LONG_MIN) mask |= 0x08;
      if (value > INT_MAX  || value < LONG_MIN) mask |= 0x04;
      if (value > SHRT_MAX || value < SHRT_MIN) mask |= 0x02;
   }
}
