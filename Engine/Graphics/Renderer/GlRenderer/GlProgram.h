//
//  GlProgram.h
//  Application
//
//  Created by Narendra Umate on 3/14/14.
//
//

#ifndef __Application__GlProgram__
#define __Application__GlProgram__

#if defined(__APPLE__)
#include <OpenGL/gl3.h>
#endif //defined(__APPLE__)

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
