//
//  DxRenderer.cpp
//  Application
//
//  Created by Narendra Umate on 9/7/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#ifdef _WIN32

#include "DxRenderer.h"

namespace Engine
{

	DxRenderer::DxRenderer(const int& width, const int& height)
	:	Renderer(width, height)
	{

	}

	DxRenderer::~DxRenderer()
	{

	}

	bool DxRenderer::initialize()
	{
		return true;
	}

	void DxRenderer::run()
	{

	}

	void DxRenderer::shutdown()
	{

	}

	void DxRenderer::setViewport(const int& xPos, const int& yPos, const int& w, const int& h)
	{

	}

	void DxRenderer::getViewport(int& xPos, int& yPos, int& w, int& h) const
	{

	}

	void DxRenderer::setDepthRange(const float& zMin, const float& zMax)
	{

	}

	void DxRenderer::getDepthRange(float& zMin, float& zMax) const
	{

	}

	void DxRenderer::resize(const int& width, const int& height)
	{

	}

	void DxRenderer::clearColorBuffer()
	{

	}

	void DxRenderer::clearDepthBuffer()
	{

	}

	void DxRenderer::clearStencilBuffer()
	{

	}

	void DxRenderer::clearBuffers()
	{

	}

	void DxRenderer::clearColorBuffer(const int& x, const int& y, const int& w, const int& h)
	{

	}

	void DxRenderer::clearDepthBuffer(const int& x, const int& y, const int& w, const int& h)
	{

	}

	void DxRenderer::clearStencilBuffer(const int& x, const int& y, const int& w, const int& h)
	{

	}

	void DxRenderer::clearBuffers(const int& x, const int& y, const int& w, const int& h)
	{

	}

	void DxRenderer::displayColorBuffer()
	{

	}

	bool DxRenderer::preDraw()
	{
		return true;
	}

	void DxRenderer::postDraw()
	{

	}

	void DxRenderer::draw(const unsigned char* screenBuffer, const bool& reflectY)
	{

	}

	void DxRenderer::draw(const int& x, const int& y, const Color4f& color, const std::string& message)
	{

	}

	void DxRenderer::drawPrimitive()
	{

	}

}

#endif //_WIN32
