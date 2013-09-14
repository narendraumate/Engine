//
//  Quaternion.cpp
//  Camaleao
//
//  Created by Narendra Umate on 3/8/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#include "Quaternion.h"

namespace Engine
{

	Quat::Quat(void)
	:   x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{ }

	Quat::Quat(const Mat4& mat4)
	{
		//TODO
	}

	Quat::Quat(const Vec4& vec4)
	:   x(vec4.x), y(vec4.y), z(vec4.z), w(vec4.w)
	{ }

	Quat::Quat(const float &s, const Vec3 &vec3)
	:   x(vec3.x), y(vec3.y), z(vec3.z), w(s)
	{ }

	Quat::Quat(const Vec3 &axis, const float &angle)
	{
		float angle_divide_2 = angle * 0.5f;
		Vec3 v = axis.normal() * sinf(angle_divide_2);
		x = v.x;
		y = v.y;
		z = v.z;
		w = /* s = */ cosf(angle_divide_2);
	}

	Quat::Quat(const Vec3 &v0, const Vec3 &v1)
	{
		// Reference
		// Game Programming Gems 1
		// 2.10 The Shortest Arc Quaternion Page 217 Author Stan Melax

		// r = v0normal x v1normal
		// s_multiply_2 = sqrt(2 * (1 + v0normal . v1normal))

		Vec3 v0normal = v0.normal();
		Vec3 v1normal = v1.normal();

		float s_multiply_2 = sqrtf(2.0f * (1.0f + dot(v0normal, v1normal)));

		Vec3 v = cross(v0normal, v1normal) / s_multiply_2;
		x = v.x;
		y = v.y;
		z = v.z;
		w = /* s = */ s_multiply_2 / 2.0f;
	}

	Quat::Quat(const float &x, const float &y, const float &z, const float &w)
	:   x(x), y(y), z(z), w(w)
	{ }

	Quat Quat::identity()
	{
		return Quat(0.0f, 0.0f, 0.0f, 1.0f);
	}

	Vec3 Quat::axis() const
	{
		return Vec3(x, y, z);
	}

	float Quat::angle() const
	{
		// w = cos(angle / 2)
		// angle = acos(w) * 2
		return acosf(w) * 2.0f;
	}

	Quat Quat::inverse() const
	{
		float invmagsqr = 1.0f / dot(*this, *this);
		return Quat(-x * invmagsqr, -y * invmagsqr, -z * invmagsqr, w * invmagsqr);
	}

	Quat Quat::conjugate() const
	{
		return Quat(-x, -y, -z, w);
	}

	float Quat::norm(void) const
	{
		return sqrtf(x * x + y * y + z * z + w * w);
	}

	Quat Quat::normal(void) const
	{
		float mag = norm();
		return Quat(x / mag, y / mag, z / mag, w / mag);
	}

	Quat Quat::normalize(void)
	{
		float mag = norm();
		x /= mag;
		y /= mag;
		z /= mag;
		w /= mag;
		return *this;
	}

	Mat3 Quat::mat3() const
	{
		return Mat3(1.0f-2.0f*(y*y + z*z), 2.0f*(x*y + w*z), 2.0f*(x*z - w*y),
					2.0f*(x*y - w*z), 1.0f-2.0f*(x*x + z*z), 2.0f*(y*z + w*x),
					2.0f*(x*z + w*y), 2.0f*(y*z - w*x), 1.0f-2.0f*(x*x + y*y));
	}

	Mat4 Quat::mat4() const
	{
		return Mat4(1.0f-2.0f*(y*y + z*z), 2.0f*(x*y + w*z), 2.0f*(x*z - w*y), 0.0f,
					2.0f*(x*y - w*z), 1.0f-2.0f*(x*x + z*z), 2.0f*(y*z + w*x), 0.0f,
					2.0f*(x*z + w*y), 2.0f*(y*z - w*x), 1.0f-2.0f*(x*x + y*y), 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
	}

	Quat Quat::operator+(const Quat &a) const
	{
		return Quat(x + a.x, y + a.y, z + a.z, w + a.w);
	}

	Quat Quat::operator-(const Quat &a) const
	{
		return Quat(x - a.x, y - a.y, z - a.z, w - a.w);
	}

	Quat Quat::operator*(const Quat &a) const
	{
		// P * Q = (p0 + p1i + p2j + p3k)(q0 + q1i + q2j + q3k)
		// P * Q = (p0q0 − p1q1 − p2q2 − p3q3) + . . . i + . . . j + . . . k
		// P * Q = (p0 + p)(q0 + q)
		// P * Q = (p0q0 + p0q + q0p + pq)	//	pq = p x q - p . q	//	cross - dot
		// P * Q = (p0q0 - p.q) + (p0q + q0p + p x q)

		return Quat(a.w * x + a.x * w - a.y * z + a.z * y,
					a.w * y + a.x * z + a.y * w - a.z * x,
					a.w * z - a.x * y + a.y * x + a.z * w,
					a.w * w - a.x * x - a.y * y - a.z * z);
	}

	Quat Quat::operator/(const Quat &a) const
	{
		float invmagsqr = 1.0f / dot(*this, *this);
		return Quat((a.w * x - a.x * w - a.y * z + a.z * y) * invmagsqr,
					(a.w * y + a.x * z - a.y * w - a.z * x) * invmagsqr,
					(a.w * z - a.x * y + a.y * x - a.z * w) * invmagsqr,
					(a.w * w + a.x * x + a.y * y + a.z * z) * invmagsqr);
	}

	void Quat::operator*=(const Quat &a)
	{
		*this = *this * a;
	}

	void Quat::operator/=(const Quat &a)
	{
		*this = *this / a;
	}

	float dot(const Quat &q0, const Quat &q1)
	{
		return (q0.x * q1.x + q0.y * q1.y + q0.z * q1.z + q0.w * q1.w);
	}

	Quat lerp(const Quat &q0, const Quat &q1, const float &t)
	{
		return Quat(lerp(q0.x, q1.x, t), lerp(q0.y, q1.y, t),
					lerp(q0.z, q1.z, t), lerp(q0.w, q1.w, t));
	}

	Quat slerp(const Quat &q0, const Quat & q1, const float &t)
	{
		return Quat::identity();	//TODO
	}
	
}
