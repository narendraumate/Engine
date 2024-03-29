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

	Logger::Logger(const std::string& logfile)
	{
#ifdef PRINT_TO_FILE
		m_fstream.open(logfile.c_str(), std::fstream::out);
#endif //PRINT_TO_FILE
	}

	Logger::~Logger()
	{
#ifdef PRINT_TO_FILE
		m_fstream.close();
#endif //PRINT_TO_FILE
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

	void Logger::printInfo()
	{ }

	void Logger::printInfo(const std::string& file, const std::string& line, const std::string& message)
	{
#ifdef PRINT_TO_FILE
		m_fstream << file << ":" << line << " " << message << std::endl;
#endif //PRINT_TO_FILE

#ifdef PRINT_TO_DISPLAY
		std::cout << file << ":" << line << " " << message << std::endl;
#endif //PRINT_TO_DISPLAY
	}

	void Logger::printInfo(const std::string& file, const std::string& line, const char* name, const void* array, const int& size)
	{
#ifdef PRINT_TO_FILE
		m_fstream << file << ":" << line << " " << name << " ";
		for (int i = 0; i < size; ++i)
			m_fstream << ((float*)array)[i] << " ";
		m_fstream << std::endl;
#endif //PRINT_TO_FILE

#ifdef PRINT_TO_DISPLAY
		std::cout << file << ":" << line << " " << name << " ";
		for (int i = 0; i < size; ++i)
			std::cout << ((float*)array)[i] << " ";
		std::cout << std::endl;
#endif //PRINT_TO_DISPLAY
	}

}
