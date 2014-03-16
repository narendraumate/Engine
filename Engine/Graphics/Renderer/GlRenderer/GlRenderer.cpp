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
Engine::GlModel* g_glModel = nullptr;
//----------------------------------------------------------------------------//

namespace Engine
{
	GlRenderer::GlRenderer(const int& width, const int& height, const char* applicationName)
	:	Renderer(width, height, applicationName)
	{ }

	GlRenderer::~GlRenderer()
	{ }

	bool GlRenderer::initialize()
	{
//----------------------------------------------------------------------------//
		g_glModel = new GlModel(Engine::Utils::singleton()->findFile("Dragon.obj"));
//----------------------------------------------------------------------------//
		return true;
	}

	void GlRenderer::run()
	{
		clearColorBuffer();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	// GL_FILL or GL_LINE
//----------------------------------------------------------------------------//
		g_glModel->render();
//----------------------------------------------------------------------------//
		glFlush();
	}

	void GlRenderer::shutdown()
	{
//----------------------------------------------------------------------------//
		if (g_glModel)
		{
			delete g_glModel;
		}
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

}

#endif //defined(__APPLE__) || defined(__linux__)
