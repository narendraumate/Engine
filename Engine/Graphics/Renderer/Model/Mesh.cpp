//
//  Mesh.cpp
//  Application
//
//  Created by Narendra Umate on 1/1/14.
//
//

#include "Mesh.h"

namespace Engine
{
	std::vector<Vec3>& Mesh::getVertices()
	{
		return m_vertices;
	}

	void Mesh::pushVertex(const Vec3& vertex)
	{
		m_vertices.push_back(vertex);
	}

	void Mesh::pushUv(const Vec2& uv)
	{
		m_uvs.push_back(uv);
	}

	void Mesh::pushNormal(const Vec3& normal)
	{
		m_normals.push_back(normal);
	}

	void Mesh::pushData(const Vec3& vertex, const Vec2& uv, const Vec3& normal)
	{
		m_vertices.push_back(vertex);
		m_uvs.push_back(uv);
		m_normals.push_back(normal);
	}
}
