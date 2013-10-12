//
//  Settings.h
//  Application
//
//  Created by Narendra Umate on 10/11/13.
//
//

#ifndef __Application__Settings__
#define __Application__Settings__

#include <iostream>
#include <string>

namespace Engine
{

	class Settings
	{
	private:
		Settings();
		~Settings();

	public:
		static Settings* singleton();
		static void destroySingleton();

		void setWidth(const int& width);
		int getWidth();
		void setHeight(const int& height);
		int getHeight();
		void setApplicationName(const char* applicationName);
		const char* getApplicationName();

	private:
		int m_width;
		int m_height;
		std::string m_applicationName;
		static Settings* s_instance;
	};

}

#endif /* defined(__Application__Settings__) */
