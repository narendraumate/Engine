#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#include "Shader.h"

#ifndef __Application__OpenGLFramework__
#define __Application__OpenGLFramework__

class OpenGLFramework
{
public:
	void initializeWindow(const int& width, const int& height, const char* applicationName);
	void deinitializeWindow();

	static void initializeOpenGL(const CGLContextObj& contextObject);
	static void deinitializeOpenGL(const CGLContextObj& contextObject);
	static void render(const CGLContextObj& contextObject);
	static void reshape(const CGLContextObj& contextObject, const int& width, const int& height);
};

#endif /* defined(__Application__OpenGLFramework__) */
