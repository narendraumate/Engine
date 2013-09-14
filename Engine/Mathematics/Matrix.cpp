//
//  Matrix.cpp
//  Camaleao
//
//  Created by Narendra Umate on 11/4/12.
//  Copyright (c) 2012 Narendra Umate. All rights reserved.
//

#include "Matrix.h"

#define DEGREES
//#define RADIANS

#define LEFTHANDED   //  Default
//#define RIGHTHANDED

//  Reference
//  http://www.geometrictools.com/Documentation/LaplaceExpansionTheorem.pdf
//  http://www.cs.rochester.edu/u/brown/Crypto/assts/projects/adj.html

namespace Engine
{

	//  Mat2

	Mat2::Mat2(void)
	:	d00(1.0f), d01(0.0f),
	d10(0.0f), d11(1.0f)
	{ }

	Mat2::Mat2(const float &m00, const float &m01,
			   const float &m10, const float &m11)
	:	d00(m00), d01(m01),
	d10(m10), d11(m11)
	{ }

	Mat2 Mat2::identity()
	{
		return Mat2(1.0f, 0.0f,
					0.0f, 1.0f);
	}

	Mat2 Mat2::zero()
	{
		return Mat2(0.0f, 0.0f,
					0.0f, 0.0f);
	}

	Mat2 Mat2::transpose()
	{
		return Mat2(d00, d10,
					d01, d11);
	}

	Mat2 Mat2::inverse()
	{
		return Mat2( d11,-d10,
					-d01, d00)
		/determinant();
	}

	float Mat2::determinant()
	{
		return d00*d11 - d10*d01;
	}

	Vec2 Mat2::operator*(const Vec2 &v) const
	{
		return Vec2(d00*v.x + d01*v.y,
					d10*v.x + d11*v.y);
	}

	Mat2 Mat2::operator*(const Mat2 &m) const
	{
		return Mat2(d00*m.d00 + d01*m.d10, d00*m.d01 + d01*m.d11,
					d10*m.d00 + d11*m.d10, d10*m.d01 + d11*m.d11);
	}

	Mat2 Mat2::operator*(const float &f) const
	{
		Mat2 m = *this;
		m.d00 *= f; m.d01 *= f;
		m.d10 *= f; m.d11 *= f;
		return m;
	}

	Mat2 Mat2::operator/(const float &f) const
	{
		Mat2 m = *this;
		m.d00 /= f; m.d01 /= f;
		m.d10 /= f; m.d11 /= f;
		return m;
	}

	//  Mat3

	Mat3::Mat3(void)
	:	d00(1.0f), d01(0.0f), d02(0.0f),
	d10(0.0f), d11(1.0f), d12(0.0f),
	d20(0.0f), d21(0.0f), d22(1.0f)
	{ }

	Mat3::Mat3(const float &m00, const float &m01, const float &m02,
			   const float &m10, const float &m11, const float &m12,
			   const float &m20, const float &m21, const float &m22)
	:	d00(m00), d01(m01), d02(m02),
	d10(m10), d11(m11), d12(m12),
	d20(m20), d21(m21), d22(m22)
	{ }

	Mat3 Mat3::identity()
	{
		return Mat3(1.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 1.0f);
	}

	Mat3 Mat3::zero()
	{
		return Mat3(0.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 0.0f);
	}

	Mat3 Mat3::translate(const float &tx, const float &ty)
	{
		return Mat3(1.0f, 0.0f,   tx,
					0.0f, 1.0f,   ty,
					0.0f, 0.0f, 1.0f);
	}

	Mat3 Mat3::rotate(const float &theta)
	{
#if defined RADIANS
		float cosT = cosf(theta);				   //  theta in radians
		float sinT = sinf(theta);				   //  theta in radians
#elif defined DEGREES
		float cosT = cosf(theta * M_PI / 180.0f);   //  theta in degrees
		float sinT = sinf(theta * M_PI / 180.0f);   //  theta in degrees
#endif

#if defined RIGHTHANDED
		return Mat3( cosT, -sinT, 0.0f,
					sinT,  cosT, 0.0f,
					0.0f,  0.0f, 1.0f);
#elif defined LEFTHANDED
		return Mat3( cosT, sinT, 0.0f,
					-sinT, cosT, 0.0f,
					0.0f, 0.0f, 1.0f);
#endif
	}

	Mat3 Mat3::scale(const float &sx, const float &sy)
	{
		return Mat3(  sx, 0.0f, 0.0f,
					0.0f,   sy, 0.0f,
					0.0f, 0.0f, 1.0f);
	}

	Mat3 Mat3::transpose()
	{
		return Mat3(d00, d10, d20,
					d01, d11, d21,
					d02, d12, d22);
	}

	Mat3 Mat3::inverse()
	{
		return Mat3( d11*d22 - d21*d12,
					-d01*d22 - d21*d02,
					d01*d12 - d11*d02,
					-d10*d22 - d20*d12,
					d00*d22 - d20*d02,
					-d00*d12 - d10*d02,
					d10*d21 - d20*d11,
					-d00*d21 - d20*d01,
					d00*d11 - d10*d01)
		/determinant();
	}

	float Mat3::determinant()
	{
		return d00*(d11*d22-d21*d12)-d01*(d10*d22-d20*d12)+d02*(d10*d21-d20*d11);
	}

	Vec3 Mat3::operator*(const Vec3 &v) const
	{
		return Vec3(d00 * v.x + d01 * v.y + d02 * v.z,
					d10 * v.x + d11 * v.y + d12 * v.z,
					d20 * v.x + d21 * v.y + d22 * v.z);
	}

	Mat3 Mat3::operator*(const Mat3 &m) const
	{
		return Mat3( d00*m.d00 + d01*m.d10 + d02*m.d20,
					d00*m.d01 + d01*m.d11 + d02*m.d21,
					d00*m.d02 + d01*m.d12 + d02*m.d22,
					d10*m.d00 + d11*m.d10 + d12*m.d20,
					d10*m.d01 + d11*m.d11 + d12*m.d21,
					d10*m.d02 + d11*m.d12 + d12*m.d22,
					d20*m.d00 + d21*m.d10 + d22*m.d20,
					d20*m.d01 + d21*m.d11 + d22*m.d21,
					d20*m.d02 + d21*m.d12 + d22*m.d22 );
	}

	Mat3 Mat3::operator*(const float &f) const
	{
		Mat3 m = *this;
		m.d00 *= f; m.d01 *= f; m.d02 *= f;
		m.d10 *= f; m.d11 *= f; m.d12 *= f;
		m.d20 *= f; m.d21 *= f; m.d22 *= f;
		return m;
	}

	Mat3 Mat3::operator/(const float &f) const
	{
		Mat3 m = *this;
		m.d00 /= f; m.d01 /= f; m.d02 /= f;
		m.d10 /= f; m.d11 /= f; m.d12 /= f;
		m.d20 /= f; m.d21 /= f; m.d22 /= f;
		return m;
	}

	//  Mat4

	Mat4::Mat4(void)
	:	d00(1.0f), d01(0.0f), d02(0.0f), d03(0.0f),
	d10(0.0f), d11(1.0f), d12(0.0f), d13(0.0f),
	d20(0.0f), d21(0.0f), d22(1.0f), d23(0.0f),
	d30(0.0f), d31(0.0f), d32(0.0f), d33(1.0f)
	{ }

	Mat4::Mat4(const float &m00,const float &m01,const float &m02,const float &m03,
			   const float &m10,const float &m11,const float &m12,const float &m13,
			   const float &m20,const float &m21,const float &m22,const float &m23,
			   const float &m30,const float &m31,const float &m32,const float &m33)
	:	d00(m00), d01(m01), d02(m02), d03(m03),
	d10(m10), d11(m11), d12(m12), d13(m13),
	d20(m20), d21(m21), d22(m22), d23(m23),
	d30(m30), d31(m31), d32(m32), d33(m33)
	{ }

	Mat4 Mat4::identity()
	{
		return Mat4(1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
	}

	Mat4 Mat4::zero()
	{
		return Mat4(0.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 0.0f);
	}

	Mat4 Mat4::translate(const float &tx, const float &ty, const float &tz)
	{
		return Mat4(1.0f, 0.0f, 0.0f,   tx,
					0.0f, 1.0f, 0.0f,   ty,
					0.0f, 0.0f, 1.0f,   tz,
					0.0f, 0.0f, 0.0f, 1.0f);
	}

	Mat4 Mat4::rotateX(const float &theta)
	{
#if defined RADIANS
		float cosT = cosf(theta);				   //  theta in radians
		float sinT = sinf(theta);				   //  theta in radians
#elif defined DEGREES
		float cosT = cosf(theta * M_PI / 180.0f);   //  theta in degrees
		float sinT = sinf(theta * M_PI / 180.0f);   //  theta in degrees
#endif

#ifdef RIGHTHANDED
		return Mat4( 1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, cosT, sinT, 0.0f,
					0.0f,-sinT, cosT, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
#elif defined LEFTHANDED
		return Mat4( 1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, cosT,-sinT, 0.0f,
					0.0f, sinT, cosT, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
#endif
	}

	Mat4 Mat4::rotateY(const float &theta)
	{
#if defined RADIANS
		float cosT = cosf(theta);				   //  theta in radians
		float sinT = sinf(theta);				   //  theta in radians
#elif defined DEGREES
		float cosT = cosf(theta * M_PI / 180.0f);   //  theta in degrees
		float sinT = sinf(theta * M_PI / 180.0f);   //  theta in degrees
#endif

#ifdef RIGHTHANDED
		return Mat4( cosT, 0.0f,-sinT, 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					sinT, 0.0f, cosT, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
#elif defined LEFTHANDED
		return Mat4( cosT, 0.0f, sinT, 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					-sinT, 0.0f, cosT, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
#endif
	}

	Mat4 Mat4::rotateZ(const float &theta)
	{
#if defined RADIANS
		float cosT = cosf(theta);				   //  theta in radians
		float sinT = sinf(theta);				   //  theta in radians
#elif defined DEGREES
		float cosT = cosf(theta * M_PI / 180.0f);   //  theta in degrees
		float sinT = sinf(theta * M_PI / 180.0f);   //  theta in degrees
#endif

#ifdef RIGHTHANDED
		return Mat4( cosT, sinT, 0.0f, 0.0f,
					-sinT, cosT, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
#elif defined LEFTHANDED
		return Mat4( cosT,-sinT, 0.0f, 0.0f,
					sinT, cosT, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
#endif
	}

	Mat4 Mat4::rotate(const float &theta,
					  const float &x,
					  const float &y,
					  const float &z)
	{
		float alpha = atan2f(x, y);
		float beta  = atan2f(y, z);
		float _theta = theta;

		// Avoid Gimbal lock
		if (y == 0.0f && z == 0.0f)
		{
			if (x == 0.0f)
				alpha = beta = _theta = 0.0f;
			else if (x > 0.0f)
				beta =  M_PI_2;
			else
				beta = -M_PI_2;
		}

		Mat4 m;// = Mat4::identity();

		m = m * Mat4::rotateZ(-alpha);
		m = m * Mat4::rotateX(-beta);
		m = m * Mat4::rotateZ(_theta);
		m = m * Mat4::rotateX( beta);
		m = m * Mat4::rotateZ( alpha);

		return m;
	}

	Mat4 Mat4::rotate(const float &theta, const Vec3 &v)
	{
		return Mat4::rotate(theta, v.x, v.y, v.z);
	}

	Mat4 Mat4::scale(const float &sx, const float &sy, const float &sz)
	{
		return Mat4(  sx, 0.0f, 0.0f, 0.0f,
					0.0f,   sy, 0.0f, 0.0f,
					0.0f, 0.0f,   sz, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
	}

	Mat4 Mat4::transpose()
	{
		return Mat4(d00, d10, d20, d30,
					d01, d11, d21, d31,
					d02, d12, d22, d32,
					d03, d13, d23, d33);
	}

	Mat4 Mat4::inverse()
	{
		float s0 = d00*d11 - d10*d01;
		float s1 = d00*d12 - d10*d02;
		float s2 = d00*d13 - d10*d03;
		float s3 = d01*d12 - d11*d02;
		float s4 = d01*d13 - d11*d03;
		float s5 = d02*d13 - d12*d03;

		float c0 = d20*d31 - d30*d21;
		float c1 = d20*d32 - d30*d22;
		float c2 = d20*d33 - d30*d23;
		float c3 = d21*d32 - d31*d22;
		float c4 = d21*d33 - d31*d23;
		float c5 = d22*d33 - d32*d23;

		return Mat4( d11*c5 - d12*c4 + d13*c3,
					-d01*c5 + d02*c4 - d03*c3,
					d31*s5 - d32*s4 + d33*s3,
					-d21*s5 + d22*s4 - d23*s3,
					-d10*c5 + d12*c2 - d13*c1,
					d00*c5 - d02*c2 + d03*c1,
					-d30*s5 + d32*s2 - d33*s1,
					d20*s5 - d22*s2 + d23*s1,
					d10*c4 - d11*c2 + d13*c0,
					-d00*c4 + d01*c2 - d03*c0,
					d30*s4 - d31*s2 + d33*s0,
					-d20*s4 + d21*s2 - d23*s0,
					-d10*c3 + d11*c1 - d12*c0,
					d00*c3 - d01*c1 + d02*c0,
					-d30*s3 + d31*s1 - d32*s0,
					d20*s3 - d21*s1 + d22*s0)
		/determinant();
	}

	float Mat4::determinant()
	{
		float s0 = d00*d11 - d10*d01;
		float s1 = d00*d12 - d10*d02;
		float s2 = d00*d13 - d10*d03;
		float s3 = d01*d12 - d11*d02;
		float s4 = d01*d13 - d11*d03;
		float s5 = d02*d13 - d12*d03;

		float c0 = d20*d31 - d30*d21;
		float c1 = d20*d32 - d30*d22;
		float c2 = d20*d33 - d30*d23;
		float c3 = d21*d32 - d31*d22;
		float c4 = d21*d33 - d31*d23;
		float c5 = d22*d33 - d32*d23;

		return s0*c5 - s1*c4 + s2*c3 + s3*c2 - s4*c1 + s5*c0;

		/*  return
		 (d00*(d11*(d22*d33-d32*d23)-d12*(d21*d33-d31*d23)+d13*(d21*d32-d31*d22))-
		 d01*(d10*(d22*d33-d32*d23)-d12*(d20*d33-d30*d23)+d13*(d20*d32-d30*d22))+
		 d02*(d10*(d21*d33-d31*d23)-d11*(d20*d33-d30*d23)+d13*(d20*d31-d30*d21))-
		 d03*(d10*(d21*d32-d31*d22)-d11*(d20*d32-d30*d22)+d12*(d20*d31-d30*d21)));*/
	}

	Vec4 Mat4::operator*(const Vec4 &v) const
	{
		return Vec4(d00*v.x + d01*v.y + d02*v.z + d03*v.w,
					d10*v.x + d11*v.y + d12*v.z + d13*v.w,
					d20*v.x + d21*v.y + d22*v.z + d23*v.w,
					d30*v.x + d31*v.y + d32*v.z + d33*v.w);
	}

	Mat4 Mat4::operator*(const Mat4 &m) const
	{
		return Mat4(d00*m.d00 + d01*m.d10 + d02*m.d20 + d03*m.d30,
					d00*m.d01 + d01*m.d11 + d02*m.d21 + d03*m.d31,
					d00*m.d02 + d01*m.d12 + d02*m.d22 + d03*m.d32,
					d00*m.d03 + d01*m.d13 + d02*m.d23 + d03*m.d33,
					d10*m.d00 + d11*m.d10 + d12*m.d20 + d13*m.d30,
					d10*m.d01 + d11*m.d11 + d12*m.d21 + d13*m.d31,
					d10*m.d02 + d11*m.d12 + d12*m.d22 + d13*m.d32,
					d10*m.d03 + d11*m.d13 + d12*m.d23 + d13*m.d33,
					d20*m.d00 + d21*m.d10 + d22*m.d20 + d23*m.d30,
					d20*m.d01 + d21*m.d11 + d22*m.d21 + d23*m.d31,
					d20*m.d02 + d21*m.d12 + d22*m.d22 + d23*m.d32,
					d20*m.d03 + d21*m.d13 + d22*m.d23 + d23*m.d33,
					d30*m.d00 + d31*m.d10 + d32*m.d20 + d33*m.d30,
					d30*m.d01 + d31*m.d11 + d32*m.d21 + d33*m.d31,
					d30*m.d02 + d31*m.d12 + d32*m.d22 + d33*m.d32,
					d30*m.d03 + d31*m.d13 + d32*m.d23 + d33*m.d33);
	}

	Mat4 Mat4::operator*(const float &f) const
	{
		Mat4 m = *this;
		m.d00 *= f; m.d01 *= f; m.d02 *= f; m.d03 *= f;
		m.d10 *= f; m.d11 *= f; m.d12 *= f; m.d13 *= f;
		m.d20 *= f; m.d21 *= f; m.d22 *= f; m.d23 *= f;
		m.d30 *= f; m.d31 *= f; m.d32 *= f; m.d33 *= f;
		return m;
	}
	
	Mat4 Mat4::operator/(const float &f) const
	{
		Mat4 m = *this;
		m.d00 /= f; m.d01 /= f; m.d02 /= f; m.d03 /= f;
		m.d10 /= f; m.d11 /= f; m.d12 /= f; m.d13 /= f;
		m.d20 /= f; m.d21 /= f; m.d22 /= f; m.d23 /= f;
		m.d30 /= f; m.d31 /= f; m.d32 /= f; m.d33 /= f;
		return m;
	}
	
}
