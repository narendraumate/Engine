//
//  Color.cpp
//  Camaleao
//
//  Created by Narendra Umate on 10/5/12.
//  Copyright (c) 2012 Narendra Umate. All rights reserved.
//

#include "Color.h"

namespace Engine
{

	//  Color4f

	Color4f::Color4f(const Color &color)
#if defined __LITTLE_ENDIAN__	//  R8G8B8A8 Reverse
	:	r((float)((color >>  0) & 0x000000FF) / 255.0f)
	,	g((float)((color >>  8) & 0x000000FF) / 255.0f)
	,	b((float)((color >> 16) & 0x000000FF) / 255.0f)
	,	a((float)((color >> 24) & 0x000000FF) / 255.0f)
#elif defined __BIG_ENDIAN__	//  A8B8G8R8 Straight
	:	a((float)((color >>  0) & 0x000000FF) / 255.0f)
	,	b((float)((color >>  8) & 0x000000FF) / 255.0f)
	,	g((float)((color >> 16) & 0x000000FF) / 255.0f)
	,	r((float)((color >> 24) & 0x000000FF) / 255.0f)
#endif
	{ }

	Color4f::Color4f(const float &r, const float &g, const float &b, const float &a)
	:	r(r)
	,	g(g)
	,	b(b)
	,	a(a)
	{ }

	Color4f::Color4f(const Vec3 &v, const float &a)
	:	r(v.x)
	,	g(v.y)
	,	b(v.z)
	,	a(  a)
	{ }

	Color4f::Color4f(const Vec4 &v)
	:	r(v.x)
	,	g(v.y)
	,	b(v.z)
	,	a(v.w)
	{ }

	Color4f& Color4f::operator=(const Color4f &u)
	{
		if (this != &u)
		{
			r = u.r;
			g = u.g;
			b = u.b;
			a = u.a;
		}
		return *this;
	}

	Color4f Color4f::operator+(const Color4f &u) const
	{
		return Color4f(r + u.r,
					   g + u.g,
					   b + u.b,
					   a + u.a);
	}

	Color4f Color4f::operator-(const Color4f &u) const
	{
		return Color4f(r - u.r,
					   g - u.g,
					   b - u.b,
					   a - u.a);
	}

	Color4f Color4f::operator*(const Color4f &u) const
	{
		return Color4f(r * u.r,
					   g * u.g,
					   b * u.b,
					   a * u.a);
	}

	Color4f Color4f::operator/(const Color4f &u) const
	{
		return Color4f(r / u.r,
					   g / u.g,
					   b / u.b,
					   a / u.a);
	}

	Color4f Color4f::operator*(const float &u) const
	{
		return Color4f(r * u,
					   g * u,
					   b * u,
					   a * u);
	}

	Color4f Color4f::operator/(const float &u) const
	{
		return Color4f(r / u,
					   g / u,
					   b / u,
					   a / u);
	}

	Color4f Color4f::operator+()const
	{
		return *this;
	}

	Color4f Color4f::operator-()const
	{
		return Color4f(-r, -g, -b, -a);
	}

	Color4f& Color4f::operator+=(const Color4f &u)
	{
		*this = *this + u;
		return *this;
	}

	Color4f& Color4f::operator-=(const Color4f &u)
	{
		*this = *this - u;
		return *this;
	}

	Color4f& Color4f::operator/=(const Color4f &u)
	{
		*this = *this / u;
		return *this;
	}

	Color4f& Color4f::operator*=(const Color4f &u)
	{
		*this = *this * u;
		return *this;
	}

	Color4f& Color4f::operator/=(const float u)
	{
		*this = *this / u;
		return *this;
	}

	Color4f& Color4f::operator*=(const float u)
	{
		*this = *this * u;
		return *this;
	}

	bool Color4f::operator==(const Color4f &u) const
	{
		return (r == u.r && g == u.g && b == u.b && a == u.a);
	}

	bool Color4f::operator!=(const Color4f &u) const
	{
		return (r != u.r || g != u.g || b != u.b || a != u.a);
	}

	Color4f Color4f::clamp()
	{
		return Color4f(r > 1.0f ? 1.0f : r < 0.0f ? 0.0f : r,
					   g > 1.0f ? 1.0f : g < 0.0f ? 0.0f : g,
					   b > 1.0f ? 1.0f : b < 0.0f ? 0.0f : b,
					   a > 1.0f ? 1.0f : a < 0.0f ? 0.0f : a);
	}

	Vec3 Color4f::vec3() const
	{
		return Vec3(r, g, b);
	}

	Vec4 Color4f::vec4() const
	{
		return Vec4(r, g, b, a);
	}

	Color Color4f::color() const
	{
		return (Color)RGBA((uint8_t)(r * 255.0f),
						   (uint8_t)(g * 255.0f),
						   (uint8_t)(b * 255.0f),
						   (uint8_t)(a * 255.0f));
	}

	ostream& operator<<(ostream& out, const Color4f &u)
	{
		out << u.r << ' ' << u.g << ' ' << u.b << ' ' << u.a << ' ';
		return out;
	}

	//	Functions

	Color color(const Vec3 &v, const float &a)
	{
		return (Color)RGBA((uint8_t)(v.x * 255.0f),
						   (uint8_t)(v.y * 255.0f),
						   (uint8_t)(v.z * 255.0f),
						   (uint8_t)(  a * 255.0f));
	}

	Color color(const Vec4 &v)
	{
		return (Color)RGBA((uint8_t)(v.x * 255.0f),
						   (uint8_t)(v.y * 255.0f),
						   (uint8_t)(v.z * 255.0f),
						   (uint8_t)(v.w * 255.0f));
	}
	
	Color4f lerp(const Color4f &u, const Color4f &v, const float &t)
	{
		return (u - v) * t + v;
	}
	
}
