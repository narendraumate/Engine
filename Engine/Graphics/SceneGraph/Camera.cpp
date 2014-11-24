#include "Camera.h"

namespace Engine
{
	Camera::Camera(const int& screenWidth, const int& screenHeight)
	{
		// Calling function from construction might be unsafe.
		resize(screenWidth, screenHeight);
	}
	
	Camera::~Camera()
	{ }

	void Camera::resize(const int& screenWidth, const int& screenHeight)
	{
		// TODO screenNear and screenDepth to be fed from Renderer or Settings.
		setPerspectiveProjection(M_PI_4, (float)screenWidth / (float)screenHeight, 1.0f, 100.0f);

		//TODO Fix this so transition between projections is seamless.
		setOrthographicProjection(screenWidth, screenHeight, 1.0f, 100.0f);
	}

	Vec3 Camera::getPosition()
	{
		return m_position;
	}

	void Camera::setPosition(const Vec3& position)
	{
		m_position = position;
		updateViewMatrix();
	}
	
	void Camera::setAxes(const Vec3& look, const Vec3& right, const Vec3& up)
	{
		m_look = look.normal();
		m_right = right.normal();
		m_up = up.normal();
		updateViewMatrix();
	}
	
	void Camera::setView(const Vec3& position, const Vec3& look, const Vec3& right, const Vec3& up)
	{
		m_position = position;
		m_look = look.normal();
		m_right = right.normal();
		m_up = up.normal();		
		updateViewMatrix();
	}
	
	void Camera::setPerspectiveProjection(const float& fieldOfViewX, const float& screenAspect, const float& screenNear, const float& screenFar)
	{
		m_fieldOfViewX = fieldOfViewX;
		m_screenAspect = screenAspect;
		m_pScreenNear = screenNear;
		m_pScreenFar = screenFar;
		updatePerspectiveProjection();
	}
	
	void Camera::setOrthographicProjection(const int& screenWidth, const int& screenHeight, const float& screenNear, const float& screenFar)
	{
		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;
		m_oScreenNear = screenNear;
		m_oScreenFar = screenFar;
		updateOrthographicProjection();
	}
	
	const Mat4* Camera::getView() const
	{
		return &m_viewMatrix;
	}
	
	const Mat4* Camera::getPerspectiveProjection() const
	{
		return &m_perspectiveProjection;
	}

	const Mat4* Camera::getOrthographicProjection() const
	{
		return &m_orthographicProjection;
	}
	
	void Camera::updateViewMatrix()
	{
		m_viewMatrix = Mat4(m_right.x,	m_right.y,	m_right.z,	-dot(m_right, m_position),
							m_up.x,		m_up.y,		m_up.z,		-dot(m_up, m_position),
							m_look.x,	m_look.y,	m_look.z,	-dot(m_look, m_position),
							0.0f,		0.0f,		0.0f,		1.0f);
	}
	
	void Camera::updatePerspectiveProjection()
	{
		// http://unspecified.wordpress.com/2012/06/21/calculating-the-gluperspective-matrix-and-other-opengl-matrix-maths/
		float h = 1.0f / tan(m_fieldOfViewX * 0.5f);
		float w = h / m_screenAspect;
		m_perspectiveProjection =
		Mat4(w, 0.0f, 0.0f, 0.0f,
			 0.0f, h, 0.0f, 0.0f,
			 0.0f, 0.0f, (m_pScreenFar + m_pScreenNear) / (m_pScreenNear - m_pScreenFar), (2.0f * m_pScreenNear * m_pScreenFar) / (m_pScreenNear - m_pScreenFar),
			 0.0f, 0.0f, -1.0f, 0.0f);
	}
	
	void Camera::updateOrthographicProjection()
	{
		// http://unspecified.wordpress.com/2012/06/21/calculating-the-gluperspective-matrix-and-other-opengl-matrix-maths/
		/*
		m_orthographicProjection = 
		Mat4(2.0f / m_screenWidth, 0.0f, 0.0f, 0.0f,
			 0.0f, 2.0f / m_screenHeight, 0.0f, 0.0f,
			 0.0f, 0.0f, -2.0f / (m_oScreenFar - m_oScreenNear), (m_oScreenNear + m_oScreenFar) / (m_oScreenNear - m_oScreenFar),
			 0.0f, 0.0f, 0.0f, 1.0f);
		 */
		// Experimental but works.
		float multiplier = m_oScreenNear / m_oScreenFar;
		m_orthographicProjection = 
		Mat4((2.0f / m_screenWidth * m_screenHeight * multiplier), 0.0f, 0.0f, 0.0f,
			 0.0f,(2.0f * multiplier), 0.0f, 0.0f,
			 0.0f, 0.0f, -2.0f / (m_oScreenFar - m_oScreenNear), (m_oScreenNear + m_oScreenFar) / (m_oScreenNear - m_oScreenFar),
			 0.0f, 0.0f, 0.0f, 1.0f);			 
	}
	
#ifdef __APPLE__
	/*Mat4* Camera::matrixRotationYawPitchRoll(Mat4* pOut, const float& yaw, const float& pitch, const float& roll)
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
		// Transform of the matrix below.
		// http://msdn.microsoft.com/en-us/library/windows/desktop/bb205342(v=vs.85).aspx
		
		Vec3 look = (*pAt - *pEye).normal();
		Vec3 right  = cross(*pUp, look).normal();
		Vec3 up     = cross(look, right).normal();
		
		*pOut = Mat4(right.x,	right.y,	right.z,	-dot(right, *pEye),
					 up.x,		up.y,		up.z,		-dot(up, *pEye),
					 look.x,	look.y,		look.z,		-dot(look, *pEye),
					 0.0f,		0.0f,		0.0f,		1.0f);
		return pOut;
	}*/
#endif //__APPLE__
}


