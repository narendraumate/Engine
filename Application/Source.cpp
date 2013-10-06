//
//  Source.cpp
//  Application
//
//  Created by Narendra Umate on 9/7/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#include "Header.h"

int runApplication(int argc, const char * argv[])
{
	char applicationName[9] = "Renderer";

	// Create the renderer object
#ifdef __APPLE__
	std::auto_ptr<Engine::Renderer> renderer(new Engine::GlRenderer(800, 600, applicationName));
#elif _WIN32
	std::auto_ptr<Engine::Renderer> renderer(new Engine::DxRenderer(800, 600, applicationName));
#endif

	// Initialize and run the renderer object
	if (renderer->initialize())
	{
		renderer->run();
	}

	// Shutdown and release the renderer object
	renderer->shutdown();

	// Delete not required for auto_ptr
	//delete renderer;

	return 0;
}

int main(int argc, const char * argv[])
{
	int result = runApplication(argc, argv);

#ifdef USE_MEMTRACK
	Engine::TrackDumpBlocks();

	Engine::TrackListMemoryUsage();
#endif //USE_MEMTRACK

	return result;
}

