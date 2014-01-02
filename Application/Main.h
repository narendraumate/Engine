//
//  Main.h
//  Application
//
//  Created by Narendra Umate on 9/15/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#ifndef Application_Main_h
#define Application_Main_h

#include <iostream>
#include <memory>

#include "../Engine/Core/Logger.h"
#include "../Engine/Core/Settings.h"
#include "../Engine/Core/Utils.h"

#include "../Engine/Graphics/Renderer/DxRenderer/DxRenderer.h"
#include "../Engine/Graphics/Renderer/GlRenderer/GlRenderer.h"

#define USE_MEMTRACK

#ifdef USE_MEMTRACK
#include "../Engine/External/MemTrack/MemTrack.h"
#endif //USE_MEMTRACK

void initializeMain();
bool runMain();
void deinitializeMain();

Engine::Logger* getLogger();
Engine::Settings* getSettings();
Engine::Utils* getUtils();

Engine::Renderer* getRenderer();

#endif
