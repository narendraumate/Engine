//
//  ObjLoader.h
//  Application
//
//  Created by Narendra Umate on 1/1/14.
//
//

#ifndef __Application__ObjLoader__
#define __Application__ObjLoader__

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "../../../Mathematics/Vector.h"
#include "Mesh.h"
#include "Utils.h"

namespace Engine
{

	class ObjLoader
	{
	private:
		ObjLoader();
		~ObjLoader();
		static ObjLoader* s_instance;

	public:
		static ObjLoader* singleton();
		static void destroySingleton();
		Mesh loadObj(const std::string& strObjFileName);
	};

}

#endif /* defined(__Application__ObjLoader__) */
