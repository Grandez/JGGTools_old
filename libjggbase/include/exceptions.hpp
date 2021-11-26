#pragma once
#include <stdexcept>

#include "config.h"

#include <memory>
#include "spimplmc.hpp"

namespace NST {
class ToolsException : public std::domain_error {
public:
    ToolsException(const char *fmt, ...);
    ~ToolsException();

    // Destructor, move constructor and move assignment are compiler-generated.
    // Copy constructor and copy assignment are implicitly deleted.

    const char* what();
   
private:
    class ToolsExceptionImpl;
    spimpl::unique_impl_ptr<ToolsExceptionImpl> _pImpl;  // Movable Smart PIMPL
};

/*
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <cstdarg>
#include "config.h"

namespace NST {
	class ToolsException : public std::domain_error {
       public:
 	      ToolsException() = delete;
          ~ToolsException();
	      ToolsException(const char* fmt, ...);
          const char* what() const override;
 	      
       protected:
          std::string mountMessage(const char* fmt, va_list list);
       private:
          class ToolsExceptionImpl;
          std::unique_ptr<ToolsExceptionImpl> _pImpl;
    };
    class ToolsCastException : public ToolsException {
    public:
 		ToolsCastException() = delete;
		ToolsCastException(const char* fmt, ...);

	};
*/
/*
	class CmdLineNotFoundException : public std::runtime_error {
	public:
	class CmdLineInvalidTypeException : public std::runtime_error {
	public:
		CmdLineInvalidTypeException() = delete;
		CmdLineInvalidTypeException(const char* fmt, ...);
	};

	class CmdLineException : public std::invalid_argument {
	public:
		CmdLineException() : invalid_argument("") {};
		CmdLineException(const char* fmt, ...); 
		CmdLineException(char* txt);
		~CmdLineException() {};
        string type;
	};

	class CmdLineParameterException : public CmdLineException {
	public:
		CmdLineParameterException() = delete;
		CmdLineParameterException(const char* fmt, ...);
	};
	class CmdLineValueException : public CmdLineException {
	public:
		CmdLineValueException() = delete;
		CmdLineValueException(const char* fmt, ...);
	};
	class CmdLineDuplicateArgumentException : public CmdLineException {
	public:
		CmdLineDuplicateArgumentException() = delete;
		CmdLineDuplicateArgumentException(const char* fmt, ...);
	};

	 // Exception indicating HELP has been requested

	class HelpRequested : public CmdLineException {
	public:
		const char *name;
		bool detailed = false;
		std::unordered_map<std::string, bool>        flags;
		std::unordered_map<std::string, std::string> options;

		HelpRequested() = delete;
		~HelpRequested();
	protected:
        HelpRequested(const char * programName, const char *txt, bool detailed
		                             , std::unordered_map<std::string, bool> flags
		                             , std::unordered_map<std::string, string> options);
	};
	class HelpSimpleRequested : public HelpRequested {
	public:
		HelpSimpleRequested( char * programName
			                ,unordered_map<string,bool> flags  
		                    ,unordered_map<string,string> options);       
	};
	class HelpDetailedRequested : public HelpRequested {
	public:
		HelpDetailedRequested( const char * programName
			                  ,unordered_map<string,bool> flags  
		                      ,unordered_map<string,string> options);
	};
*/

}