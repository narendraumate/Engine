//
//  GlModel.cpp
//  Application
//
//  Created by Narendra Umate on 3/16/14.
//
//

#include "GlModel.h"

namespace Engine
{

	GlModel::GlModel(std::string objFilename)
	:	m_loaded(false)
	{
		if (tinyobj::LoadObj(shapes, objFilename.c_str()).empty())
		{			
			std::vector<GLuint> shaders;
			shaders.push_back(GlShader::loadShader("simple.vertex", GL_VERTEX_SHADER));
			shaders.push_back(GlShader::loadShader("simple.fragment", GL_FRAGMENT_SHADER));
			ProgramID = GlProgram::createProgram(shaders);
		
			
			struct VertexData
			{
				GLubyte color[4];
				GLfloat position[2];
			};
			
			VertexData vertices[6] =
			{
				{{ 255,   0,   0, 255 }, { -0.90, -0.90 }},  // Triangle 1
				{{   0, 255,   0, 255 }, {  0.85, -0.90 }},
				{{   0,   0, 255, 255 }, { -0.90,  0.85 }},
				
				{{   0, 255, 255, 255 }, {  0.90, -0.85 }},  // Triangle 2
				{{ 255,   0, 255, 255 }, {  0.90,  0.90 }},
				{{ 255, 255,   0, 255 }, { -0.85,  0.90 }}
			};
			
			glGenVertexArrays(NumVAOs, VAOs);
			glBindVertexArray(VAOs[Triangles]);
			
			glGenBuffers(NumBuffers, Buffers);
			glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			
			glUseProgram(ProgramID);
			glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), BUFFER_OFFSET(sizeof(vertices[0].color)));
			glVertexAttribPointer(vColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexData), BUFFER_OFFSET(0));
			
			glEnableVertexAttribArray(vPosition);
			glEnableVertexAttribArray(vColor);
			
			m_loaded = true;
		}
		else
		{
			m_loaded = false;
		}
	}
	
	GlModel::~GlModel()
	{
		glDisableVertexAttribArray(vPosition);
		glDisableVertexAttribArray(vColor);
		glDeleteBuffers(NumBuffers, Buffers);
		glDeleteVertexArrays(NumVAOs, VAOs);
		GlProgram::deleteProgram(ProgramID);
	}
	
	void GlModel::render()
	{
//----------------------------------------------------------------------------//
		glDrawArrays(GL_TRIANGLES, 0, NumVertices);
//----------------------------------------------------------------------------//
	}
	
}
