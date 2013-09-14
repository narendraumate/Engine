//
//  Math.cpp
//  Engine.Framework
//
//  Created by Narendra Umate on 4/13/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#include "Math.h"

namespace Engine
{

	// Is power of two
	// http://graphics.stanford.edu/~seander/bithacks.html
	// Determining if an integer is a power of 2 branch less
	bool isp2(const int& value)
	{
		return (value && !(value & (value - 1)));
	}

	// Greatest power of 2 less than or equal to value
	// Hacker's Delight Henry S. Warren
	// Rounding Up/Down to the Next Power of 2 branch less
	int flp2(const int& value)
	{
		int v = value;
		v--;
		v |= v >> 1;
		v |= v >> 2;
		v |= v >> 4;
		v |= v >> 8;
		v |= v >> 16;
		return v - (v >> 1);
	}

	// Least power of 2 greater than or equal to value
	// Hacker's Delight Henry S. Warren
	// Rounding Up/Down to the Next Power of 2 branch less
	int clp2(const int& value)
	{
		int v = value;
		v--;
		v |= v >> 1;
		v |= v >> 2;
		v |= v >> 4;
		v |= v >> 8;
		v |= v >> 16;
		return v + 1;
	}

	int clamp(const int& value, const int& min, const int& max)
	{
		return (value > max ? max : value < min ? min : value);
	}

	float clamp(const float& value, const float& min, const float& max)
	{
		return (value > max ? max : value < min ? min : value);
	}

	float degrees(const float& radians)
	{
		return radians * M_180_PI;
	}

	float radians(const float& degrees)
	{
		return degrees * M_PI_180;
	}

	float lerp(const float& a, const float& b, const float& t)
	{
		return (a - b) * t + b;
	}

	// Returns the Cartesian coordinate for one axis of a point that is defined by
	// a given triangle and two normalized barycentric (areal) coordinates.
	// value1 coordinate on one axis of vertex 1 of the defining triangle.
	// value2 coordinate on the same axis of vertex 2 of the defining triangle.
	// value3 coordinate on the same axis of vertex 3 of the defining triangle.
	// amount1 normalized barycentric (areal) coordinate b2, equal to weighting
	// factor for vertex 2, coordinate of which is specified in value2.
	// amount2 normalized barycentric (areal) coordinate b3, equal to weighting
	// factor for vertex 3, coordinate of which is specified in value3.
	// Returns Cartesian coordinate of point with respect to the axis being used.
	float barycentric(const float& value1, const float& value2, const float& value3,
					  const float& amount1, const float& amount2)
	{
		return value1 + (value2 - value1) * amount1 + (value3 - value1) * amount2;
	}

	// Performs a Catmull-Rom interpolation using the specified positions.
	// value1 The first position in the interpolation.
	// value2 The second position in the interpolation.
	// value3 The third position in the interpolation.
	// value4 The fourth position in the interpolation.
	// amount Weighting factor.
	// Returns A position that is the result of the Catmull-Rom interpolation.
	float catmullRom(const float& value1, const float& value2, const float& value3,
					 const float& value4, const float& amount)
	{
		// Using formula from http://www.mvps.org/directx/articles/catmull/
		// Internally using doubles not to lose precission
		double amountsquare = amount * amount;
		double amountcube = amountsquare * amount;
		return
		(2.0f * value2 + (value3 - value1) * amount +
		 (2.0f * value1 - 5.0f * value2 + 4.0f * value3 - value4) * amountsquare +
		 (3.0f * value2 - value1 - 3.0f * value3 + value4) * amountcube) * 0.5f;
	}

	// Performs a Hermite spline interpolation.
	// value1 Source position.
	// tangent1 Source tangent.
	// value2 Source position.
	// tangent2 Source tangent.
	// amount Weighting factor.
	// Returns The result of the Hermite spline interpolation.
	float hermite(const float& value1, const float& tangent1, const float& value2,
				  const float& tangent2, const float& amount)
	{
		// All transformed to double not to lose precission
		// For high values of amount the result is NaN instead of Infinity
		float result = 0.0f;
		double v1 = value1, v2 = value2, t1 = tangent1, t2 = tangent2, s = amount;
		double ssquare = s * s;
		double scube = ssquare * s;

		if (amount == 0.0f)
			result = value1;
		else if (amount == 1.0f)
			result = value2;
		else
			result = (2 * v1 - 2 * v2 + t2 + t1) * scube +
			(3 * v2 - 3 * v1 - 2 * t1 - t2) * ssquare +
			t1 * s + v1;
		return result;
	}

	// Interpolates between two values using a cubic equation.
	// value1 Source value.
	// value2 Source value.
	// amount Weighting value.
	// Returns Interpolated value.
	float smoothStep(const float& value1, const float& value2, const float& amount)
	{
		// It is expected that 0 < amount < 1
		// If amount < 0, return value1
		// If amount > 1, return value2
		return hermite(value1, 0.0f, value2, 0.0f, clamp(amount, 0.0f, 1.0f));
	}
	
}
