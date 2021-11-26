#pragma once

#include "config.h"
#include "sstring.hpp"

using namespace std;

namespace NST {
   class Natural {
   public:
      Natural() = delete;
      Natural(sstring value) { Natural(value.c_str()); }
      Natural(const char* value);
      Natural(short value);
      Natural(int value);
      Natural(long value);
      Natural(long long value);
      bool isShort   () { return mask & 1; }
      bool isInt     () { return mask & 2; }
      bool isLong    () { return mask & 4; }
      bool isLongLong() { return mask & 8; }
      sstring toString();
      char *  toChar(); 
   private:
      long long value;
      char mask = 0x01;
      void validateNatural(unsigned long long value);
   };
}
