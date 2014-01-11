//
//  GlShader.h
//  Application
//
//  Created by Narendra Umate on 9/28/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#ifndef __Application__GlShader__
#define __Application__GlShader__

#if defined(__APPLE__)
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#elif defined(__linux__)
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h> // sudo apt-get install mesa-common-dev mesa-utils freeglut3 freeglut3-dev
#endif //defined(__linux__)

#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include "Utils.h"

namespace Engine
{

	class GlShader
	{
	public:
		static std::vector<GLuint> loadShaders(const std::map<std::string, GLenum>& shaderPairs);
		static GLuint createProgram(const std::vector<GLuint>& shaders);
	};

}

#endif /* defined(__Application__GlShader__) */
