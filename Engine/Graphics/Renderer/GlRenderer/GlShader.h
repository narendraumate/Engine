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
#include <OpenGL/gl3.h>
#elif defined(__linux__)
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h> // sudo apt-get install mesa-common-dev mesa-utils freeglut3 freeglut3-dev
#include <GL/glx.h>
#endif // defined(__linux__)

#include <map>
#include <sstream>
#include <vector>

#include "../../../Application/Common/Utils.h"

namespace Engine
{
	class GlShader
	{
	private:
		GlShader();
		~GlShader();
		static char* loadShaderSourceFile(const char* shaderSourceFile);
		
	public:
		static GLuint loadShader(const std::string& shaderName);
		static GLuint loadShader(const std::string& shaderFilename, const GLenum& shaderType);
		static std::vector<GLuint> loadShaderMap(const std::map<std::string, GLenum>& shaderFileTypePairs);
	};
}

#endif /* defined(__Application__GlShader__) */
