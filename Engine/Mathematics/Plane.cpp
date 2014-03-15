//
//  Plane.cpp
//  Renderer
//
//  Created by Narendra Umate on 5/4/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#include "Plane.h"

namespace Engine
{
	
	Plane::Plane()
	:	a(0.0f), b(0.0f), c(0.0f), d(0.0f)
	{ }
	
	Plane::Plane(const float& a, const float& b, const float& c, const float& d)
	:	a(a), b(b), c(c), d(d)
	{ }
	
	Plane::Plane(const Plane& other)
	:	a(other.a), b(other.b), c(other.c), d(other.d)
	{ }
	
	Plane::~Plane()
	{ }
	
	void Plane::normalize()
	{
		// This function normalizes a plane so that |a, b, c| == 1.
		// d also needs to be divided.
		float magnitude = 1.0f / sqrtf(a * a + b * b + c * c);
		a *= magnitude;
		b *= magnitude;
		c *= magnitude;
		d *= magnitude;
	}
	
	float Plane::dot(const Vec3& point)
	{
		// This function returns a * x + b * y + c * z + d * 1.
		// d also needs to be added.
		return (a * point.x + b * point.y + c * point.z + d);
	}
	
}
