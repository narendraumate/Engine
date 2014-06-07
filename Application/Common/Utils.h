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
#define ASSET_FILE_DIR "/Users/ardneran/Documents/Models/"
#elif defined(__linux__)
#define GLOBAL_FILE_DIR "/home/ardneran/Documents/Projects/GitHub/Engine/Data/"
#define ASSET_FILE_DIR "/home/ardneran/Documents/Models/obj/"
#elif defined(_WIN32)
#define GLOBAL_FILE_DIR "/Data/" //TODO
#define ASSET_FILE_DIR "/obj/" //TODO
#endif //defined(_WIN32)

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
		std::string findFilePath(const std::string &strFileName);
		std::string findBasePath(const std::string &strFileName);

	private:
		static Utils* s_instance;
	};

}

#endif /* defined(__Application__Utils__) */
