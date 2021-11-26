#pragma once
#include <string>

#include "config.h"

using namespace std;

namespace NST {
   class Path {
   public:
      Path() = delete;
      Path(string value);
      Path(const char* value);
      bool isDir();
      bool isFile();
      bool exists();
      string getDrive();
      string getDir();
      string getName();
      string getExt(); 
      string getPath();
   private:
      string path;

   };
}
