//
//  tiny_mesh_loader.h
//  Application
//
//  Created by Narendra Umate on 6/7/14.
//
//

#ifndef Application_tiny_mesh_loader_h
#define Application_tiny_mesh_loader_h

#if defined(__linux__)
#include <cstddef>
#include <cstring>
#else
#include <string>
#endif // (__linux__)

#include <iostream>
#include <fstream>
#include "tiny_obj_loader.h"

namespace tinyobj {

	std::string LoadMesh(std::vector<shape_t>& shapes_c, const char* filename);

}

#endif
