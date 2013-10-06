//
//  Header.h
//  Application
//
//  Created by Narendra Umate on 9/15/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#ifndef Application_Header_h
#define Application_Header_h

#include <iostream>
#include <memory>

#include "../Engine/Graphics/Renderer/DxRenderer/DxRenderer.h"
#include "../Engine/Graphics/Renderer/GlRenderer/GlRenderer.h"

#define USE_MEMTRACK

#ifdef USE_MEMTRACK
#include "../Engine/Core/MemTrack/MemTrack.h"
#endif //USE_MEMTRACK

#endif
