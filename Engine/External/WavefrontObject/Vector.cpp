
// ===============================================================================================================
// -*- C++ -*-
//
// Vector.cpp - 2D / 3D Vector math.
//
// Copyright (c) 2010 Guilherme R. Lampert
// guilherme.ronaldo.lampert@gmail.com
//
// This code is licenced under the MIT license.
//
// This software is provided "as is" without express or implied
// warranties. You may freely copy and compile this source into
// applications you distribute provided that the copyright text
// above is included in the resulting source code.
//
// ===============================================================================================================

#include "Vector.hpp"

// == Vec2 Class Implementation ==

Vec2::Vec2(void) : x(0), y(0)
{
	// Defaul constructor creates a vector at origin (0,0)
}

Vec2::Vec2(float X, float Y) : x(X), y(Y)
{
}

Vec2::Vec2(const Vec2 & r) : x(r.x), y(r.y)
{
}

Vec2 & Vec2::operator = (float Val)
{
	x = Val;
	y = Val;
	return (*this);
}

Vec2 & Vec2::operator = (const Vec2 & r)
{
	x = r.x;
	y = r.y;
	return (*this);
}

bool Vec2::operator == (const Vec2 & r) const
{
	return ((x == r.x) && (y == r.y));
}

bool Vec2::operator != (const Vec2 & r) const
{
	return ((x != r.x) && (y != r.y));
}

Vec2 Vec2::Lerp(const Vec2 & vec, float t) const
{
	return (Vec2((x + t * (vec.x - x)), (y + t * (vec.y - y))));
}

float Vec2::DotProduct(const Vec2 & r) const
{
	return ((x * r.x) + (y * r.y));
}

float Vec2::Length(void) const
{
	return (sqrtf((x * x) + (y * y)));
}

void Vec2::Normalize(void)
{
	const float invLen = 1.0f/sqrtf((x * x) + (y * y));
	x *= invLen;
	y *= invLen;
}

void Vec2::Scale(float factor)
{
	x *= factor;
	y *= factor;
}

void Vec2::Negate(void)
{
	x = -x;
	y = -y;
}

// == Vec3 Class Implementation ==

Vec3::Vec3(void) : x(0), y(0), z(0)
{
	// Defaul constructor creates a vector at origin (0,0,0)
}

Vec3::Vec3(float X, float Y, float Z) : x(X), y(Y), z(Z)
{
}

Vec3::Vec3(const Vec3 & r) : x(r.x), y(r.y), z(r.z)
{
}

Vec3 & Vec3::operator = (float Val)
{
	x = Val;
	y = Val;
	z = Val;
	return (*this);
}

Vec3 & Vec3::operator = (const Vec3 & r)
{
	x = r.x;
	y = r.y;
	z = r.z;
	return (*this);
}

bool Vec3::operator == (const Vec3 & r) const
{
	return ((x == r.x) && (y == r.y) && (z == r.z));
}

bool Vec3::operator != (const Vec3 & r) const
{
	return ((x != r.x) && (y != r.y) && (z != r.z));
}

float Vec3::DotProduct(const Vec3 & r) const
{
	return ((x * r.x) + (y * r.y) + (z * r.z));
}

float Vec3::Length(void) const
{
	return (sqrtf((x * x) + (y * y) + (z * z)));
}

Vec3 Vec3::CrossProduct(const Vec3 & vec) const
{
	return (Vec3(((y * vec.z) - (z * vec.y)),
				 ((z * vec.x) - (x * vec.z)),
				 ((x * vec.y) - (y * vec.x))));
}

Vec3 Vec3::Lerp(const Vec3 & vec, float t) const
{
	return (Vec3((x + t * (vec.x - x)),
				 (y + t * (vec.y - y)),
				 (z + t * (vec.z - z))));
}

void Vec3::Normalize(void)
{
	const float invLen = 1.0f/sqrtf((x * x) + (y * y) + (z * z));
	x *= invLen;
	y *= invLen;
	z *= invLen;
}

void Vec3::Scale(float factor)
{
	x *= factor;
	y *= factor;
	z *= factor;
}

void Vec3::Negate(void)
{
	x = -x;
	y = -y;
	z = -z;
}
