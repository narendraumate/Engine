//
//  Utils.h
//  Application
//
//  Created by Narendra Umate on 1/2/14.
//
//

#ifndef __Application__Utils__
#define __Application__Utils__

#include <iostream>
#include <fstream>
#include <string>

#define LOCAL_FILE_DIR "Data/"
#if defined(__APPLE__)
#define GLOBAL_FILE_DIR "/Users/ardneran/Documents/Projects/GitHub/Engine/Data/"
#elif defined(__linux__)
#define GLOBAL_FILE_DIR "/home/ardneran/Documents/Engine/Data/"
#endif //defined(__linux__)

namespace Engine
{

	class Utils
	{
	private:
		Utils();
		~Utils();

	public:
		static Utils* singleton();
		static void destroySingleton();
		std::string findFile(const std::string &strBasename);

	private:
		static Utils* s_instance;
	};

}

#endif /* defined(__Application__Utils__) */
