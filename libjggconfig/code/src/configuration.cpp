#pragma once
#include <string>

#include "config.h"

#include "configuration.hpp"
#include "config_ini.hpp"
#include "path.hpp"


namespace NST {
   Configuration *Configuration::load(string configFile, int type) {
       return load(configFile.c_str());
   }
   Configuration *Configuration::load(const char *configFile, int type) {
       path = Path(configFile);
       string ext = path.getExt();
       cfg = (Configuration *) new ConfigIni(path.getPath());
//       switch (getType(path.getExt(), type)) {
//          case 1: 
//       }
       return cfg;
   }
   unordered_map<string, set<string>> Configuration::parse(string configFile, int type) {
       load(configFile, type);
       return cfg->parse();
   }
   
/*
   Configuration *Configuration::get(const char *configFile, int type) {
       this->path = Path(configFile);
       string ext = path.getExt();
       switch (getType(path.getExt(), type)) {
          case 1: 
       }
   }

   Configuration *Configuration::getConfig() {
       
   }
   int Configuration::getType(string ext, int type) {
      if (type != 0) return type;
      return 1;
   }
*/
}
