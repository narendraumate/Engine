//
//  Matrix.h
//  Camaleao
//
//  Created by Narendra Umate on 11/4/12.
//  Copyright (c) 2012 Narendra Umate. All rights reserved.
//

#ifndef __Camaleao__Matrix__
#define __Camaleao__Matrix__

#include "Math.h"
#include "Vector.h"

#if defined(__APPLE__) || defined(__linux__)
#define ROWMAJOR		//  OpenGL
#elif defined(_WIN32)
#define COLUMNMAJOR		//  DirectX
#endif //defined(_WIN32)

namespace Engine
{

	class Vec2;
	class Vec3;
	class Vec4;

	//  Mat2

	class Mat2
	{
	public:

#if defined(COLUMNMAJOR)
		float d00, d01;
		float d10, d11;
#elif defined(ROWMAJOR)
		float d00, d10;
		float d01, d11;
#endif //defined(ROWMAJOR)

		Mat2(void);
		Mat2(const float &m00, const float &m01,
			 const float &m10, const float &m11);

		static Mat2	 identity();
		static Mat2	 zero();

		Mat2			transpose();
		Mat2			inverse();
		float			determinant();

		Vec2			operator*(const Vec2 &v) const;
		Mat2			operator*(const Mat2 &v) const;
		Mat2			operator*(const float &f) const;
		Mat2			operator/(const float &f) const;
	};

	//  Mat3

	class Mat3
	{
	public:

#if defined(COLUMNMAJOR)
		float d00, d01, d02;
		float d10, d11, d12;
		float d20, d21, d22;
#elif defined(ROWMAJOR)
		float d00, d10, d20;
		float d01, d11, d21;
		float d02, d12, d22;
#endif //defined(ROWMAJOR)

		Mat3(void);
		Mat3(const float &m00, const float &m01, const float &m02,
			 const float &m10, const float &m11, const float &m12,
			 const float &m20, const float &m21, const float &m22);

		static Mat3	 identity();
		static Mat3	 zero();

		static Mat3	 translate(const float &tx, const float &ty);
		static Mat3	 translate(const Vec2 &v);
		static Mat3	 rotate(const float &theta);
		static Mat3	 scale(const float &sx, const float &sy);
		static Mat3	 scale(const Vec2 &s);
		
		Mat3			transpose();
		Mat3			inverse();
		float			determinant();

		Vec3			operator*(const Vec3 &v) const;
		Mat3			operator*(const Mat3 &v) const;
		Mat3			operator*(const float &f) const;
		Mat3			operator/(const float &f) const;
	};

	//  Mat4

	class Mat4
	{
	public:

#if defined(COLUMNMAJOR)
		float d00, d01, d02, d03;
		float d10, d11, d12, d13;
		float d20, d21, d22, d23;
		float d30, d31, d32, d33;
#elif defined(ROWMAJOR)
		float d00, d10, d20, d30;
		float d01, d11, d21, d31;
		float d02, d12, d22, d32;
		float d03, d13, d23, d33;
#endif //defined(ROWMAJOR)

		Mat4(void);
		Mat4(const float &m00,const float &m01,const float &m02,const float &m03,
			 const float &m10,const float &m11,const float &m12,const float &m13,
			 const float &m20,const float &m21,const float &m22,const float &m23,
			 const float &m30,const float &m31,const float &m32,const float &m33);

		static Mat4 identity();
		static Mat4 zero();

		static Mat4 translate(const float &tx, const float &ty, const float &tz);
		static Mat4 translate(const Vec3 &v);
		static Mat4 rotateX(const float &theta);
		static Mat4 rotateY(const float &theta);
		static Mat4 rotateZ(const float &theta);
		static Mat4 rotate(const float &theta,
						   const float &x,
						   const float &y,
						   const float &z);
		static Mat4 rotate(const float &theta, const Vec3 &v);
		static Mat4 scale(const float &sx, const float &sy, const float &sz);
		static Mat4 scale(const Vec3 &s);

		Mat4		transpose();
		Mat4		inverse();
		float		determinant();

		Vec4		operator*(const Vec4 &v) const;
		Mat4		operator*(const Mat4 &m) const;
		Mat4		operator*(const float &f) const;
		Mat4		operator/(const float &f) const;
	};
	
}

#endif /* defined(__Camaleao__Matrix__) */
