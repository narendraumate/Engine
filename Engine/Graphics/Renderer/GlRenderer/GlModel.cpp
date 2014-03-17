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

	GlModel::GlModel(GLuint programId, std::string objFilename)
	:	m_programId(programId)
	,	m_loaded(false)
	{
		if (tinyobj::LoadObj(m_shapes, objFilename.c_str()).empty())
		{
			struct VertexData
			{
				GLfloat position[2];
				GLubyte color[4];
			};
			
			VertexData vertices[6] =
			{
				{{ -0.90, -0.90 }, { 255,   0,   0, 255 }},  // Triangle 1
				{{  0.85, -0.90 }, {   0, 255,   0, 255 }},
				{{ -0.90,  0.85 }, {   0,   0, 255, 255 }},
				
				{{  0.90, -0.85 }, {   0, 255, 255, 255 }},  // Triangle 2
				{{  0.90,  0.90 }, { 255,   0, 255, 255 }},
				{{ -0.85,  0.90 }, { 255, 255,   0, 255 }}
			};
			
			glGenVertexArrays(NumVAOs, VAOs);
			glBindVertexArray(VAOs[Triangles]);
			
			glGenBuffers(NumBuffers, Buffers);
			glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			
			glUseProgram(m_programId);
			glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), BUFFER_OFFSET(0));
			glVertexAttribPointer(vColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexData), BUFFER_OFFSET(sizeof(vertices[0].position)));
			
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
		GlProgram::deleteProgram(m_programId);
	}
	
	void GlModel::render()
	{
//----------------------------------------------------------------------------//
		glDrawArrays(GL_TRIANGLES, 0, NumVertices);
//----------------------------------------------------------------------------//
	}
	
}
