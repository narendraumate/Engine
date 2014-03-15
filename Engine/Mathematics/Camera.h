#ifndef _CAMERA_H_
#define _CAMERA_H_

#ifdef __APPLE__
#include "Matrix.h"
#include "Vector.h"
#endif //__APPLE__

#ifdef _WIN32
#include <D3DX10math.h>
#include "Math/Math.h"
#endif //_WIN32

namespace Engine
{
	
	class Camera
	{
	public:
		Camera();
		~Camera();
		
		void setPosition(const float& x, const float& y, const float& z);
		void setRotation(const float& x, const float& y, const float& z);
		
		void render();
		
#ifdef __APPLE__
		const Vec3* getPosition();
		const Vec3* getRotation();
		const Mat4* getViewMatrix();
#endif //__APPLE__
		
#ifdef _WIN32
		const D3DXVECTOR3* getPosition();
		const D3DXVECTOR3* getRotation();
		const D3DXMATRIX* getViewMatrix();
#endif //_WIN32
		
	private:
		
#ifdef __APPLE__
		Vec3 m_position;
		Vec3 m_rotation;
#endif //__APPLE__
		
#ifdef _WIN32
		D3DXVECTOR3 m_position;
		D3DXVECTOR3 m_rotation;
#endif //_WIN32
		
#ifdef __APPLE__
		Mat4 m_viewMatrix;
#endif //__APPLE__
		
#ifdef _WIN32
		D3DXMATRIX m_viewMatrix;
#endif //_WIN32
		
#ifdef __APPLE__
		Mat4* matrixRotationYawPitchRoll(Mat4* pOut, float yaw, float pitch, float roll);
		Vec3* vec3TransformCoord(Vec3* pOut, Vec3* pV, Mat4* pM);
		Mat4* matrixLookAtLh(Mat4* pOut, Vec3* pEye, Vec3* pAt, Vec3* pUp);
#endif //__APPLE__
		
	};
	
}

#endif //_CAMERA_H_
