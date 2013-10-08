#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#include "Shader.h"
#include "../../../../External/callback/callback.h"
#include "../../../Renderer/Renderer.h"

#ifndef __Application__OpenGLFramework__
#define __Application__OpenGLFramework__

class OpenGLFramework
{
public:
	OpenGLFramework(Engine::Renderer* renderer, const CBFunctor1<CGLContextObj> &uponInitDoThis);
	~OpenGLFramework();
	void initializeWindow(const int& width, const int& height, const char* applicationName);
	void passbackContext(const CGLContextObj& contextObj);
	void deinitializeWindow();

private:
	Engine::Renderer* m_renderer;
	CBFunctor1<CGLContextObj> m_setContextObj;
};

#endif /* defined(__Application__OpenGLFramework__) */
