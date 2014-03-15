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

#include <vector>

#include "../Renderer.h"
#include "GlProgram.h"
#include "GlShader.h"

namespace Engine
{

	class GlRenderer : public Renderer
	{

	public:

		GlRenderer(const int& width, const int& height, const char* applicationName);
		~GlRenderer();

		bool initialize();
		void run();
		void shutdown();

		void setViewport(const int& xPos, const int& yPos, const int& w, const int& h);
		void getViewport(int& xPos, int& yPos, int& w, int& h) const;
		void setDepthRange(const float& zMin, const float& zMax);
		void getDepthRange(float& zMin, float& zMax) const;
		void resize(const int& width, const int& height);

		void clearColorBuffer();
		void clearDepthBuffer();
		void clearStencilBuffer();
		void clearBuffers();
		void clearColorBuffer(const int& x, const int& y, const int& w, const int& h);
		void clearDepthBuffer(const int& x, const int& y, const int& w, const int& h);
		void clearStencilBuffer(const int& x, const int& y, const int& w, const int& h);
		void clearBuffers(const int& x, const int& y, const int& w, const int& h);
		void displayColorBuffer();

		bool preDraw();
		void postDraw();

	};

}

#endif //defined(__APPLE__) || defined(__linux__)

#endif /* defined(__Application__GlRenderer__) */
