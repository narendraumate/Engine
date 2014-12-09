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

		DxRenderer(const int& width, const int& height);
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
	};

}

#endif //_WIN32

#endif /* defined(__Application__DxRenderer__) */
