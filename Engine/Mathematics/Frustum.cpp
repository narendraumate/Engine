//
//  Frustum.cpp
//  Renderer
//
//  Created by Narendra Umate on 5/4/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#include "Frustum.h"

namespace Engine
{
	
	Frustum::Frustum()
	{ }
	
	Frustum::Frustum(const Frustum& other)
	{
		m_planes[0] = other.m_planes[0];
		m_planes[1] = other.m_planes[1];
		m_planes[2] = other.m_planes[2];
		m_planes[3] = other.m_planes[3];
		m_planes[4] = other.m_planes[4];
		m_planes[5] = other.m_planes[5];
	}
	
	Frustum::~Frustum()
	{ }
	
	void Frustum::constructFrustum(const float& screenDepth,
								   const Mat4* projectionMatrix,
								   const Mat4* viewMatrix)
	{
		// Create the frustum matrix from the view matrix and projection matrix.
		// Transpose is OpenGL hack so that indices match DirectX matrix indices.
		Mat4 matrix = (*projectionMatrix * *viewMatrix).transpose();
		
		// Calculate near plane of frustum.
		m_planes[0].a = matrix.d03 + matrix.d02;
		m_planes[0].b = matrix.d13 + matrix.d12;
		m_planes[0].c = matrix.d23 + matrix.d22;
		m_planes[0].d = matrix.d33 + matrix.d32;
		
		// Calculate far plane of frustum.
		m_planes[1].a = matrix.d03 - matrix.d02;
		m_planes[1].b = matrix.d13 - matrix.d12;
		m_planes[1].c = matrix.d23 - matrix.d22;
		m_planes[1].d = matrix.d33 - matrix.d32;
		
		// Calculate left plane of frustum.
		m_planes[2].a = matrix.d03 + matrix.d00;
		m_planes[2].b = matrix.d13 + matrix.d10;
		m_planes[2].c = matrix.d23 + matrix.d20;
		m_planes[2].d = matrix.d33 + matrix.d30;
		
		// Calculate right plane of frustum.
		m_planes[3].a = matrix.d03 - matrix.d00;
		m_planes[3].b = matrix.d13 - matrix.d10;
		m_planes[3].c = matrix.d23 - matrix.d20;
		m_planes[3].d = matrix.d33 - matrix.d30;
		
		// Calculate top plane of frustum.
		m_planes[4].a = matrix.d03 - matrix.d01;
		m_planes[4].b = matrix.d13 - matrix.d11;
		m_planes[4].c = matrix.d23 - matrix.d21;
		m_planes[4].d = matrix.d33 - matrix.d31;
		
		// Calculate bottom plane of frustum.
		m_planes[5].a = matrix.d03 + matrix.d01;
		m_planes[5].b = matrix.d13 + matrix.d11;
		m_planes[5].c = matrix.d23 + matrix.d21;
		m_planes[5].d = matrix.d33 + matrix.d31;
		
		// Normalize frustum planes.
		m_planes[0].normalize();
		m_planes[1].normalize();
		m_planes[2].normalize();
		m_planes[3].normalize();
		m_planes[4].normalize();
		m_planes[5].normalize();
	}
	
	bool Frustum::checkPoint(const Vec3& point)
	{
		// Check if the point is inside all six planes of the view frustum.
		for (int i = 0; i < 6; i++)
		{
			if (m_planes[i].dot(point) < 0.0f)
			{
				return false;
			}
		}
		return true;
	}
	
	bool Frustum::checkCube(const Vec3& center, const float& radius)
	{
		// Check if any one point of the cube is in the view frustum.
		for (int i = 0; i < 6; i++)
		{
			if (m_planes[i].dot(Vec3((center.x - radius), (center.y - radius), (center.z - radius))) >= 0.0f)
			{
				continue;
			}
			else if (m_planes[i].dot(Vec3((center.x + radius), (center.y - radius), (center.z - radius))) >= 0.0f)
			{
				continue;
			}
			else if (m_planes[i].dot(Vec3((center.x - radius), (center.y + radius), (center.z - radius))) >= 0.0f)
			{
				continue;
			}
			else if (m_planes[i].dot(Vec3((center.x + radius), (center.y + radius), (center.z - radius))) >= 0.0f)
			{
				continue;
			}
			else if (m_planes[i].dot(Vec3((center.x - radius), (center.y - radius), (center.z + radius))) >= 0.0f)
			{
				continue;
			}
			else if (m_planes[i].dot(Vec3((center.x + radius), (center.y - radius), (center.z + radius))) >= 0.0f)
			{
				continue;
			}
			else if (m_planes[i].dot(Vec3((center.x - radius), (center.y + radius), (center.z + radius))) >= 0.0f)
			{
				continue;
			}
			else if (m_planes[i].dot(Vec3((center.x + radius), (center.y + radius), (center.z + radius))) >= 0.0f)
			{
				continue;
			}
			
			return false;
		}
		
		return true;
	}
	
	bool Frustum::checkSphere(const Vec3& center, const float& radius)
	{
		// Check if the radius of the sphere is inside the view frustum.
		for (int i = 0; i < 6; i++)
		{
			if (m_planes[i].dot(center) < -radius)
			{
				return false;
			}
		}
		return true;
	}
	
	bool Frustum::checkRectangle(const Vec3& center, const Vec3& size)
	{
		// Check if any one point of the cube is in the view frustum.
		for (int i = 0; i < 6; i++)
		{
			if (m_planes[i].dot(Vec3((center.x - size.x), (center.y - size.y), (center.z - size.z))) >= 0.0f)
			{
				continue;
			}
			else if (m_planes[i].dot(Vec3((center.x + size.x), (center.y - size.y), (center.z - size.z))) >= 0.0f)
			{
				continue;
			}
			else if (m_planes[i].dot(Vec3((center.x - size.x), (center.y + size.y), (center.z - size.z))) >= 0.0f)
			{
				continue;
			}
			else if (m_planes[i].dot(Vec3((center.x + size.x), (center.y + size.y), (center.z - size.z))) >= 0.0f)
			{
				continue;
			}
			else if (m_planes[i].dot(Vec3((center.x - size.x), (center.y - size.y), (center.z + size.z))) >= 0.0f)
			{
				continue;
			}
			else if (m_planes[i].dot(Vec3((center.x + size.x), (center.y - size.y), (center.z + size.z))) >= 0.0f)
			{
				continue;
			}
			else if (m_planes[i].dot(Vec3((center.x - size.x), (center.y + size.y), (center.z + size.z))) >= 0.0f)
			{
				continue;
			}
			else if (m_planes[i].dot(Vec3((center.x + size.x), (center.y + size.y), (center.z + size.z))) >= 0.0f)
			{
				continue;
			}
			
			return false;
		}
		
		return true;
	}
	
}
