//
//  Source.cpp
//  Application
//
//  Created by Narendra Umate on 9/7/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#include "Header.h"

int main(int argc, const char * argv[])
{
	char applicationName[9] = "Renderer";

	// Create the system object
#ifdef __APPLE__
	Engine::Renderer* renderer = new Engine::GlRenderer(800, 600, applicationName);
#elif _WIN32
	Engine::Renderer* renderer = new Engine::DxRenderer(800, 600, applicationName);
#endif

	// Initialize and run the system object
	if (renderer->initialize())
	{
		renderer->run();
	}

	// Shutdown and release the system object
	renderer->shutdown();

	delete renderer;

#ifdef USE_MEMTRACK
	Engine::TrackDumpBlocks();
	
	Engine::TrackListMemoryUsage();
#endif //USE_MEMTRACK

	return 0;
}
