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
#elif defined(__linux__)
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h> // sudo apt-get install mesa-common-dev mesa-utils freeglut3 freeglut3-dev
#include <GL/glx.h>
#endif // defined(__linux__)

#include <iostream>
#include <vector>

namespace Engine
{
	class GlProgram
	{
	private:
		GlProgram();
		~GlProgram();
		
	public:
		static GLuint createProgram(const std::vector<GLuint>& shaders);
		static void deleteProgram(const GLuint& program);
	};
}
#endif /* defined(__Application__GlProgram__) */
