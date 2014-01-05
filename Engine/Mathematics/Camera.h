//
//  Camera.h
//  Application
//
//  Created by Narendra Umate on 9/12/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#ifndef __Application__Camera__
#define __Application__Camera__

#include "Matrix.h"
#include "Point.h"

namespace Engine
{

	class Camera
	{

	public:

		Camera(const bool& isPerspective = true);
		virtual ~Camera();

		bool getIsPerspective() const { return m_isPerspective; }
		Mat4* getViewMatrix() const { return (Mat4*)&m_viewMatrix; }
		Mat4* getProjectionMatrix() const { return (Mat4*)&m_projectionMatrix; }
		Mat4* getPostProjectionMatrix() const { return (Mat4*)&m_postProjectionMatrix; }

	private:

		bool m_isPerspective;
		Point m_position;
		Vec4 m_directionVector;
		Vec4 m_uvVector;
		Vec4 m_reflectionVector;
		Mat4 m_viewMatrix;
		Mat4 m_projectionMatrix;
		Mat4 m_postProjectionMatrix;

	};

}

#endif /* defined(__Application__Camera__) */
