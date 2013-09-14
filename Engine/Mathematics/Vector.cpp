//
//  Vector.cpp
//  Camaleao
//
//  Created by Narendra Umate on 10/4/12.
//  Copyright (c) 2012 Narendra Umate. All rights reserved.
//

#include "Vector.h"

namespace Engine
{

	//  Vec1

	Vec1::Vec1(void)
	:	x(0.0f)
	{ }

	Vec1::Vec1(const float &x)
	:	x(x)
	{ }

	void Vec1::set(const float &x)
	{
		this->x = x;
	}

	void Vec1::zero(void)
	{
		x = 0.0f;
	}

	Vec1 Vec1::abs(void) const
	{
		return maxVec(*this, -*this);
	}

	float Vec1::sqr(void) const
	{
		return dot(*this, *this);
	}

	float Vec1::norm(void) const
	{
		return fabs(x);//return x > 0.0f ? x : -x;//return sqrtf(dot(*this, *this));
	}

	Vec1 Vec1::normal(void) const
	{
		float magnitude = norm();
		return (magnitude > 1.0f) ? (*this / magnitude) : (*this);
	}

	void Vec1::normalize(void)
	{
		float magnitude = norm();
		if (magnitude > 1.0f)
		{
			*this /= norm();
		}
	}

	float Vec1::operator[](const int index) const
	{
		return (&x)[index];
	}

	float& Vec1::operator[](const int index)
	{
		return (&x)[index];
	}

	Vec1 Vec1::operator-() const
	{
		return Vec1(-x);
	}

	float Vec1::operator*(const Vec1 &a) const
	{
		return x * a.x;
	}

	Vec1 Vec1::operator*(const float &a) const
	{
		return Vec1(x * a);
	}

	Vec1 Vec1::operator/(const float &a) const
	{
		return Vec1(x / a);
	}

	Vec1 Vec1::operator+(const Vec1 &a) const
	{
		return Vec1(x + a.x);
	}

	Vec1 Vec1::operator-(const Vec1 &a) const
	{
		return Vec1(x - a.x);
	}

	void Vec1::operator+=(const Vec1 &a)
	{
		x += a.x;
	}

	void Vec1::operator-=(const Vec1 &a)
	{
		x -= a.x;
	}

	void Vec1::operator/=(const Vec1 &a)
	{
		x /= a.x;
	}

	void Vec1::operator/=(const float &a)
	{
		x /= a;
	}

	void Vec1::operator*=(const float &a)
	{
		x *= a;
	}

	bool Vec1::operator==(const Vec1 &a) const
	{
		return (x == a.x);
	}

	bool Vec1::operator!=(const Vec1 &a) const
	{
		return (x != a.x);
	}

	Vec1 Vec1::operator*(const Mat4 &m) const
	{
		return Vec1(x * m.d00 + m.d30);
	}

	Vec1 Vec1::operator*(const Quat &q) const
	{
		return Vec1();	//TODO
	}

	//  Vec2

	Vec2::Vec2(void)
	:	x(0.0f),
		y(0.0f)
	{ }

	Vec2::Vec2(const float &x, const float &y)
	:	x(x),
		y(y)
	{ }

	void Vec2::set(const float &x, const float &y)
	{
		this->x = x;
		this->y = y;
	}

	void Vec2::zero(void)
	{
		x = y = 0.0f;
	}

	Vec2 Vec2::abs(void) const
	{
		return maxVec(*this, -*this);
	}

	float Vec2::sqr(void) const
	{
		return dot(*this, *this);
	}

	float Vec2::norm(void) const
	{
		return sqrtf(dot(*this, *this));
	}

	Vec2 Vec2::normal(void) const
	{
		float magnitude = norm();
		return (magnitude > 1.0f) ? (*this / magnitude) : (*this);
	}

	void Vec2::normalize(void)
	{
		float magnitude = norm();
		if (magnitude > 1.0f)
		{
			*this /= norm();
		}
	}

	float Vec2::operator[](const int index) const
	{
		return (&x)[index];
	}

	float& Vec2::operator[](const int index)
	{
		return (&x)[index];
	}

	Vec2 Vec2::operator-() const
	{
		return Vec2(-x, -y);
	}

	float Vec2::operator*(const Vec2 &a) const
	{
		return x * a.x + y * a.y;
	}

	Vec2 Vec2::operator*(const float &a) const
	{
		return Vec2(x * a, y * a);
	}

	Vec2 Vec2::operator/(const float &a) const
	{
		return Vec2(x / a, y / a);
	}

	Vec2 Vec2::operator+(const Vec2 &a) const
	{
		return Vec2(x + a.x, y + a.y);
	}

	Vec2 Vec2::operator-(const Vec2 &a) const
	{
		return Vec2(x - a.x, y - a.y);
	}

	void Vec2::operator+=(const Vec2 &a)
	{
		x += a.x;
		y += a.y;
	}

	void Vec2::operator-=(const Vec2 &a)
	{
		x -= a.x;
		y -= a.y;
	}

	void Vec2::operator/=(const Vec2 &a)
	{
		x /= a.x;
		y /= a.y;
	}

	void Vec2::operator/=(const float &a)
	{
		x /= a;
		y /= a;
	}

	void Vec2::operator*=(const float &a)
	{
		x *= a;
		y *= a;
	}

	bool Vec2::operator==(const Vec2 &a) const
	{
		return (x == a.x && y == a.y);
	}

	bool Vec2::operator!=(const Vec2 &a) const
	{
		return (x != a.x || y != a.y);
	}

	Vec2 Vec2::operator*(const Mat4 &m) const
	{
		return Vec2(x * m.d00 + y * m.d10 + m.d30,
					x * m.d01 + y * m.d11 + m.d31);
	}

	Vec2 Vec2::operator*(const Quat &q) const
	{
		return Vec2();	//TODO
	}

	//  Vec3

	Vec3::Vec3(void)
	:	x(0.0f),
		y(0.0f),
		z(0.0f)
	{ }

	Vec3::Vec3(const float &x, const float &y, const float &z)
	:	x(x),
		y(y),
		z(z)
	{ }

	void Vec3::set(const float &x, const float &y, const float &z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void Vec3::zero(void)
	{
		x = y = z = 0.0f;
	}

	Vec3 Vec3::abs(void) const
	{
		return maxVec(*this, -*this);
	}

	float Vec3::sqr(void) const
	{
		return dot(*this, *this);
	}

	float Vec3::norm(void) const
	{
		return sqrtf(dot(*this, *this));
	}

	Vec3 Vec3::normal(void) const
	{
		float magnitude = norm();
		return (magnitude > 1.0f) ? (*this / magnitude) : (*this);
	}

	void Vec3::normalize(void)
	{
		float magnitude = norm();
		if (magnitude > 1.0f)
		{
			*this /= norm();
		}
	}

	float Vec3::operator[](const int index) const
	{
		return (&x)[index];
	}

	float& Vec3::operator[](const int index)
	{
		return (&x)[index];
	}

	Vec3 Vec3::operator-() const
	{
		return Vec3(-x, -y, -z);
	}

	float Vec3::operator*(const Vec3 &a) const
	{
		return x * a.x + y * a.y + z * a.z;
	}

	Vec3 Vec3::operator*(const float &a) const
	{
		return Vec3(x * a, y * a, z * a);
	}

	Vec3 Vec3::operator/(const float &a) const
	{
		return Vec3(x / a, y / a, z / a);
	}

	Vec3 Vec3::operator+(const Vec3 &a) const
	{
		return Vec3(x + a.x, y + a.y, z + a.z);
	}

	Vec3 Vec3::operator-(const Vec3 &a) const
	{
		return Vec3(x - a.x, y - a.y, z - a.z);
	}

	void Vec3::operator+=(const Vec3 &a)
	{
		x += a.x;
		y += a.y;
		z += a.z;
	}

	void Vec3::operator-=(const Vec3 &a)
	{
		x -= a.x;
		y -= a.y;
		z -= a.z;
	}

	void Vec3::operator/=(const Vec3 &a)
	{
		x /= a.x;
		y /= a.y;
		z /= a.z;
	}

	void Vec3::operator/=(const float &a)
	{
		x /= a;
		y /= a;
		z /= a;
	}

	void Vec3::operator*=(const float &a)
	{
		x *= a;
		y *= a;
		z *= a;
	}

	bool Vec3::operator==(const Vec3 &a) const
	{
		return (x == a.x && y == a.y && z == a.z);
	}

	bool Vec3::operator!=(const Vec3 &a) const
	{
		return (x != a.x || y != a.y || z != a.z);
	}

	Vec3 Vec3::operator*(const Mat4 &m) const
	{
		return Vec3(x * m.d00 + y * m.d10 + z * m.d20 + m.d30,
					x * m.d01 + y * m.d11 + z * m.d21 + m.d31,
					x * m.d02 + y * m.d12 + z * m.d22 + m.d32);
	}

	Vec3 Vec3::operator*(const Quat &q) const
	{
		return Vec3();	//TODO
	}

	//  Vec4

	Vec4::Vec4(void)
	:	x(0.0f),
		y(0.0f),
		z(0.0f),
		w(0.0f)
	{ }

	Vec4::Vec4(const float &x, const float &y, const float &z, const float &w)
	:	x(x),
		y(y),
		z(z),
		w(w)
	{ }

	void Vec4::set(const float &x, const float &y, const float &z, const float &w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	void Vec4::zero(void)
	{
		x = y = z = w = 0.0f;
	}

	Vec4 Vec4::abs(void) const
	{
		return maxVec(*this, -*this);
	}

	float Vec4::sqr(void) const
	{
		return dot(*this, *this);
	}

	float Vec4::norm(void) const
	{
		return sqrtf(dot(*this, *this));
	}

	Vec4 Vec4::normal(void) const
	{
		float magnitude = norm();
		return (magnitude > 1.0f) ? (*this / magnitude) : (*this);
	}

	void Vec4::normalize(void)
	{
		float magnitude = norm();
		if (magnitude > 1.0f)
		{
			*this /= norm();
		}
	}

	Vec3 Vec4::project(void)
	{
		return Vec3(x, y, z);
	}

	float Vec4::operator[](const int index) const
	{
		return (&x)[index];
	}

	float& Vec4::operator[](const int index)
	{
		return (&x)[index];
	}

	Vec4 Vec4::operator-() const
	{
		return Vec4(-x, -y, -z, -w);
	}

	float Vec4::operator*(const Vec4 &a) const
	{
		return x * a.x + y * a.y + z * a.z + w * a.w;
	}

	Vec4 Vec4::operator*(const float &a) const
	{
		return Vec4(x * a, y * a, z * a, w * a);
	}

	Vec4 Vec4::operator/(const float &a) const
	{
		return Vec4(x / a, y / a, z / a, w / a);
	}

	Vec4 Vec4::operator+(const Vec4 &a) const
	{
		return Vec4(x + a.x, y + a.y, z + a.z, w + a.w);
	}

	Vec4 Vec4::operator-(const Vec4 &a) const
	{
		return Vec4(x - a.x, y - a.y, z - a.z, w - a.w);
	}

	void Vec4::operator+=(const Vec4 &a)
	{
		x += a.x;
		y += a.y;
		z += a.z;
		w += a.w;
	}

	void Vec4::operator-=(const Vec4 &a)
	{
		x -= a.x;
		y -= a.y;
		z -= a.z;
		w -= a.w;
	}

	void Vec4::operator/=(const Vec4 &a)
	{
		x /= a.x;
		y /= a.y;
		z /= a.z;
		w /= a.w;
	}

	void Vec4::operator/=(const float &a)
	{
		x /= a;
		y /= a;
		z /= a;
		w /= a;
	}

	void Vec4::operator*=(const float &a)
	{
		x *= a;
		y *= a;
		z *= a;
		w *= a;
	}

	bool Vec4::operator==(const Vec4 &a) const
	{
		return (x == a.x && y == a.y && z == a.z && w == a.w);
	}

	bool Vec4::operator!=(const Vec4 &a) const
	{
		return (x != a.x || y != a.y || z != a.z || w != a.w);
	}

	Vec4 Vec4::operator*(const Mat4 &m) const
	{
		return Vec4(x * m.d00 + y * m.d10 + z * m.d20 + w * m.d30,
					x * m.d01 + y * m.d11 + z * m.d21 + w * m.d31,
					x * m.d02 + y * m.d12 + z * m.d22 + w * m.d32,
					x * m.d03 + y * m.d13 + z * m.d23 + w * m.d33);
	}

	Vec4 Vec4::operator*(const Quat &q) const
	{
		return Vec4();	//TODO
	}

	//  Functions

	Vec4 freeVector(const Vec3 &v)
	{
		return Vec4(v.x, v.y, v.z, 1.0f);
	}

	Vec4 pointVector(const Vec3 &v)
	{
		return Vec4(v.x, v.y, v.z, 0.0f);
	}

	Vec1 minVec(const Vec1 &u, const Vec1 &v)
	{
		return Vec1(minVec(u.x, v.x));
	}

	Vec2 minVec(const Vec2 &u, const Vec2 &v)
	{
		return Vec2(minVec(u.x, v.x), minVec(u.y, v.y));
	}

	Vec3 minVec(const Vec3 &u, const Vec3 &v)
	{
		return Vec3(minVec(u.x, v.x), minVec(u.y, v.y), minVec(u.z, v.z));
	}

	Vec4 minVec(const Vec4 &u, const Vec4 &v)
	{
		return Vec4(minVec(u.x, v.x), minVec(u.y, v.y), minVec(u.z, v.z), minVec(u.w, v.w));
	}

	Vec1 maxVec(const Vec1 &u, const Vec1 &v)
	{
		return Vec1(maxVec(u.x, v.x));
	}

	Vec2 maxVec(const Vec2 &u, const Vec2 &v)
	{
		return Vec2(maxVec(u.x, v.x), maxVec(u.y, v.y));
	}

	Vec3 maxVec(const Vec3 &u, const Vec3 &v)
	{
		return Vec3(maxVec(u.x, v.x), maxVec(u.y, v.y), maxVec(u.z, v.z));
	}

	Vec4 maxVec(const Vec4 &u, const Vec4 &v)
	{
		return Vec4(maxVec(u.x, v.x), maxVec(u.y, v.y), maxVec(u.z, v.z), maxVec(u.w, v.w));
	}

	float dot(const Vec1 &u, const Vec1 &v)
	{
		return u.x * v.x;
	}

	float dot(const Vec2 &u, const Vec2 &v)
	{
		return u.x * v.x + u.y * v.y;
	}

	float dot(const Vec3 &u, const Vec3 &v)
	{
		return u.x * v.x + u.y * v.y + u.z * v.z;
	}

	float dot(const Vec4 &u, const Vec4 &v)
	{
		return u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w;
	}

	Vec3 cross(const Vec3 &u, const Vec3 &v)
	{
		return Vec3(u.y * v.z - v.y * u.z,
					v.x * u.z - u.x * v.z,
					u.x * v.y - v.x * u.y);
	}

	Vec4 cross(const Vec4 &u, const Vec4 &v, const Vec4 &w)
	{
		// Calculate intermediate values.
		float a = (v[0] * w[1]) - (v[1] * w[0]);
		float b = (v[0] * w[2]) - (v[2] * w[0]);
		float c = (v[0] * w[3]) - (v[3] * w[0]);
		float d = (v[1] * w[2]) - (v[2] * w[1]);
		float e = (v[1] * w[3]) - (v[3] * w[1]);
		float f = (v[2] * w[3]) - (v[3] * w[2]);

		// Calculate the result-vector components.
		return Vec4(  (u.y * f) - (u.z * e) + (u.w * d),
					- (u.x * f) + (u.z * c) - (u.w * b),
					(u.x * e) - (u.y * c) + (u.w * a),
					- (u.x * d) + (u.y * b) - (u.z * a) );
	}

	float dist(const Vec1 &u, const Vec1 &v)
	{
		return fabsf(u.x - v.x);
	}

	float dist(const Vec2 &u, const Vec2 &v)
	{
		return sqrtf((u.x - v.x) * (u.x - v.x) + (u.y - v.y) * (u.y - v.y));
	}

	float dist(const Vec3 &u, const Vec3 &v)
	{
		return sqrtf((u.x - v.x) * (u.x - v.x) +
					 (u.y - v.y) * (u.y - v.y) +
					 (u.z - v.z) * (u.z - v.z));
	}

	float dist(const Vec4 &u, const Vec4 &v)
	{
		return sqrtf((u.x - v.x) * (u.x - v.x) +
					 (u.y - v.y) * (u.y - v.y) +
					 (u.z - v.z) * (u.z - v.z) +
					 (u.w - v.w) * (u.w - v.w));
	}

	float distsqr(const Vec1 &u, const Vec1 &v)
	{
		return (u.x - v.x) * (u.x - v.x);
	}

	float distsqr(const Vec2 u, const Vec2 &v)
	{
		return (u.x - v.x) * (u.x - v.x) + (u.y - v.y) * (u.y - v.y);
	}

	float distsqr(const Vec3 &u, const Vec3 &v)
	{
		return ((u.x - v.x) * (u.x - v.x) +
				(u.y - v.y) * (u.y - v.y) +
				(u.z - v.z) * (u.z - v.z));
	}

	float distsqr(const Vec4 &u, const Vec4 &v)
	{
		return ((u.x - v.x) * (u.x - v.x) +
				(u.y - v.y) * (u.y - v.y) +
				(u.z - v.z) * (u.z - v.z) +
				(u.w - v.w) * (u.w - v.w));
	}

	Vec1 lerp(const Vec1 &a, const Vec1 &b, const float &t)
	{
		return (a - b) * t + b;
	}

	Vec2 lerp(const Vec2 &a, const Vec2 &b, const float &t)
	{
		return (a - b) * t + b;
	}

	Vec3 lerp(const Vec3 &a, const Vec3 &b, const float &t)
	{
		return (a - b) * t + b;
	}

	Vec4 lerp(const Vec4 &a, const Vec4 &b, const float &t)
	{
		return (a - b) * t + b;
	}

	Vec1 reflect(const Vec1 &incident, const Vec1 &normal)
	{
		return incident - normal * 2.0f * dot(incident, normal);
	}

	Vec2 reflect(const Vec2 &incident, const Vec2 &normal)
	{
		return incident - normal * 2.0f * dot(incident, normal);
	}

	Vec3 reflect(const Vec3 &incident, const Vec3 &normal)
	{
		return incident - normal * 2.0f * dot(incident, normal);
	}

	Vec4 reflect(const Vec4 &incident, const Vec4 &normal)
	{
		return incident - normal * 2.0f * dot(incident, normal);
	}

	Vec3  vectorTripleProduct(const Vec3 &u, const Vec3 &v, const Vec3 &w)
	{
		//a x (b x c) = (a . c) b - (a . b) c
		return cross(u, cross(v, w));
	}

	float scalarTripleProduct(const Vec3 &u, const Vec3 &v, const Vec3 &w)
	{
		//a . (b x c) = b . (c x a) = c . (a x b)
		return dot(u, cross(v, w));
	}

	Vec1 barycentric(const Vec1& value1, const Vec1& value2, const Vec1& value3,
					 const float& amount1, const float& amount2)
	{
		return Vec1(barycentric(value1.x, value2.x, value3.x, amount1, amount2));
	}

	Vec2 barycentric(const Vec2& value1, const Vec2& value2, const Vec2& value3,
					 const float& amount1, const float& amount2)
	{
		return Vec2(barycentric(value1.x, value2.x, value3.x, amount1, amount2),
					barycentric(value1.y, value2.y, value3.y, amount1, amount2));
	}

	Vec3 barycentric(const Vec3& value1, const Vec3& value2, const Vec3& value3,
					 const float& amount1, const float& amount2)
	{
		return Vec3(barycentric(value1.x, value2.x, value3.x, amount1, amount2),
					barycentric(value1.y, value2.y, value3.y, amount1, amount2),
					barycentric(value1.z, value2.z, value3.z, amount1, amount2));
	}

	Vec4 barycentric(const Vec4& value1, const Vec4& value2, const Vec4& value3,
					 const float& amount1, const float& amount2)
	{
		return Vec4(barycentric(value1.x, value2.x, value3.x, amount1, amount2),
					barycentric(value1.y, value2.y, value3.y, amount1, amount2),
					barycentric(value1.z, value2.z, value3.z, amount1, amount2),
					barycentric(value1.w, value2.w, value3.w, amount1, amount2));
	}

	Vec1 catmullRom(const Vec1& value1, const Vec1& value2, const Vec1& value3,
					const Vec1& value4, const float& amount)
	{
		return Vec1(catmullRom(value1.x, value2.x, value3.x, value4.x, amount));
	}

	Vec2 catmullRom(const Vec2& value1, const Vec2& value2, const Vec2& value3,
					const Vec2& value4, const float& amount)
	{
		return Vec2(catmullRom(value1.x, value2.x, value3.x, value4.x, amount),
					catmullRom(value1.y, value2.y, value3.y, value4.y, amount));
	}

	Vec3 catmullRom(const Vec3& value1, const Vec3& value2, const Vec3& value3,
					const Vec3& value4, const float& amount)
	{
		return Vec3(catmullRom(value1.x, value2.x, value3.x, value4.x, amount),
					catmullRom(value1.y, value2.y, value3.y, value4.y, amount),
					catmullRom(value1.z, value2.z, value3.z, value4.z, amount));
	}

	Vec4 catmullRom(const Vec4& value1, const Vec4& value2, const Vec4& value3,
					const Vec4& value4, const float& amount)
	{
		return Vec4(catmullRom(value1.x, value2.x, value3.x, value4.x, amount),
					catmullRom(value1.y, value2.y, value3.y, value4.y, amount),
					catmullRom(value1.z, value2.z, value3.z, value4.z, amount),
					catmullRom(value1.w, value2.w, value3.w, value4.w, amount));
	}

	Vec1 hermite(const Vec1& value1, const Vec1& tangent1, const Vec1& value2,
				 const Vec1& tangent2, const float& amount)
	{
		return Vec1(hermite(value1.x, tangent1.x, value2.x, tangent2.x, amount));
	}

	Vec2 hermite(const Vec2& value1, const Vec2& tangent1, const Vec2& value2,
				 const Vec2& tangent2, const float& amount)
	{
		return Vec2(hermite(value1.x, tangent1.x, value2.x, tangent2.x, amount),
					hermite(value1.y, tangent1.y, value2.y, tangent2.y, amount));
	}

	Vec3 hermite(const Vec3& value1, const Vec3& tangent1, const Vec3& value2,
				 const Vec3& tangent2, const float& amount)
	{
		return Vec3(hermite(value1.x, tangent1.x, value2.x, tangent2.x, amount),
					hermite(value1.y, tangent1.y, value2.y, tangent2.y, amount),
					hermite(value1.z, tangent1.z, value2.z, tangent2.z, amount));
	}

	Vec4 hermite(const Vec4& value1, const Vec4& tangent1, const Vec4& value2,
				 const Vec4& tangent2, const float& amount)
	{
		return Vec4(hermite(value1.x, tangent1.x, value2.x, tangent2.x, amount),
					hermite(value1.y, tangent1.y, value2.y, tangent2.y, amount),
					hermite(value1.z, tangent1.z, value2.z, tangent2.z, amount),
					hermite(value1.w, tangent1.w, value2.w, tangent2.w, amount));
	}
	
	Vec1 smoothStep(const Vec1& value1, const Vec1& value2, const float& amount)
	{
		return Vec1(smoothStep(value1.x, value2.x, amount));
	}
	
	Vec2 smoothStep(const Vec2& value1, const Vec2& value2, const float& amount)
	{
		return Vec2(smoothStep(value1.x, value2.x, amount),
					smoothStep(value1.y, value2.y, amount));
	}
	
	Vec3 smoothStep(const Vec3& value1, const Vec3& value2, const float& amount)
	{
		return Vec3(smoothStep(value1.x, value2.x, amount),
					smoothStep(value1.y, value2.y, amount),
					smoothStep(value1.z, value2.z, amount));
	}
	
	Vec4 smoothStep(const Vec4& value1, const Vec4& value2, const float& amount)
	{
		return Vec4(smoothStep(value1.x, value2.x, amount),
					smoothStep(value1.y, value2.y, amount),
					smoothStep(value1.z, value2.z, amount),
					smoothStep(value1.w, value2.w, amount));
	}
	
}
