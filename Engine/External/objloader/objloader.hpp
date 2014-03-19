#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include "Vector.h"

namespace objloader
{
	bool loadObj(
				 const char * path, 
				 std::vector<Engine::Vec3> & out_vertices, 
				 std::vector<Engine::Vec3> & out_normals,
				 std::vector<Engine::Vec2> & out_uvs 
				 );
}
#endif