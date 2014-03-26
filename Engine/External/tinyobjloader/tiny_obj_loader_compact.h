//
//  tiny_obj_loader_compact.h
//  Application
//
//  Created by Narendra Umate on 3/26/14.
//
//

#ifndef __Application__tiny_obj_loader_compact__
#define __Application__tiny_obj_loader_compact__

#include <fstream>
#include "tiny_obj_loader.h"

namespace tinyobj {
	std::string LoadObjCompact(
						std::vector<shape_t>& shapes,   // [output]
						const char* filename,
						const char* mtl_basepath = NULL);
}

#endif /* defined(__Application__tiny_obj_loader_compact__) */
