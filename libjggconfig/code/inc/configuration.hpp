#pragma once
#include <string>
#include <vector>
#include <set>
#include <unordered_map>

#include "config.h"
#include "jggtools.hpp"
#include "path.hpp"

using namespace std;
namespace NST {
   class Configuration {
      public:
          static Configuration*                        load(string configFile, int type = 0);
          static Configuration*                        load(const char *configFile, int type = 0);
          static unordered_map<string, set<string>> parse(string configFile, int type = 0);
          virtual unordered_map<string, set<string>> parse() = 0;
      protected:
          Configuration() {};
      private:
          static Path path;
          static Configuration *cfg;
   };

}
