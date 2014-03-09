
// ===============================================================================================================
// -*- C++ -*-
//
// Vector.hpp - 2D / 3D Vector math.
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

#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <math.h>

// ===============
// 2D Vector Class
// ===============

class Vec2 {

public:

	union {
		struct {
			float x; // X-Axis
			float y; // Y-Axis
		};
		float v[2];
	};

public:

	// Constructors:

	Vec2(void);
	Vec2(float X, float Y);
	Vec2(const Vec2 & r);

	// Operators:

	Vec2 & operator = (float Val);
	Vec2 & operator = (const Vec2 & r);

	bool operator == (const Vec2 & r) const;
	bool operator != (const Vec2 & r) const;

public:

	// Public Interface:

	// Linear interpolation between this vector and 'vec'.
	Vec2 Lerp(const Vec2 & vec, float t) const;

	// Dot product between this vector and 'r'.
	float DotProduct(const Vec2 & r) const;

	// The absolute length of this vector.
	float Length(void) const;

	// Normalize this vector. (Divide it by it's length).
	void Normalize(void);

	// Scale the vector by a given factor. (vector = vector * factor)
	void Scale(float factor);

	// Negate the vector. (vector = -vector)
	void Negate(void);
};

// ===============
// 3D Vector Class
// ===============

class Vec3 {

public:

	union {
		struct {
			float x; // X-Axis
			float y; // Y-Axis
			float z; // Z-Axis
		};
		float v[3];
	};

public:

	// Constructors:

	Vec3(void);
	Vec3(float X, float Y, float Z);
	Vec3(const Vec3 & r);

	// Operators:

	Vec3 & operator = (float Val);
	Vec3 & operator = (const Vec3 & r);

	bool operator == (const Vec3 & r) const;
	bool operator != (const Vec3 & r) const;

public:

	// Public Interface:

	// Dot product between this vector and 'r'.
	float DotProduct(const Vec3 & r) const;

	// The absolute length of this vector.
	float Length(void) const;

	// Computes the cross product of this vector and 'vec' and return the result as a new vector.
	Vec3 CrossProduct(const Vec3 & vec) const;

	// Linear interpolation between this vector and 'vec'.
	Vec3 Lerp(const Vec3 & vec, float t) const;

	// Normalize this vector. (Divide it by it's length).
	void Normalize(void);

	// Scale the vector by a given factor. (vector = vector * factor)
	void Scale(float factor);

	// Negate the vector. (vector = -vector)
	void Negate(void);
};

#endif // __VECTOR_HPP__