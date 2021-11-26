#pragma once

#include <vector>
#include <string>

#include "config.h"
#include "jggtools.hpp"
#include "sstring.hpp"
#include "date.hpp"
#include "time.hpp"
#include "datetime.hpp"

using namespace std;

namespace NST {
   class Timestamp : public DateTime {
   public:
      Timestamp();
      Timestamp(sstring     str);
      Timestamp(const char* str);
      sstring toString();
//      Date   getDate();
//      Time   getTime();
//      struct tm *getTM();
   private:
       static long int uSec;
   };

}
