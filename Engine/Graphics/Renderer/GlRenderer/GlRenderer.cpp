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
enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attribute_IDs { vPosition = 0, vColor = 1 };

GLuint ProgramID;
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint  NumVertices = 6;
#define BUFFER_OFFSET(offset) ((void *)(offset))
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
		std::map<std::string, GLuint> shaderMap;
		shaderMap["gouraud.vert"] = GL_VERTEX_SHADER;
		shaderMap["gouraud.frag"] = GL_FRAGMENT_SHADER;
		std::vector<GLuint> shaders = GlShader::loadShaders(shaderMap);
		ProgramID = GlProgram::createProgram(shaders);

		struct VertexData
		{
			GLubyte color[4];
			GLfloat position[4];
		};

		VertexData vertices[NumVertices] =
		{
			{{ 255,   0,   0, 255 }, { -0.90, -0.90 }},  // Triangle 1
			{{   0, 255,   0, 255 }, {  0.85, -0.90 }},
			{{   0,   0, 255, 255 }, { -0.90,  0.85 }},

			{{  10,  10,  10, 255 }, {  0.90, -0.85 }},  // Triangle 2
			{{ 100, 100, 100, 255 }, {  0.90,  0.90 }},
			{{ 255, 255, 255, 255 }, { -0.85,  0.90 }}
		};

		glGenVertexArrays(NumVAOs, VAOs);
		glBindVertexArray(VAOs[Triangles]);

		glGenBuffers(NumBuffers, Buffers);
		glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glUseProgram(ProgramID);
		glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), BUFFER_OFFSET(sizeof(vertices[0].color)));
		glVertexAttribPointer(vColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexData), BUFFER_OFFSET(0));

		glEnableVertexAttribArray(vPosition);
		glEnableVertexAttribArray(vColor);
//----------------------------------------------------------------------------//
		return true;
	}

	void GlRenderer::run()
	{
//----------------------------------------------------------------------------//
		glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
		glClear(GL_COLOR_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	// GL_FILL or GL_LINE
		glDrawArrays(GL_TRIANGLES, 0, NumVertices);
		glFlush();
//----------------------------------------------------------------------------//
	}

	void GlRenderer::shutdown()
	{
//----------------------------------------------------------------------------//
		glDeleteBuffers(NumBuffers, Buffers);
		glDeleteVertexArrays(NumVAOs, VAOs);
		GlProgram::deleteProgram(ProgramID);
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
