#pragma once

#include "config.h"
#include "sstring.hpp"

using namespace std;

namespace NST {
   class Real {
   public:
      Real() = delete;
      Real(sstring value) { Real(value.c_str()); }
      Real(const char* value);
      Real(float value);
      Real(double value);
      Real(long double value);
      bool isFloat   () { return mask & 1; }
      bool isDouble     () { return mask & 2; }
      bool isLongDouble    () { return mask & 4; }
   private:
      long long value;
      char mask = 0x01;
      void validateReal(long long value);
   };
}
