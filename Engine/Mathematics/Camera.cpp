#include "Camera.h"

namespace Engine
{
	
	Camera::Camera()
	:	m_position(0.0f, 0.0f, 0.0f)
	,	m_rotation(0.0f, 0.0f, 0.0f)
	{ }
	
	Camera::~Camera()
	{ }
	
	void Camera::setPosition(const float& x, const float& y, const float& z)
	{
		m_position.x = x;
		m_position.y = y;
		m_position.z = z;
	}
	
	void Camera::setRotation(const float& x, const float& y, const float& z)
	{
		m_rotation.x = x;
		m_rotation.y = y;
		m_rotation.z = z;
	}
	
	void Camera::render()
	{
#ifdef __APPLE__
		Vec3 up, lookAt;
		Mat4 rotationMatrix;
#endif //__APPLE__
		
#ifdef _WIN32
		D3DXVECTOR3 up, lookAt;
		D3DXMATRIX rotationMatrix;
#endif //_WIn32
		
		// Setup up vector
		up.x = 0.0f;
		up.y = 1.0f;
		up.z = 0.0f;
		
		// Setup lookAt
		lookAt.x = 0.0f;
		lookAt.y = 0.0f;
		lookAt.z = 1.0f;
		
		// Set the yaw y, pitch x, roll z rotations in radians
		float pitch = float(m_rotation.x * M_PI_180);
		float yaw   = float(m_rotation.y * M_PI_180);
		float roll  = float(m_rotation.z * M_PI_180);
		
		// Create the rotation matrix from yaw, pitch roll values
#ifdef __APPLE__
		matrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);
#endif //__APPLE__
		
#ifdef _WIN32
		D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);
#endif //_WIn32
		
		// Transform lookAt and up vector by rotation matrix so the view is
		// correctly rotated at the origin
#ifdef __APPLE__
		vec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
		vec3TransformCoord(&up, &up, &rotationMatrix);
#endif //__APPLE__
		
#ifdef _WIN32
		D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
		D3DXVec3TransformCoord(&up, &up, &rotationMatrix);
#endif //_WIN32
		
		// Translate rotated camera position to the location of the viewer
		lookAt += m_position;
		
		// Finally create the view matrix from three updated vectors
#ifdef __APPLE__
		matrixLookAtLh(&m_viewMatrix, &m_position, &lookAt, &up);
#endif //__APPLE__
		
#ifdef _WIN32
		D3DXMatrixLookAtLH(&m_viewMatrix, &m_position, &lookAt, &up);
#endif //_WIN32
	}
	
#ifdef __APPLE__
	const Vec3* Camera::getPosition()
	{
		return (Vec3*)&m_position;
	}
	
	const Vec3* Camera::getRotation()
	{
		return (Vec3*)&m_rotation;
	}
	
	const Mat4* Camera::getViewMatrix()
	{
		return &m_viewMatrix;
	}
#endif //__APPLE__
	
#ifdef _WIN32
	const D3DXVECTOR3* Camera::getPosition()
	{
		return &m_position;
	}
	
	const D3DXVECTOR3* Camera::getRotation()
	{
		return &m_rotation;
	}
	
	const D3DXMATRIX* Camera::getViewMatrix()
	{
		return &m_viewMatrix;
	}
#endif //_WIN32
	
#ifdef __APPLE__
	Mat4* Camera::matrixRotationYawPitchRoll(Mat4* pOut, float yaw, float pitch, float roll)
	{
		// Yaw * Pitch * Roll unoptimized but functional with the gimble lock
		*pOut = Mat4::rotateY(yaw) * Mat4::rotateX(pitch) * Mat4::rotateZ(roll);
		return pOut;
	}
	
	Vec3* Camera::vec3TransformCoord(Vec3* pOut, Vec3* pV, Mat4* pM)
	{
		// Transforms the vector, pV (x, y, z, 1), by the matrix, pM,
		// projecting the result back into w=1
		*pOut = (freeVector(*pV) * (*pM)).project();
		return pOut;
	}
	
	Mat4* Camera::matrixLookAtLh(Mat4* pOut, Vec3* pEye, Vec3* pAt, Vec3* pUp)
	{
		//*pOut = Transform::lookatlh(*pEye, *pAt, *pUp);
		//return pOut;
		
		Vec3 look = (*pAt - *pEye).normal();
		Vec3 right  = cross(*pUp, look).normal();
		Vec3 up     = cross(look, right).normal();
		
		*pOut = Mat4(right.x,	right.y,	right.z,	-dot(right, *pEye),
					 up.x,		up.y,		up.z,		-dot(up, *pEye),
					 look.x,	look.y,		look.z,		-dot(look, *pEye),
					 0.0f,		0.0f,		0.0f,		1.0f);
		return pOut;
	}
	
}
#endif //__APPLE__
