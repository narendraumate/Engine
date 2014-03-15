//
//  Plane.h
//  Renderer
//
//  Created by Narendra Umate on 5/4/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#ifndef __Renderer__Plane__
#define __Renderer__Plane__

#include "Math.h"
#include "Vector.h"

namespace Engine
{
	class Plane
	{
	public:
		Plane();
		Plane(const float& a, const float& b, const float& c, const float& d);
		Plane(const Plane& other);
		~Plane();
		
		void normalize();
		float dot(const Vec3& point);
		
		float a, b, c, d;
	};	
}

#endif /* defined(__Renderer__Plane__) */
