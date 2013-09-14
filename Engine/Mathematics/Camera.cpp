//
//  Camera.cpp
//  Application
//
//  Created by Narendra Umate on 9/12/13.
//
//

#include "Camera.h"

namespace Engine
{

	Camera::Camera(const bool& isPerspective)
	:	m_isPerspective(isPerspective)
	{

	}

	Camera::~Camera()
	{

	}

	inline bool Camera::getIsPerspective() const
	{
		return m_isPerspective;
	}

	inline Mat4* Camera::getViewMatrix() const
	{
		return (Mat4*)&m_viewMatrix;
	}

	inline Mat4* Camera::getProjectionMatrix() const
	{
		return (Mat4*)&m_projectionMatrix;
	}

	inline Mat4* Camera::getPostProjectionMatrix() const
	{
		return (Mat4*)&m_postProjectionMatrix;
	}
	
}
