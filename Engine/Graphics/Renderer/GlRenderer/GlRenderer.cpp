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
static const float vertexPositions[] =
{
	0.75f, 0.75f, 0.0f, 1.0f,
	0.75f, -0.75f, 0.0f, 1.0f,
	-0.75f, -0.75f, 0.0f, 1.0f,
};

static GLuint position_buffer_object, vertex_array_object, shader_program;
//----------------------------------------------------------------------------//
namespace Engine
{

	GlRenderer::GlRenderer(const int& width, const int& height, const char* applicationName)
	:	Renderer(width, height, applicationName)
	{
	}

	GlRenderer::~GlRenderer()
	{
	}

	bool GlRenderer::initialize()
	{
//----------------------------------------------------------------------------//
		glGenBuffers(1, &position_buffer_object);
		glBindBuffer(GL_ARRAY_BUFFER, position_buffer_object);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*12, vertexPositions, GL_STATIC_DRAW);

		std::vector<GLuint> shaders;
		shaders.push_back(Shader::LoadShader(GL_VERTEX_SHADER, "pass_along.vert"));
		shaders.push_back(Shader::LoadShader(GL_FRAGMENT_SHADER, "uniform_color.frag"));
		shader_program = Shader::CreateProgram(shaders);
        for (std::vector<GLuint>::const_iterator shader = shaders.begin(); shader != shaders.end(); shader++)
        {
            glDeleteShader(*shader);
        }

		glGenVertexArrays(1, &vertex_array_object);
		glBindVertexArray(vertex_array_object);
//----------------------------------------------------------------------------//
		return true;
	}

	void GlRenderer::run()
	{

	}

	void GlRenderer::shutdown()
	{

	}

	void GlRenderer::setContextObj(const ContextObj& contextObj)
	{
		m_contextObj = contextObj;
	}

	ContextObj GlRenderer::getContextObj()
	{
		return m_contextObj;
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
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader_program);
		glBindBuffer(GL_ARRAY_BUFFER, position_buffer_object);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);
		glUseProgram(0);

#if defined(__APPLE__)
        CGLFlushDrawable(m_contextObj);
#elif defined(_WIN32)
        //TODO
#elif defined(__linux___)
        //TODO
#endif //defined(__linux__)
//----------------------------------------------------------------------------//
	}

	void GlRenderer::draw(const unsigned char* screenBuffer, const bool& reflectY)
	{

	}

	void GlRenderer::draw(const int& x, const int& y, const Color4f& color, const std::string& message)
	{
		
	}

	void GlRenderer::drawPrimitive()
	{
		
	}

}

#endif //defined(__APPLE__) || defined(__linux__)
