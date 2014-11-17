#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../../Mathematics/Actor.h"

#if defined(__APPLE__) || defined(__linux__)
#include "../../Mathematics/Matrix.h"
#include "../../Mathematics/Vector.h"
#endif //__APPLE__ || defined(__linux__)

#ifdef _WIN32
#include <D3DX10math.h>
#include "../../Mathematics/Math.h"
#define Vec3 D3DXVECTOR3
#define Mat4 D3DXMATRIX
#define matrixRotationYawPitchRoll D3DXMatrixRotationYawPitchRoll
#endif //_WIN32

namespace Engine
{
	
	class Camera : public Actor
	{
	public:
		Camera(const int& screenWidth, const int& screenHeight);
		~Camera();

		virtual void setPosition(const Vec3& position);
		virtual void setAxes(const Vec3& look, const Vec3& right, const Vec3& up);
		virtual void setView(const Vec3& position, const Vec3& look, const Vec3& right, const Vec3& up);

		void setPerspectiveProjection(const float& fieldOfViewX, const float& screenAspect, const float& screenNear, const float& screenFar);
		void setOrthographicProjection(const int& screenWidth, const int& screenHeight, const float& screenNear, const float& screenFar);
		const Mat4* getView() const;
		const Mat4* getPerspectiveProjection() const;
		const Mat4* getOrthographicProjection() const;
		void updateViewMatrix();
		void updatePerspectiveProjection();
		void updateOrthographicProjection();
		
	private:
		Mat4 m_viewMatrix;
		
		float m_fieldOfViewX;
		float m_screenAspect;
		float m_pScreenNear;
		float m_pScreenFar;
		Mat4 m_perspectiveProjection;
		
		int m_screenWidth;
		int m_screenHeight;
		float m_oScreenNear;
		float m_oScreenFar;
		Mat4 m_orthographicProjection;
		
#ifdef __APPLE__
		//Mat4* matrixRotationYawPitchRoll(Mat4* pOut, const float& yaw, const float& pitch, const float& roll);
		//Vec3* vec3TransformCoord(Vec3* pOut, Vec3* pV, Mat4* pM);
		//Mat4* matrixLookAtLh(Mat4* pOut, Vec3* pEye, Vec3* pAt, Vec3* pUp);
#endif //__APPLE__
	};
	
}

#endif //_CAMERA_H_
