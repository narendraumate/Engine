//
//  Logger.cpp
//  Application
//
//  Created by Narendra Umate on 10/9/13.
//
//

#include "Logger.h"

Engine::Logger* Engine::Logger::s_instance = NULL;

namespace Engine
{

	Logger::Logger(std::string logfile)
	{

	}

	Logger::~Logger()
	{

	}

	Logger* Logger::singleton()
	{
		if (s_instance == NULL)
		{
			s_instance = new Logger("Application.log");
		}
		return s_instance;
	}

	void Logger::destroySingleton()
	{
		if (s_instance)
		{
			delete s_instance;
			s_instance = NULL;
		}
	}

	void Logger::printInfo(std::string file, std::string line, std::string message)
	{
		std::cout << file << ":" << line << " " << message << std::endl;
	}
	
}
