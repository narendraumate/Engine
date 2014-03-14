//
//  GlShader.h
//  Application
//
//  Created by Narendra Umate on 9/28/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#ifndef __Application__GlShader__
#define __Application__GlShader__

#include <sstream>
#include <map>
#include <vector>

#include "GlHeader.h"
#include "Utils.h"

namespace Engine
{

	class GlShader
	{
	public:
		static std::vector<GLuint> loadShaders(const std::map<std::string, GLenum>& shaderFileTypePairs);
	};

}

#endif /* defined(__Application__GlShader__) */
