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
vector<Engine::GlModel*> g_glModels;
//----------------------------------------------------------------------------//

namespace Engine
{
	GlRenderer::GlRenderer(const int& width, const int& height, const char* applicationName)
	:	Renderer(width, height, applicationName)
	{
//----------------------------------------------------------------------------//
#if defined(__linux__)
		// gl calls need a valid context
		int major = 0;
		int minor = 0;
		char cardName[128];
		getVideoCardInfo(cardName);
		getGlVersion(&major, &minor);
		getGlslVersion(&major, &minor);
		getGlParameters();
#endif // defined(__linux__)
//----------------------------------------------------------------------------//
		glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
		glClearDepth(m_clearDepth);
		glClearStencil(m_clearStencil);
	}

	GlRenderer::~GlRenderer()
	{ }

	bool GlRenderer::initialize()
	{
//----------------------------------------------------------------------------//
		std::vector<GLuint> gouraudShaders;
		std::vector<GLuint> phongShaders;
		std::vector<GLuint> smoothShaders;

		smoothShaders.push_back(GlShader::loadShader("smooth.vert", GL_VERTEX_SHADER));
		smoothShaders.push_back(GlShader::loadShader("smooth.frag", GL_FRAGMENT_SHADER));
		gouraudShaders.push_back(GlShader::loadShader("gouraud.vert", GL_VERTEX_SHADER));
		gouraudShaders.push_back(GlShader::loadShader("gouraud.frag", GL_FRAGMENT_SHADER));
		phongShaders.push_back(GlShader::loadShader("phong.vert", GL_VERTEX_SHADER));
		phongShaders.push_back(GlShader::loadShader("phong.frag", GL_FRAGMENT_SHADER));

		int programIndex = 1;

		switch (programIndex) {
			case 0:
				g_programId = GlProgram::createProgram(smoothShaders);
				break;

			case 1:
				g_programId = GlProgram::createProgram(gouraudShaders);
				break;

			case 2:
				g_programId = GlProgram::createProgram(phongShaders);
				break;

			default:
				break;
		}

		int modelArrayIndex = 1;

		switch (modelArrayIndex) {
			case 0:
			{

				std::string modelNames[] = { "cube.obj", "coke.obj", "teapot.obj", "dragon.obj" };

				for (int modelIndex = 0; modelIndex < sizeof(modelNames) / sizeof(modelNames[0]); ++modelIndex)
				{
					g_glModels.push_back(new GlModel(g_programId, m_camera.getView(),
													 Utils::singleton()->findFilePath(modelNames[modelIndex]),
													 Utils::singleton()->findBasePath(modelNames[modelIndex])));
				}

				g_glModels[0]->setRotation(Vec3(30.0f, 30.0f, 0.0f));
				g_glModels[0]->setPosition(Vec3(-5.0f, 0.0f, 0.0f));
				g_glModels[0]->setScale(Vec3(1.0f, 1.0f, 1.0f));

				g_glModels[1]->setRotation(Vec3(30.0f, 30.0f, 0.0f));
				g_glModels[1]->setPosition(Vec3(-2.5f, 0.0f, 0.0f));
				g_glModels[1]->setScale(Vec3(0.5f, 0.5f, 0.5f));

				g_glModels[2]->setRotation(Vec3(30.0f, 30.0f, 0.0f));
				g_glModels[2]->setPosition(Vec3(2.5f, -2.5f, 0.0f));
				g_glModels[2]->setScale(Vec3(0.025f, 0.025f, 0.025f));

				g_glModels[3]->setRotation(Vec3(30.0f, 30.0f, 0.0f));
				g_glModels[3]->setPosition(Vec3(10.0f, -5.0f, 0.0f));
				g_glModels[3]->setScale(Vec3(4.0f, 4.0f, 4.0f));
			}
				break;

			case 1:
			{
				int modelIndex = 6;
				std::string modelNames[] = { "rungholt/house.obj", "lost-empire/lost_empire.obj", "buddha/buddha.obj",
					                         "crytek-sponza/sponza.obj", "hairball/hairball.obj", "head/head.obj",
					                         "rungholt/rungholt.obj", "san-miguel/san-miguel.obj", "person-a/person-a.obj",
											 "person-b/person-b.obj", "person-c/person-c.obj"};
				g_glModels.push_back(new GlModel(g_programId, m_camera.getView(),
												 Utils::singleton()->findFilePath(modelNames[modelIndex]),
												 Utils::singleton()->findBasePath(modelNames[modelIndex])));

				g_glModels[0]->setPosition(Vec3(0.0f, 0.0f, 0.0f));
				g_glModels[0]->setRotation(Vec3(30.0f, 0.0f, 0.0f));

				if (modelIndex == 0)//house
				{
					g_glModels[0]->setPosition(Vec3(0, -1, 0));
					g_glModels[0]->setScale(Vec3(0.09f, 0.09f, 0.09f));
				}
				else if (modelIndex == 6)//rungholt
				{
					g_glModels[0]->setScale(Vec3(0.0145f, 0.0145f, 0.0145f));
				}
				else if (modelIndex == 8)//person-a
				{
					g_glModels[0]->setPosition(Vec3(0, -4.5, 0));
					g_glModels[0]->setScale(Vec3(1.6f, 1.6f, 1.6f));
				}
				else if (modelIndex == 9)//person-b
				{
					g_glModels[0]->setPosition(Vec3(0, -3, 0));
					g_glModels[0]->setScale(Vec3(0.085f, 0.085f, 0.085f));
				}
				else if (modelIndex == 10)//person-c
				{
					g_glModels[0]->setPosition(Vec3(0, -4.5, 0));
					g_glModels[0]->setScale(Vec3(4.5f, 4.5f, 4.5f));
				}
			}
				break;

			default:
				break;
		}

		for (vector<Engine::GlModel*>::iterator it = g_glModels.begin(); it != g_glModels.end(); ++it)
		{
			(*it)->updateViewMatrix();
			(*it)->pushPerspectiveMatrix(m_camera.getPerspectiveProjection());
			(*it)->pushOrthographicMatrix(m_camera.getOrthographicProjection());
		}

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);	// GL_CW or GL_CCW
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	// GL_FILL or GL_LINE
//----------------------------------------------------------------------------//
		return true;
	}

	void GlRenderer::run()
	{
		clearBuffers();
//----------------------------------------------------------------------------//
		for (vector<Engine::GlModel*>::iterator it = g_glModels.begin(); it != g_glModels.end(); ++it)
		{
			(*it)->draw();
		}
//----------------------------------------------------------------------------//
	}

	void GlRenderer::shutdown()
	{
//----------------------------------------------------------------------------//
		for (vector<Engine::GlModel*>::iterator it = g_glModels.begin(); it != g_glModels.end(); ++it)
		{
			delete (*it);
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
		//glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
		//glClearDepth(m_clearDepth);
		//glClearStencil(m_clearStencil);
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
        glFlush();
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

	void GlRenderer::getGlParameters()
	{
		int maxValue = 0;
		glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &maxValue);
		std::cout << "GL_MAX_ELEMENTS_INDICES " << maxValue << std::endl;
		glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &maxValue);
		std::cout << "GL_MAX_ELEMENTS_VERTICES " << maxValue << std::endl;
	}
}

#endif //defined(__APPLE__) || defined(__linux__)
