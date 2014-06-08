//
//  tiny_model_loader_compact.h
//  Application
//
//  Created by Narendra Umate on 3/26/14.
//
//

#ifndef __Application__tiny_model_loader_compact__
#define __Application__tiny_model_loader_compact__

#if defined(__linux__)
#include <cstddef>
#include <cstring>
#else
#include <string>
#endif // (__linux__)

#include <assert.h>
#include <fstream>
#include <iostream>
#include <stdint.h>
#include "../../Mathematics/Vector.h"
#include "tiny_mesh_loader.h"
#include "tiny_obj_loader.h"

namespace tinyobj {

	typedef struct
	{
		std::vector<float>          positions;
		std::vector<float>          normals;
		std::vector<float>          texcoords;
		std::vector<float>          tangents;
		std::vector<float>          bitangents;
		std::vector<unsigned int>   indices;
	} mesh_c_t;

	typedef struct
	{
		std::string  name;
		material_t   material;
		mesh_c_t     mesh;
	} shape_c_t;

	std::string LoadModelCompact(std::vector<shape_c_t>& shapes,   // [output]
								 const char* filename,
								 const char* model_basepath = NULL,
								 const bool& enable_compact = true);
}

#endif /* defined(__Application__tiny_model_loader_compact__) */
