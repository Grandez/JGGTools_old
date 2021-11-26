#include <iostream>
#include <cstdio>
#include "config.h"

#include "exceptions.hpp"

#ifdef _WIN32
#pragma warning( disable : 4996 )
#endif
#include <cstdarg>
using namespace std;

namespace NST {
 ToolsException::ToolsException(const char* fmt, ...) :  domain_error(fmt) {
	va_list args;
	va_start(args, fmt);
    mountMessage(fmt, args);
    va_end(args);
}
const char* ToolsException::what() {
    return message.c_str();
}
/// \cond DO_NOT_DOCUMENT
void ToolsException::mountMessage(const char* fmt, va_list list) {
        int szSize = 0;
        int count = 1;
        char *szWhat = (char *) malloc(szSize);
        do {
           szSize += MAX_SIZE_ERR;
           if (szWhat != 0x0) free (szWhat);
           szWhat = (char *) malloc(szSize);
           count = vsnprintf(szWhat, szSize, fmt, list);
        } while (count < 0);
        message = szWhat;
        free(szWhat);
//        addPointer(std::addressof(szWhat)); 
    }
/// \endcond
ToolsValueException::ToolsValueException(const char* fmt, ...) : ToolsException(fmt) {
	va_list args;
	va_start(args, fmt);
    mountMessage(fmt, args);
    va_end(args);
}
ToolsCastException::ToolsCastException(const char* fmt, ...) : ToolsException(fmt) {
	va_list args;
	va_start(args, fmt);
    mountMessage(fmt, args);
    va_end(args);
}
}