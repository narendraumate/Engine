//
//  Main.cpp
//  Application
//
//  Created by Narendra Umate on 9/7/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#include "Main.h"

Engine::Renderer* g_renderer = NULL;

void initializeMain()
{
	char applicationName[9] = "Renderer";

	// Create the renderer object
#ifdef __APPLE__
	g_renderer = new Engine::GlRenderer(800, 600, applicationName);
#elif _WIN32
	g_renderer = new Engine::DxRenderer(800, 600, applicationName);
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
	// Shutdown and release the renderer object
	g_renderer->shutdown();
	delete g_renderer;

#ifdef USE_MEMTRACK
	Engine::TrackDumpBlocks();

	Engine::TrackListMemoryUsage();
#endif //USE_MEMTRACK
}

Engine::Renderer* getRenderer()
{
	return g_renderer;
}
