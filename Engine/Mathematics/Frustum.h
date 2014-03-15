//
//  Frustum.h
//  Renderer
//
//  Created by Narendra Umate on 5/4/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#ifndef __Renderer__Frustum__
#define __Renderer__Frustum__

#include "Matrix.h"
#include "Plane.h"

namespace Engine
{
	class Frustum
	{
	public:
		Frustum();
		Frustum(const Frustum& other);
		~Frustum();
		
		void constructFrustum(const float& screenDepth,
							  const Mat4* projectionMatrix,
							  const Mat4* viewMatrix);
		
		bool checkPoint(const Vec3& point);
		bool checkCube(const Vec3& center, const float& radius);
		bool checkSphere(const Vec3& center, const float& radius);
		bool checkRectangle(const Vec3& center, const Vec3& size);
		
	private:
		Plane m_planes[6];
	};
}

#endif /* defined(__Renderer__Frustum__) */
