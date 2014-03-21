//
//  GlRenderer.cpp
//  Application
//
//  Created by Narendra Umate on 9/7/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#if defined(__APPLE__) || defined(__linux__)

#include "GlRenderer.h"

//----------------------------------------------------------------------------//
#include "GlModel.h"
GLuint g_programId = 0;
Engine::GlModel* g_glModel = nullptr;
//----------------------------------------------------------------------------//

namespace Engine
{
	GlRenderer::GlRenderer(const int& width, const int& height, const char* applicationName)
	:	Renderer(width, height, applicationName)
	{
//----------------------------------------------------------------------------//
		int major = 0;
		int minor = 0;
		char cardName[128];
		getVideoCardInfo(cardName);
		getGlVersion(&major, &minor);
		getGlslVersion(&major, &minor);
//----------------------------------------------------------------------------//
	}

	GlRenderer::~GlRenderer()
	{ }

	bool GlRenderer::initialize()
	{
//----------------------------------------------------------------------------//
		std::vector<GLuint> shaders;
		shaders.push_back(GlShader::loadShader("3d.vert", GL_VERTEX_SHADER));
		shaders.push_back(GlShader::loadShader("3d.frag", GL_FRAGMENT_SHADER));
		g_programId = GlProgram::createProgram(shaders);

		g_glModel = new GlModel(g_programId, 
								Utils::singleton()->findFilePath("CokeCan.obj"),
								Utils::singleton()->findBasePath("CokeCan.mtl"));

		g_glModel->setPosition(Vec3(0.0f, 0.0f, 0.0f));
		g_glModel->setRotation(Vec3(45.0f, 45.0f, 0.0f));
		
		g_glModel->pushViewMatrix(m_camera.getView());
		g_glModel->pushPerspectiveMatrix(m_camera.getPerspectiveProjection());
		g_glModel->pushOrthographicMatrix(m_camera.getOrthographicProjection());
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	// GL_FILL or GL_LINE
//----------------------------------------------------------------------------//
		return true;
	}

	void GlRenderer::run()
	{
		clearColorBuffer();
		clearDepthBuffer();
//		glEnable(GL_CULL_FACE);
//		glCullFace(GL_BACK);
//		glFrontFace(GL_CW);	// GL_CW or GL_CCW
//----------------------------------------------------------------------------//
		g_glModel->draw();
//----------------------------------------------------------------------------//
	}

	void GlRenderer::shutdown()
	{
//----------------------------------------------------------------------------//
		if (g_glModel)
		{
			delete g_glModel;
		}
		GlProgram::deleteProgram(g_programId);
//----------------------------------------------------------------------------//
	}

	void GlRenderer::setViewport(const int& xPos, const int& yPos, const int& w, const int& h)
	{
		glViewport(xPos, yPos, w, h);
	}

	void GlRenderer::getViewport(int& xPos, int& yPos, int& w, int& h) const
	{
		int params[4];
		glGetIntegerv(GL_VIEWPORT, params);

		xPos = params[0];
		yPos = params[1];
		w = params[2];
		h = params[3];
	}

	void GlRenderer::setDepthRange(const float& zMin, const float& zMax)
	{
		glDepthRange(zMin, zMax);
	}

	void GlRenderer::getDepthRange(float& zMin, float& zMax) const
	{
		int params[2];
		glGetIntegerv(GL_DEPTH_RANGE, params);
		zMin = params[0];
		zMax = params[1];
	}

	void GlRenderer::resize(const int& width, const int& height)
	{
		m_width = width;
		m_height = height;

		int params[4];
		glGetIntegerv(GL_VIEWPORT, params);
		glViewport(params[0], params[1], width, height);
	}

	void GlRenderer::clearColorBuffer()
	{
		glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void GlRenderer::clearDepthBuffer()
	{
		glClearDepth(m_clearDepth);
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void GlRenderer::clearStencilBuffer()
	{
		glClearStencil(m_clearStencil);
		glClear(GL_STENCIL_BUFFER_BIT);
	}

	void GlRenderer::clearBuffers()
	{
		glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
		glClearDepth(m_clearDepth);
		glClearStencil(m_clearStencil);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void GlRenderer::clearColorBuffer(const int& x, const int& y, const int& w, const int& h)
	{
		glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
		glEnable(GL_SCISSOR_TEST);
		glScissor(x, y, w, h);
		glClear(GL_COLOR_BUFFER_BIT);
		glDisable(GL_SCISSOR_TEST);
	}

	void GlRenderer::clearDepthBuffer(const int& x, const int& y, const int& w, const int& h)
	{
		glClearDepth(m_clearDepth);
		glEnable(GL_SCISSOR_TEST);
		glScissor(x, y, w, h);
		glClear(GL_DEPTH_BUFFER_BIT);
		glDisable(GL_SCISSOR_TEST);
	}

	void GlRenderer::clearStencilBuffer(const int& x, const int& y, const int& w, const int& h)
	{
		glClearStencil(m_clearStencil);
		glEnable(GL_SCISSOR_TEST);
		glScissor(x, y, w, h);
		glClear(GL_STENCIL_BUFFER_BIT);
		glDisable(GL_SCISSOR_TEST);
	}

	void GlRenderer::clearBuffers(const int& x, const int& y, const int& w, const int& h)
	{
		glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
		glClearDepth(m_clearDepth);
		glClearStencil(m_clearStencil);
		glEnable(GL_SCISSOR_TEST);
		glScissor(x, y, w, h);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glDisable(GL_SCISSOR_TEST);
	}

	void GlRenderer::displayColorBuffer()
	{

	}

	bool GlRenderer::preDraw()
	{
		return true;
	}

	void GlRenderer::postDraw()
	{
//----------------------------------------------------------------------------//
#if defined(__APPLE__)
        CGLFlushDrawable(m_contextObj);
#elif defined(_WIN32)
        //TODO
#elif defined(__linux___)
        //TODO
#endif //defined(__linux__)
//----------------------------------------------------------------------------//
	}
	
	void GlRenderer::getVideoCardInfo(char* cardName)
	{
		strncpy(cardName, (const char *)glGetString(GL_RENDERER), 128);
		std::cout << cardName << std::endl;
	}
	
	void GlRenderer::getGlVersion(int *major, int *minor)
	{
		const char *verstr = (const char *) glGetString(GL_VERSION);
		if ((verstr == NULL) || (sscanf(verstr,"%d.%d", major, minor) != 2))
		{
			*major = *minor = 0;
			std::cout << "Invalid GL_VERSION format." << std::endl;
		}
		std::cout << "GL_VERSION " << verstr << std::endl;
	}
	
	void GlRenderer::getGlslVersion(int *major, int *minor)
	{
		int gl_major, gl_minor;
		getGlVersion(&gl_major, &gl_minor);
		*major = *minor = 0;
		if (gl_major == 1)
		{
			/* GL v1.x can provide GLSL v1.00 only as an extension */
			const char *extstr = (const char *) glGetString(GL_EXTENSIONS);
			if ((extstr != NULL) &&
				(strstr(extstr, "GL_ARB_shading_language_100") != NULL))
			{
				*major = 1;
				*minor = 0;
			}
			std::cout << "GL_EXTENSIONS " << extstr << std::endl;
		}
		else if (gl_major >= 2)
		{
			/* GL v2.0 and greater must parse the version string */
			const char *verstr =
			(const char *) glGetString(GL_SHADING_LANGUAGE_VERSION);
			if ((verstr == NULL) || (sscanf(verstr, "%d.%d", major, minor) != 2))
			{
				*major = *minor = 0;
				std::cout << "Invalid GL_SHADING_LANGUAGE_VERSION format." << std::endl;
			}
			std::cout << "GL_SHADING_LANGUAGE_VERSION " << verstr << std::endl;
		}
	}
}

#endif //defined(__APPLE__) || defined(__linux__)
