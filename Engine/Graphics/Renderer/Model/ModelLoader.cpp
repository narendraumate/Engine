//
//  ModelLoader.cpp
//  Application
//
//  Created by Narendra Umate on 1/1/14.
//
//

#include "ModelLoader.h"

Engine::ModelLoader* Engine::ModelLoader::s_instance = NULL;

namespace Engine
{

	ModelLoader::ModelLoader()
	{ }

	ModelLoader::~ModelLoader()
	{ }

	ModelLoader* ModelLoader::singleton()
	{
		if (s_instance == NULL)
		{
			s_instance = new ModelLoader();
		}
		return s_instance;
	}

	void ModelLoader::destroySingleton()
	{
		if (s_instance)
		{
			delete s_instance;
			s_instance = NULL;
		}
	}
	
}
