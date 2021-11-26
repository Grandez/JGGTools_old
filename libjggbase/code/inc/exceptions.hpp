#pragma once
#include <stdexcept>
#include <string>

#include "config.h"
#include "msg_locale.hpp"

namespace NST {
   class ToolsException : public std::domain_error {
      public:
         ToolsException(const char *fmt, ...);
         const char* what();
      protected:   
/// \cond DO_NOT_DOCUMENT
         void mountMessage(const char* fmt, va_list list);
/// \endcond
      private:
         std::string message;
   };
   class ToolsValueException : public ToolsException {
      public:
         ToolsValueException(const char *fmt, ...);
   };
   class ToolsCastException : public ToolsException {
      public:
         ToolsCastException(const char *fmt, ...);
   };

}