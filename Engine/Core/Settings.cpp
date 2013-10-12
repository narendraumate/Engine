//
//  Settings.cpp
//  Application
//
//  Created by Narendra Umate on 10/11/13.
//
//

#include "Settings.h"

Engine::Settings* Engine::Settings::s_instance = NULL;

namespace Engine
{

	Settings::Settings()
	:	m_width(0)
	,	m_height(0)
	{ }

	Settings::~Settings()
	{
		m_width = 0;
		m_height = 0;
		m_applicationName = "";
	}

	Settings* Settings::singleton()
	{
		if (s_instance == NULL)
		{
			s_instance = new Settings::Settings();
		}
		return s_instance;
	}

	void Settings::destroySingleton()
	{
		if (s_instance)
		{
			delete s_instance;
			s_instance = NULL;
		}
	}

	void Settings::setWidth(const int& width)
	{
		m_width = width;
	}

	int Settings::getWidth()
	{
		return m_width;
	}

	void Settings::setHeight(const int& height)
	{
		m_height = height;
	}

	int Settings::getHeight()
	{
		return m_height;
	}

	void Settings::setApplicationName(const char* applicationName)
	{
		m_applicationName = applicationName;
	}

	const char* Settings::getApplicationName()
	{
		return m_applicationName.c_str();
	}
	
}