//
//  GlRenderer.h
//  Application
//
//  Created by Narendra Umate on 9/7/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#ifndef __Application__GlRenderer__
#define __Application__GlRenderer__

#if defined(__APPLE__) || defined(__linux__)

#if defined(__APPLE__)
#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>
#elif defined(__linux__)

#endif //defined(__linux__)

#include <vector>

#include "Shader.h"
#include "../Renderer.h"

namespace Engine
{

	class GlRenderer : public Renderer
	{

	public:

		GlRenderer(const int& width, const int& height, const char* applicationName);
		virtual ~GlRenderer();

		virtual bool initialize();
		virtual void run();
		virtual void shutdown();

		virtual void setContextObj(const ContextObj& contextObj);
		virtual ContextObj getContextObj();

		virtual void setViewport(const int& xPos, const int& yPos, const int& w, const int& h);
		virtual void getViewport(int& xPos, int& yPos, int& w, int& h) const;
		virtual void setDepthRange(const float& zMin, const float& zMax);
		virtual void getDepthRange(float& zMin, float& zMax) const;
		virtual void resize(const int& width, const int& height);

		virtual void clearColorBuffer();
		virtual void clearDepthBuffer();
		virtual void clearStencilBuffer();
		virtual void clearBuffers();
		virtual void clearColorBuffer(const int& x, const int& y, const int& w, const int& h);
		virtual void clearDepthBuffer(const int& x, const int& y, const int& w, const int& h);
		virtual void clearStencilBuffer(const int& x, const int& y, const int& w, const int& h);
		virtual void clearBuffers(const int& x, const int& y, const int& w, const int& h);
		virtual void displayColorBuffer();

		virtual bool preDraw();
		virtual void postDraw();

		virtual void draw(const unsigned char* screenBuffer, const bool& reflectY = false);

		virtual void draw(const int& x, const int& y, const Color4f& color, const std::string& message);

	private:

		virtual void drawPrimitive();

	};

}

#endif //defined(__APPLE__) || defined(__linux__)

#endif /* defined(__Application__GlRenderer__) */
