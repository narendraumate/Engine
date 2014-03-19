//
//  Logger.h
//  Application
//
//  Created by Narendra Umate on 10/9/13.
//
//

#ifndef __Application__Logger__
#define __Application__Logger__

#include <string>

#define PRINT_TO_FILE
#define PRINT_TO_DISPLAY

#ifdef PRINT_TO_FILE
#include <fstream>
#endif //PRINT_TO_FILE

#ifdef PRINT_TO_DISPLAY
#include <iostream>
#endif //PRINT_TO_DISPLAY

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define print0() printInfo(__FILE__, TOSTRING(__LINE__), __FUNCTION__)
#define print1(message) printInfo(__FILE__, TOSTRING(__LINE__), message)

namespace Engine
{

	class Logger
	{
	private:
		Logger(const std::string& logfile);
		~Logger();

	public:
		static Logger* singleton();
		static void destroySingleton();
		void printInfo(const std::string& file, const std::string& line, const std::string& message);

	private:
		static Logger* s_instance;
#ifdef PRINT_TO_FILE
		std::fstream m_fstream;
#endif //PRINT_TO_FILE
	};

}
#endif /* defined(__Application__Logger__) */
