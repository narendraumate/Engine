#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#include "Shader.h"
#include "../../../../Core/callback/callback.h"

#ifndef __Application__OpenGLFramework__
#define __Application__OpenGLFramework__

class OpenGLFramework
{
public:
	OpenGLFramework(const CBFunctor1<CGLContextObj> &uponInitDoThis);
	~OpenGLFramework();
	void initializeWindow(const int& width, const int& height, const char* applicationName);
	void passbackContext(const CGLContextObj& contextObj);
	void deinitializeWindow();

	static void initializeOpenGL(const CGLContextObj& contextObject);
	static void deinitializeOpenGL(const CGLContextObj& contextObject);
	static void render(const CGLContextObj& contextObject);
	static void reshape(const CGLContextObj& contextObject, const int& width, const int& height);

private:
	CBFunctor1<CGLContextObj> setContextObj;
};

#endif /* defined(__Application__OpenGLFramework__) */
