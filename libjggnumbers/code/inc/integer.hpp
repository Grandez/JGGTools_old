#pragma once

#include "config.h"
#include "sstring.hpp"

using namespace std;

namespace NST {
   class Integer {
   public:
      Integer() = delete;
      Integer(sstring value) { Integer(value.c_str()); }
      Integer(const char* value);
      Integer(short value);
      Integer(int value);
      Integer(long value);
      Integer(long long value);
      bool isShort   () { return mask & 1; }
      bool isInt     () { return mask & 2; }
      bool isLong    () { return mask & 4; }
      bool isLongLong() { return mask & 8; }
   private:
      long long value;
      char mask = 0x01;
      void validateInteger(long long value);
   };
}
