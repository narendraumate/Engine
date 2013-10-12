//
//  Logger.h
//  Application
//
//  Created by Narendra Umate on 10/9/13.
//
//

#ifndef __Application__Logger__
#define __Application__Logger__

#include <iostream>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define print0() printInfo(__FILE__, TOSTRING(__LINE__), __FUNCTION__)
#define print1(message) printInfo(__FILE__, TOSTRING(__LINE__), message)

namespace Engine
{

	class Logger
	{
	private:
		Logger(std::string logfile);
		~Logger();

	public:
		static Logger* singleton();
		static void destroySingleton();
		void printInfo(std::string file, std::string line, std::string message);

	private:
		static Logger* s_instance;
	};

}
#endif /* defined(__Application__Logger__) */
