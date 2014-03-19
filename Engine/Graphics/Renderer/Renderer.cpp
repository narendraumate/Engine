//
//  Renderer.cpp
//  Application
//
//  Created by Narendra Umate on 9/7/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#include "Renderer.h"

namespace Engine
{

	Renderer::Renderer(const int& width, const int& height, const char* applicationName)
	:	m_width(width)
	,	m_height(height)
	,	m_applicationName(strdup(applicationName))
	,	m_camera(width, height)
	{ }

	Renderer::~Renderer()
	{
		m_width = 0;
		m_height = 0;
		delete [] m_applicationName;
	}

	void Renderer::setContextObj(const ContextObj& contextObj)
	{
		m_contextObj = contextObj;
	}

	ContextObj Renderer::getContextObj()
	{
		return m_contextObj;
	}

	int Renderer::getWidth() const
	{
		return m_width;
	}

	int Renderer::getHeight() const
	{
		return m_height;
	}

	const char* Renderer::getApplicationName() const
	{
		return m_applicationName;
	}

	void Renderer::setCamera(Camera* camera)
	{
		m_camera = *camera;
	}

	const Camera* Renderer::getCamera() const
	{
		return &m_camera;
	}

	const Mat4* Renderer::getViewMatrix() const
	{
		return m_camera.getView();
	}

	const Mat4* Renderer::getPerspectiveProjectionMatrix() const
	{
		return m_camera.getPerspectiveProjection();
	}

	const Mat4* Renderer::getOrthographicProjectionMatrix() const
	{
		return m_camera.getOrthographicProjection();
	}

	void Renderer::setClearColor(const Color4f& clearColor)
	{
		m_clearColor = clearColor;
	}

	Color4f Renderer::getClearColor() const
	{
		return m_clearColor;
	}

	void Renderer::setClearDepth(const float& clearDepth)
	{
		m_clearDepth = clearDepth;
	}

	float Renderer::getClearDepth() const
	{
		return m_clearDepth;
	}

	void Renderer::setClearStencil(unsigned int& clearStencil)
	{
		m_clearStencil = clearStencil;
	}
	
	unsigned int Renderer::getClearStencil() const
	{
		return m_clearStencil;
	}
	
}
