//
//  Utils.cpp
//  Application
//
//  Created by Narendra Umate on 1/2/14.
//
//

#include "Utils.h"

Engine::Utils* Engine::Utils::s_instance = NULL;

namespace Engine
{

	Utils::Utils()
	{ }

	Utils::~Utils()
	{ }

	Utils* Utils::singleton()
	{
		if (s_instance == NULL)
		{
			s_instance = new Utils();
		}
		return s_instance;
	}

	void Utils::destroySingleton()
	{
		if (s_instance)
		{
			delete s_instance;
			s_instance = NULL;
		}
	}

	std::string Utils::findFile(const std::string &strBasename)
	{
		std::string strFilename = LOCAL_FILE_DIR + strBasename;
		std::ifstream testFile(strFilename.c_str());
		if (testFile.is_open())
		{
			testFile.close();
			return strFilename;
		}

		strFilename = GLOBAL_FILE_DIR + strBasename;
		testFile.open(strFilename.c_str());
		if (testFile.is_open())
		{
			testFile.close();
			return strFilename;
		}

		return "";
	}

}
