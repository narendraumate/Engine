//
//  Main.cpp
//  Application
//
//  Created by Narendra Umate on 9/7/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#include "Main.h"

Engine::Logger* g_logger = NULL;
Engine::Settings* g_settings = NULL;
Engine::Utils* g_utils = NULL;
Engine::Camera* g_camera = NULL;
Engine::Renderer* g_renderer = NULL;

void initializeMain()
{
	Engine::Logger::singleton()->print0();

	// Create the camera object
	g_camera = new Engine::Camera(g_settings->getWidth(), g_settings->getHeight());

	// TODO OpenGL -Z inside and DirectX +Z inside. X is right and Y is up.
	g_camera->setView(Engine::Vec3(0, 0, 10), Engine::Vec3(0, 0, 1), Engine::Vec3(1, 0, 0), Engine::Vec3(0, 1, 0));

	// Create the renderer object
#if defined(__APPLE__) || defined(__linux__)
    g_renderer = new Engine::GlRenderer(g_settings->getWidth(), g_settings->getHeight());
#endif //_WIN32

	// Set the camera pointer of renderer object
	g_renderer->setCamera(g_camera);

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

	// Release the camera object
	delete g_camera;

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

Engine::Camera* getCamera()
{
	return g_camera;
}

Engine::Renderer* getRenderer()
{
	return g_renderer;
}
