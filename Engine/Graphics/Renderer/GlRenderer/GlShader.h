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
#endif //defined(__APPLE__)

#include <map>
#include <sstream>
#include <vector>

#include "Utils.h"

namespace Engine
{
	class GlShader
	{
	private:
		GlShader();
		~GlShader();
	
	public:
		static GLuint loadShader(const std::string& shaderFilename, const GLenum& shaderType);
		static std::vector<GLuint> loadShaderMap(const std::map<std::string, GLenum>& shaderFileTypePairs);
	};
}

#endif /* defined(__Application__GlShader__) */
