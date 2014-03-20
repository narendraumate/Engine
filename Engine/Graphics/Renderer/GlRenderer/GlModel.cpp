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
#define USE_OBJLOADER
#ifdef USE_OBJLOADER
	GlModel::GlModel(const GLuint& programId, const std::string& objFilename, const std::string& mtlBasePath)
	:	m_programId(programId)
	,	m_position(0.0f, 0.0f, 0.0f)
	,	m_rotation(0.0f, 0.0f, 0.0f)
	,	m_scale(1.0f, 1.0f, 1.0f)
	,	m_modelMatrix()
	{
//----------------------------------------------------------------------------//
		std::vector<Engine::Vec3> positions; 
		std::vector<Engine::Vec3> normals;
		std::vector<Engine::Vec2> texCoords;
		
		objloader::loadObj(objFilename.c_str(), positions, normals, texCoords);
		
		m_indexCount = positions.size();
		
		glGenVertexArrays(VaoCount, m_vaos);
		glBindVertexArray(m_vaos[VaoTriangles]);		
		
		glGenBuffers(VboCount, m_vbos);
		
		glBindBuffer(GL_ARRAY_BUFFER, m_vbos[VboPosition]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(positions[0]) * positions.size(), &positions[0], GL_STATIC_DRAW);
		glVertexAttribPointer(AttributePosition, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		
		glBindBuffer(GL_ARRAY_BUFFER, m_vbos[VboNormal]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * normals.size(), &normals[0], GL_STATIC_DRAW);
		glVertexAttribPointer(AttributeNormal, 3, GL_FLOAT, GL_TRUE, 0, NULL);
		
		glBindBuffer(GL_ARRAY_BUFFER, m_vbos[VboTexCoord]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords[0]) * texCoords.size(), &texCoords[0], GL_STATIC_DRAW);
		glVertexAttribPointer(AttributeTexCoord, 2, GL_FLOAT, GL_FALSE, 0, NULL);		
		
		glEnableVertexAttribArray(AttributePosition);
		glEnableVertexAttribArray(AttributeNormal);
		glEnableVertexAttribArray(AttributeTexCoord);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
//----------------------------------------------------------------------------//		
		updateModelMatrix();
	}
#else
	GlModel::GlModel(const GLuint& programId, const std::string& objFilePath, const std::string& mtlBasePath)
	:	m_programId(programId)
	,	m_position(0.0f, 0.0f, 0.0f)
	,	m_rotation(0.0f, 0.0f, 0.0f)
	,	m_scale(1.0f, 1.0f, 1.0f)
	,	m_modelMatrix()
	{
//----------------------------------------------------------------------------//
		std::vector<float> positions; 
		std::vector<float> normals;
		std::vector<float> texCoords;
		std::vector<unsigned int> indices;
		
		std::vector<tinyobj::shape_t> shapes;
		std::string error = tinyobj::LoadObj(shapes, objFilePath.c_str(), mtlBasePath.c_str());
						
		if (error.empty())
		{
			int i = 0;
			for (auto it = shapes.begin(); it != shapes.end(); ++it)
			{
				positions.insert(positions.end(), it->mesh.positions.begin(), it->mesh.positions.end());
				normals.insert(normals.end(), it->mesh.normals.begin(), it->mesh.normals.end());
				texCoords.insert(texCoords.end(), it->mesh.texcoords.begin(), it->mesh.texcoords.end());
				indices.insert(indices.end(), it->mesh.indices.begin(), it->mesh.indices.end());
				if (++i == 1) break;
			}
						
			m_indexCount = indices.size();
		
			glGenVertexArrays(VaoCount, m_vaos);
			glBindVertexArray(m_vaos[VaoTriangles]);		
		
			glGenBuffers(VboCount, m_vbos);
		
			glBindBuffer(GL_ARRAY_BUFFER, m_vbos[VboPosition]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(positions[0]) * positions.size(), &positions[0], GL_STATIC_DRAW);
			glVertexAttribPointer(AttributePosition, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		
			glBindBuffer(GL_ARRAY_BUFFER, m_vbos[VboNormal]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * normals.size(), &normals[0], GL_STATIC_DRAW);
			glVertexAttribPointer(AttributeNormal, 3, GL_FLOAT, GL_TRUE, 0, NULL);
		
			glBindBuffer(GL_ARRAY_BUFFER, m_vbos[VboTexCoord]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords[0]) * texCoords.size(), &texCoords[0], GL_STATIC_DRAW);
			glVertexAttribPointer(AttributeTexCoord, 2, GL_FLOAT, GL_FALSE, 0, NULL);
			
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbos[VboIndex]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);
			//No Vertex Attrib Pointer for Index buffer
		
			glEnableVertexAttribArray(AttributePosition);
			glEnableVertexAttribArray(AttributeNormal);
			glEnableVertexAttribArray(AttributeTexCoord);
		
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}
		else
		{
			std::cerr << error;
		}
//----------------------------------------------------------------------------//		
		updateModelMatrix();
	}
#endif // USE_OBJLOADER
	GlModel::~GlModel()
	{
		glDisableVertexAttribArray(AttributePosition);
		glDisableVertexAttribArray(AttributeNormal);
		glDisableVertexAttribArray(AttributeTexCoord);
		
		glDeleteBuffers(VboCount, m_vbos);
		glDeleteVertexArrays(VaoCount, m_vaos);		
	}
	
	void GlModel::setViewMatrix(const Mat4* viewMatrix)
	{
		glUseProgram(m_programId);
		GLint viewMatrixLocation = glGetUniformLocation(m_programId, "view");
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, (float*)viewMatrix);
		glUseProgram(0);
	}
	
	void GlModel::setModelMatrix(const Mat4* modelMatrix)
	{
		glUseProgram(m_programId);
		GLint modelMatrixLocation = glGetUniformLocation(m_programId, "model");
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, (float*)modelMatrix);
		glUseProgram(0);
	}
	
	void GlModel::setPerspectiveMatrix(const Mat4* perspectiveMatrix)
	{
		glUseProgram(m_programId);
		GLint perspectiveMatrixLocation = glGetUniformLocation(m_programId, "perspective");
		glUniformMatrix4fv(perspectiveMatrixLocation, 1, GL_FALSE, (float*)perspectiveMatrix);
		glUseProgram(0);
	}
	
	void GlModel::setOrthographicMatrix(const Mat4* orthographicMatrix)
	{
		glUseProgram(m_programId);
		GLint orthographicMatrixLocation = glGetUniformLocation(m_programId, "orthographic");
		glUniformMatrix4fv(orthographicMatrixLocation, 1, GL_FALSE, (float*)orthographicMatrix);
		glUseProgram(0);
	}
	
	void GlModel::setPosition(const Vec3& position)
	{
		m_position = position;
		updateModelMatrix();
	}
	
	void GlModel::setRotation(const Vec3& rotation)
	{
		m_rotation = rotation;
		updateModelMatrix();
	}
	
	void GlModel::setScale(const Vec3& scale)
	{
		m_scale = scale;
		updateModelMatrix();
	}
	
	void GlModel::updateModelMatrix()
	{
		// TODO verify this.
		m_modelMatrix = Mat4::identity();
		m_modelMatrix = m_modelMatrix * Mat4::rotateX(m_rotation.x) * Mat4::rotateY(m_rotation.y) * Mat4::rotateZ(m_rotation.z);
		m_modelMatrix = m_modelMatrix * Mat4::translate(m_position);
		m_modelMatrix = m_modelMatrix * Mat4::scale(m_scale);
		setModelMatrix(&m_modelMatrix);
	}
	
	void GlModel::draw()
	{
//----------------------------------------------------------------------------//
		glUseProgram(m_programId);
		glBindVertexArray(m_vaos[VaoTriangles]);
#ifdef USE_OBJLOADER
		glDrawArrays(GL_TRIANGLES, 0, m_indexCount);
#else
		glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
#endif
		glUseProgram(0);
//----------------------------------------------------------------------------//
	}
	
}
