//
//  Main.cpp
//  Application
//
//  Created by Narendra Umate on 9/7/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#include "Main.h"

Engine::Logger* g_logger = Engine::Logger::singleton();
Engine::Settings* g_settings = Engine::Settings::singleton();
Engine::Utils* g_utils = Engine::Utils::singleton();

Engine::Renderer* g_renderer = NULL;

void initializeMain()
{
	Engine::Logger::singleton()->print0();

	// Create the renderer object
#if defined(__APPLE__) || defined(__linux__)
    g_renderer = new Engine::GlRenderer(g_settings->getWidth(), g_settings->getHeight(), g_settings->getTitle());
#elif _WIN32
    g_renderer = new Engine::DxRenderer(g_settings->getWidth(), g_settings->getHeight(), g_settings->getTitle());
#endif //_WIN32

	// Initialize and run the renderer object
	g_renderer->initialize();
}

bool runMain()
{
	if (g_renderer->preDraw())
	{
		g_renderer->run();
		g_renderer->postDraw();
		return true;
	}
	else
	{
		return false;
	}
}

void deinitializeMain()
{
	Engine::Logger::singleton()->print0();

	// Shutdown and release the renderer object
	g_renderer->shutdown();
	delete g_renderer;

	g_logger->destroySingleton();
	g_settings->destroySingleton();
	g_utils->destroySingleton();

	Engine::MemTrack::TrackDumpBlocks();
	Engine::MemTrack::TrackListMemoryUsage();
}

Engine::Logger* getLogger()
{
	if (g_logger == NULL)
	{
		g_logger = Engine::Logger::singleton();
	}
	return g_logger;
}

Engine::Settings* getSettings()
{
	if (g_settings == NULL)
	{
		g_settings = Engine::Settings::singleton();
	}
	return g_settings;
}

Engine::Utils* getUtils()
{
	if (g_utils == NULL)
	{
		g_utils = Engine::Utils::singleton();
	}
	return g_utils;
}

Engine::Renderer* getRenderer()
{
	return g_renderer;
}
