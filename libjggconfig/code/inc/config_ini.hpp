#pragma once
#include <unordered_map>
#include <set>
#include "config.h"

#include "path.hpp"
#include "configuration.hpp" 

namespace NST {
class ConfigIni : public Configuration {
   public:
      ConfigIni(const char *path);
      void load();
      unordered_map<string, set<string>> parse() override;
   private:
      const char *path = 0x0;
      char *buffer = 0x0;
      vector<sstring> lines;
};

}