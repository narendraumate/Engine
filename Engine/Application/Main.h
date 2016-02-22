//
//  Main.h
//  Application
//
//  Created by Narendra Umate on 9/15/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#ifndef Application_Main_h
#define Application_Main_h

#include "Common/Logger.h"
#include "Common/Settings.h"
#include "Common/Utils.h"

#include "../../Engine/External/MemTrack/MemTrack.h"
#include "../../Engine/Graphics/Renderer/GlRenderer/GlRenderer.h"
#include "../../Engine/Graphics/SceneGraph/Camera.h"
#include "../../Engine/Mathematics/Vector.h"

void initializeMain();
bool runMain();
void deinitializeMain();

Engine::Logger* getLogger();
Engine::Settings* getSettings();
Engine::Utils* getUtils();
Engine::Camera* getCamera();
Engine::Renderer* getRenderer();

#endif
