#include <regex>

#include "config.h" 

#include "exceptions.hpp"
#include "natural.hpp"

#ifdef _WIN32
#pragma warning( disable : 4996 )
#endif
using namespace std;

namespace NST {
   Natural::Natural(short       value)  { validateNatural((unsigned long long) value); }
   Natural::Natural(int         value)  { validateNatural((unsigned long long) value); }
   Natural::Natural(long        value)  { validateNatural((unsigned long long) value); }
   Natural::Natural(long long   value)  { validateNatural((unsigned long long) value); }
   Natural::Natural(const char* value)  { 
        regex pat{"^[^0-9]+$"};
		bool match = regex_search(value, pat);
		if (!match) throw new ToolsValueException(BAD_NATURAL, value);
        unsigned long long res = 0;
        for (int i = 0; i < strlen(value); i++) res = (res * 10) + value[i];
        validateNatural(res);
   }
   void Natural::validateNatural(unsigned long long value)  {
      if (value < 0) throw new ToolsValueException(BAD_NATURAL, to_string(value).c_str());
      if (value > ULONG_MAX) mask |= 0x08;
      if (value > UINT_MAX)  mask |= 0x04;
      if (value > USHRT_MAX) mask |= 0x02;
   }
   sstring Natural::toString() {
       return to_string(value);
   }
   char * Natural::toChar() {
       return strdup(to_string(value).c_str());;
   }

}
