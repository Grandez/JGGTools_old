#include <string>

#include "config.h"
#include "path.hpp"

using namespace std;

namespace NST {
      Path::Path(string value) { path = value;}
      Path::Path(const char* value) { path = string(value); }
      bool Path::isDir() { return false; }
      bool Path::isFile() { return false; }
      bool Path::exists() { return false; }
      string Path::getDrive() { return ""; }
      string Path::getDir(){ return ""; }
      string Path::getName(){ return ""; }
      string Path::getExt(){ return ""; }
      string Path::getPath() { return path;}
}
/*
	filesystem::path        validateDir       (const char* value) {
		// If is not a valid path, chdir return -1
		// Some times chdir returns 0 but not change the directory
		char old[256];
		char tmp[256];
		int rc, rc2;
		char* ptr = getcwd(old, 256);
		if (strcmp(value, ".") == 0) return filesystem::path(old);
		if (strcmp(value, old) == 0) return filesystem::path(old);
		rc = _chdir(value);
		if (rc) throw new CmdLineValueException(TXT_VAL_EXPECTED, value, TXT_DIR );
		ptr = getcwd(tmp, 256);
		rc = chdir(old);
        #ifdef _WIN32 // Windows is case insensitive
		    rc2 = strcmpi(old, tmp);
        #else
		    rc2 = strcmp(old, tmp);
        #endif

		if (rc2 == 0) throw new CmdLineValueException(TXT_VAL_EXPECTED, value, TXT_DIR);
		return filesystem::path(value);
	}
	filesystem::path        validateDirExist(const char* value) {
		struct stat info;
		validateDir(value);
		int rc = stat(value, &info);
		if (stat(value, &info) != 0) throw new CmdLineValueException(TXT_VAL_EXPECTED, value, TXT_NO_DIR);
		unsigned short mask = info.st_mode & S_IFDIR;
		//mask ^= 16384; // 100 0000 0000 0000
		if (mask == 0)          throw new CmdLineValueException(TXT_VAL_EXPECTED, value, TXT_DIR_NOTFND);
		return filesystem::path(value);
	}
	filesystem::path        validateFile      (const char* value) {
		try {
			return filesystem::path(value);
		}
		catch (exception ex) {
			throw new CmdLineValueException(TXT_VAL_EXPECTED, value, TXT_FILE);
		}
	}
	filesystem::path        validateFileExist (const char* value) {
		struct stat info;
		filesystem::path p = validateFile(value);
		if (stat(value, &info) != 0) throw new CmdLineValueException(TXT_VAL_EXPECTED, value, TXT_FILE_NOTFND);
		if (info.st_mode & S_IFDIR)  throw new CmdLineValueException(TXT_VAL_EXPECTED, value, TXT_FILE_DIR);
		return p;
	}
*/