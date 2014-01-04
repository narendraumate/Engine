//
//  DxRenderer.h
//  Application
//
//  Created by Narendra Umate on 9/7/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#ifndef __Application__DxRenderer__
#define __Application__DxRenderer__

#ifdef _WIN32

#include "../Renderer.h"

namespace Engine
{

	class DxRenderer : public Renderer
	{

	public:

		DxRenderer(const int& width, const int& height, const char* applicationName);
		~DxRenderer();

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

		void draw(const unsigned char* screenBuffer, const bool& reflectY = false);

		void draw(const int& x, const int& y, const Color4f& color, const std::string& message);

	private:

		void drawPrimitive();

	};

}

#endif //_WIN32

#endif /* defined(__Application__DxRenderer__) */
