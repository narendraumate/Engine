//
//  GlProgram.h
//  Application
//
//  Created by Narendra Umate on 3/14/14.
//
//

#ifndef __Application__GlProgram__
#define __Application__GlProgram__

#include "GlHeader.h"
#include <vector>

namespace Engine
{
	class GlProgram
	{
	public:
		static GLuint createProgram(const std::vector<GLuint>& shaders);
		static void deleteProgram(const GLuint& program);
	};
}
#endif /* defined(__Application__GlProgram__) */
