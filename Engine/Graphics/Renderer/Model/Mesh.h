//
//  Mesh.h
//  Application
//
//  Created by Narendra Umate on 1/1/14.
//
//

#ifndef __Application__Mesh__
#define __Application__Mesh__

#include <vector>
#include "../../../Mathematics/Vector.h"

namespace Engine
{
	class Mesh
	{
	public:
		std::vector<Vec3>& getVertices();
		void pushVertex(const Vec3& vertex);
		void pushUv(const Vec2& vertex);
		void pushNormal(const Vec3& vertex);
		void pushData(const Vec3& vertex, const Vec2& uv, const Vec3& normal);

	private:
		std::vector<Vec3> m_vertices;
		std::vector<Vec2> m_uvs;
		std::vector<Vec3> m_normals;
	};
}

#endif /* defined(__Application__Mesh__) */
