//
//  GlHeader.h
//  Application
//
//  Created by Narendra Umate on 3/14/14.
//
//

#ifndef Application_GlHeader_h
#define Application_GlHeader_h

#if defined(__APPLE__)
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#elif defined(__linux__)
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h> // sudo apt-get install mesa-common-dev mesa-utils freeglut3 freeglut3-dev
#endif //defined(__linux__)

#endif
