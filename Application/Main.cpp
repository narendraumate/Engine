//
//  Main.cpp
//  Application
//
//  Created by Narendra Umate on 9/7/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#include "Main.h"

Engine::Logger* g_logger = Engine::Logger::singleton();
Engine::Renderer* g_renderer = NULL;
Engine::Settings* g_settings = Engine::Settings::singleton();

void initializeMain()
{
	g_logger->print0();

	// Create the renderer object
#ifdef __APPLE__
	g_renderer = new Engine::GlRenderer(g_settings->getWidth(), g_settings->getHeight(), g_settings->getApplicationName());
#elif _WIN32
	g_renderer = new Engine::DxRenderer(g_settings->getWidth(), g_settings->getHeight(), g_settings->getApplicationName());
#endif //_WIN32

	// Initialize and run the renderer object
	g_renderer->initialize();
}

bool runMain()
{
	if (g_renderer->preDraw())
	{
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
	g_logger->print0();

	// Shutdown and release the renderer object
	g_renderer->shutdown();
	delete g_renderer;

	g_logger->destroySingleton();
	g_settings->destroySingleton();

#ifdef USE_MEMTRACK
	Engine::MemTrack::TrackDumpBlocks();
	Engine::MemTrack::TrackListMemoryUsage();
#endif //USE_MEMTRACK
}

Engine::Logger* getLogger()
{
	if (g_logger == NULL)
	{
		g_logger = Engine::Logger::singleton();
	}
	return g_logger;
}

Engine::Renderer* getRenderer()
{
	return g_renderer;
}

Engine::Settings* getSettings()
{
	if (g_settings == NULL)
	{
		g_settings = Engine::Settings::singleton();
	}
	return g_settings;
}
