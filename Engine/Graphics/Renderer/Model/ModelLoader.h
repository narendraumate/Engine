//
//  ModelLoader.h
//  Application
//
//  Created by Narendra Umate on 1/1/14.
//
//

#ifndef __Application__ModelLoader__
#define __Application__ModelLoader__

#include <iostream>
#include "../../../External/assimp/include/assimp/Importer.hpp"

namespace Engine
{

	class ModelLoader
	{
	private:
		ModelLoader();
		~ModelLoader();
		static ModelLoader* s_instance;
		Assimp::Importer m_importer;

	public:
		static ModelLoader* singleton();
		static void destroySingleton();
	};

}

#endif /* defined(__Application__ModelLoader__) */
