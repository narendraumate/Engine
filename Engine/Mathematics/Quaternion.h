//
//  Quaternion.h
//  Camaleao
//
//  Created by Narendra Umate on 3/8/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#ifndef __Camaleao__Quaternion__
#define __Camaleao__Quaternion__

#include "Math.h"
#include "Matrix.h"
#include "Vector.h"

namespace Engine
{

	class Mat3;
	class Mat4;
	class Vec3;
	class Vec4;

	class Quat
	{

	public:
		// s + v
		// w + xi + yj + zk
		// s = w = cos(theta / 2)
		// v = (x, y, z) = sin(theta / 2) * rotation axis vector

		float x, y, z, w;	// x, y, z, w instead of w, x, y, z for Vec4 match

		Quat(void);
		Quat(const Mat4& mat4);
		Quat(const Vec4& vec4);
		Quat(const float &s, const Vec3 &vec3);
		Quat(const Vec3 &axis, const float &angle);
		Quat(const Vec3 &v0, const Vec3 &v1);     // q that rotates v0 to v1
		Quat(const float &x, const float &y, const float &z, const float &w);

		static	Quat identity();

		Vec3	axis() const;
		float   angle() const;
		Quat	inverse() const;
		Quat	conjugate() const;
		float	norm(void) const;
		Quat	normal(void) const;
		Quat	normalize(void);
		Mat3	mat3() const;
		Mat4	mat4() const;

		Quat	operator+(const Quat &a) const;
		Quat	operator-(const Quat &a) const;
		Quat	operator*(const Quat &a) const; // q0 * q1 != q1 * q0 noncommutative
		Quat	operator/(const Quat &a) const; // q0 / q1 is possible
		void    operator*=(const Quat &a);
		void    operator/=(const Quat &a);
	};

	float	dot(const Quat &q0, const Quat &q1);
	Quat	lerp(const Quat &q0, const Quat &q1, const float &t);
	Quat	slerp(const Quat &q0, const Quat & q1, const float &t);

}

#endif /* defined(__Camaleao__Quaternion__) */
