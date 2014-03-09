//
//  ObjLoader.cpp
//  Application
//
//  Created by Narendra Umate on 1/1/14.
//
//

#include "ObjLoader.h"

Engine::ObjLoader* Engine::ObjLoader::s_instance = NULL;

namespace Engine
{

	ObjLoader::ObjLoader()
	{ }

	ObjLoader::~ObjLoader()
	{ }

	ObjLoader* ObjLoader::singleton()
	{
		if (s_instance == NULL)
		{
			s_instance = new ObjLoader();
		}
		return s_instance;
	}

	void ObjLoader::destroySingleton()
	{
		if (s_instance)
		{
			delete s_instance;
			s_instance = NULL;
		}
	}
	
	Mesh* ObjLoader::load(const std::string& strObjFileName)
	{
		Mesh* meshPtr = new WavefrontObject(strObjFileName);
		return meshPtr;
	}
	
	void ObjLoader::unload(Mesh* const meshPtr)
	{
		if (meshPtr)
		{
			delete meshPtr;
		}
	}

}
