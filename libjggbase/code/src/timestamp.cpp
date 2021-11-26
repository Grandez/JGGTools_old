#include <time.h>

#ifdef _WIN32
   #include "sys/timeb.h"
#else
   #include <sys/time.h>
#endif

#ifdef _WIN32
#pragma warning( disable : 4996 )
#endif
#include "config.h"

#include "jggtools.hpp"
#include "timestamp.hpp"

namespace NST {
   Timestamp::Timestamp() : DateTime() {
      uSec++;
#ifndef _WIN32
      struct timeval mTimeval;
      gettimeofday (&mTimeval, NULL);
      uSec = mtimeVal.tv_usec
#endif
   }
   Timestamp::Timestamp(sstring     str) : DateTime(str) { uSec++; }
   Timestamp::Timestamp(const char* str) : DateTime(str) { uSec++; }
      sstring Timestamp::toString() { 
          char buff[27];
//          sprintf(buff, "%s-%s.%06d", mDate.toChar(), mTime.toChar(), uSec);
          return sstring(buff);
      }
//      Date   Timestamp::getDate() { return mDate; }
//      Time   Timestamp::getTime()  { return mTime; }
}
