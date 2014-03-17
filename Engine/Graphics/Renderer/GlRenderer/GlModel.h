//
//  GlModel.h
//  Application
//
//  Created by Narendra Umate on 3/16/14.
//
//

#ifndef __Application__GlModel__
#define __Application__GlModel__

#include <string>
#include "GlProgram.h"
#include "GlShader.h"
#include "../../../External/tinyobjloader/tiny_obj_loader.h"

namespace Engine
{
	class GlModel
	{
	public:
		GlModel(std::string objFilename);
		~GlModel();
		void render();
	private:
		bool m_loaded;
		std::vector<tinyobj::shape_t> m_shapes;
//----------------------------------------------------------------------------//
		enum VAO_IDs { Triangles, NumVAOs };
		enum Buffer_IDs { ArrayBuffer, NumBuffers };
		enum Attribute_IDs { vPosition = 0, vColor = 1 };
		
		GLuint ProgramID;
		GLuint VAOs[NumVAOs];
		GLuint Buffers[NumBuffers];
		
		const GLuint NumVertices = 6;
#define BUFFER_OFFSET(offset) ((void *)(offset))
//----------------------------------------------------------------------------//
	};
}
#endif /* defined(__Application__GlModel__) */
