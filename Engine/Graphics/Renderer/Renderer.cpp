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
	{
		m_applicationName = new char[strlen(applicationName) + 1];
		strcpy(m_applicationName, applicationName);
	}

	Renderer::~Renderer()
	{
		m_width = 0;
		m_height = 0;
		delete [] m_applicationName;
	}

	bool Renderer::initialize()
	{
		return true;
	}

	void Renderer::run()
	{
		//
	}

	void Renderer::shutdown()
	{
		//
	}

	void Renderer::setContextObj(const ContextObj& contextObj)
	{
		m_contextObj = contextObj;
	}

	ContextObj Renderer::getContextObj()
	{
		return m_contextObj;
	}

	inline int Renderer::getWidth() const
	{
		return m_width;
	}

	inline int Renderer::getHeight() const
	{
		return m_height;
	}

	inline char* Renderer::getApplicationName() const
	{
		return m_applicationName;
	}

	inline void Renderer::setCamera(Camera* camera)
	{
		m_camera = camera;
	}

	inline Camera* Renderer::getCamera() const
	{
		return m_camera;
	}

	inline Mat4* Renderer::getViewMatrix() const
	{
		return m_camera->getViewMatrix();
	}

	inline Mat4* Renderer::getProjectionMatrix() const
	{
		return m_camera->getProjectionMatrix();
	}

	inline Mat4* Renderer::getPostProjectionMatrix() const
	{
		return m_camera->getPostProjectionMatrix();
	}

	inline void Renderer::setClearColor(const Color4f& clearColor)
	{
		m_clearColor = clearColor;
	}

	inline Color4f Renderer::getClearColor() const
	{
		return m_clearColor;
	}

	inline void Renderer::setClearDepth(const float& clearDepth)
	{
		m_clearDepth = clearDepth;
	}

	inline float Renderer::getClearDepth() const
	{
		return m_clearDepth;
	}

	inline void Renderer::setClearStencil(unsigned int& clearStencil)
	{
		m_clearStencil = clearStencil;
	}
	
	inline unsigned int Renderer::getClearStencil() const
	{
		return m_clearStencil;
	}
	
}
