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

	GlModel::GlModel(const GLuint& programId, const Mat4* viewMatrixPtr, const std::string& objFilePath, const std::string& mtlBasePath)
	:	m_programId(programId)
	,	m_position(0.0f, 0.0f, 0.0f)
	,	m_rotation(0.0f, 0.0f, 0.0f)
	,	m_scale(1.0f, 1.0f, 1.0f)
	,	m_modelMatrix()
	,	m_viewMatrixPtr(viewMatrixPtr)
	,	m_modelViewMatrix()
	,	m_normMatrix()
	{
//----------------------------------------------------------------------------//
		std::vector<float> positions; 
		std::vector<float> normals;
		std::vector<float> texCoords;
		std::vector<unsigned int> indices;
		tinyobj::material_t material;
		
		std::vector<tinyobj::shape_t> shapes;
		std::string error = tinyobj::LoadObj(shapes, objFilePath.c_str(), mtlBasePath.c_str());
						
		if (error.empty())
		{
			/*int i = 0;
			for (auto it = shapes.begin(); it != shapes.end(); ++it)
			{
				positions.insert(positions.end(), it->mesh.positions.begin(), it->mesh.positions.end());
				normals.insert(normals.end(), it->mesh.normals.begin(), it->mesh.normals.end());
				texCoords.insert(texCoords.end(), it->mesh.texcoords.begin(), it->mesh.texcoords.end());
				indices.insert(indices.end(), it->mesh.indices.begin(), it->mesh.indices.end());
				if (++i == 1) break;
			}*/
			
			int i = 0;
			std::cout << "Shape "<< i << " "<< shapes[i].name << std::endl;
			material = shapes[i].material;
			positions = shapes[i].mesh.positions;
			normals = shapes[i].mesh.normals;
			texCoords = shapes[i].mesh.texcoords;
			indices = shapes[i].mesh.indices;			
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
			
			if (!material.diffuse_texname.empty())
			{
				StbImage texture(Utils::singleton()->findFilePath(material.diffuse_texname));
				texture.flipY();
				
				glGenTextures(1, m_textures);
				glBindTexture(GL_TEXTURE_2D, m_textures[TextureDiffuse]);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.getSizeX(), texture.getSizeY(), 0, GL_RGBA, GL_UNSIGNED_BYTE, &(texture.getPixels()[0]));

				glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				
				glGenerateMipmap(GL_TEXTURE_2D);
							
				glBindTexture(GL_TEXTURE_2D, 0);
			}
			//pushTextureSamplers();//??
			
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

	GlModel::~GlModel()
	{
//----------------------------------------------------------------------------//
		glDisableVertexAttribArray(AttributePosition);
		glDisableVertexAttribArray(AttributeNormal);
		glDisableVertexAttribArray(AttributeTexCoord);
		
		glDeleteTextures(TextureCount, m_textures);
		glDeleteBuffers(VboCount, m_vbos);
		glDeleteVertexArrays(VaoCount, m_vaos);
//----------------------------------------------------------------------------//
	}

	void GlModel::draw()
	{
//----------------------------------------------------------------------------//
		glUseProgram(m_programId);
		//glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_textures[TextureDiffuse]);
		glBindVertexArray(m_vaos[VaoTriangles]);
		glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
		glUseProgram(0);
//----------------------------------------------------------------------------//
	}
	
	void GlModel::pushModelMatrix()
	{
		glUseProgram(m_programId);
		GLint modelMatrixLocation = glGetUniformLocation(m_programId, "model");
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, (float*)&m_modelMatrix);
		glUseProgram(0);
	}

	void GlModel::pushViewMatrix()
	{
		glUseProgram(m_programId);
		GLint viewMatrixLocation = glGetUniformLocation(m_programId, "view");
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, (float*)m_viewMatrixPtr);
		glUseProgram(0);
	}

	void GlModel::pushModelViewMatrix()
	{
		glUseProgram(m_programId);
		GLint modelViewMatrixLocation = glGetUniformLocation(m_programId, "modelView");
		glUniformMatrix4fv(modelViewMatrixLocation, 1, GL_FALSE, (float*)&m_modelViewMatrix);
		glUseProgram(0);
	}

	void GlModel::pushNormMatrix()
	{
		glUseProgram(m_programId);
		GLint normMatrixLocation = glGetUniformLocation(m_programId, "norm");
		glUniformMatrix3fv(normMatrixLocation, 1, GL_FALSE, (float*)&m_normMatrix);
		glUseProgram(0);
	}
		
	void GlModel::pushPerspectiveMatrix(const Mat4* perspectiveMatrix)
	{
		glUseProgram(m_programId);
		GLint perspectiveMatrixLocation = glGetUniformLocation(m_programId, "perspective");
		glUniformMatrix4fv(perspectiveMatrixLocation, 1, GL_FALSE, (float*)perspectiveMatrix);
		glUseProgram(0);
	}
	
	void GlModel::pushOrthographicMatrix(const Mat4* orthographicMatrix)
	{
		glUseProgram(m_programId);
		GLint orthographicMatrixLocation = glGetUniformLocation(m_programId, "orthographic");
		glUniformMatrix4fv(orthographicMatrixLocation, 1, GL_FALSE, (float*)orthographicMatrix);
		glUseProgram(0);
	}
	
	/*void GlModel::pushTextureSamplers()
	{
		glUseProgram(m_programId);
		GLint diffuseTextureSamplerLocation = glGetUniformLocation(m_programId, "diffuseTextureSampler");
		glUniform1i(diffuseTextureSamplerLocation, m_textureSamplers[TextureSamplerDiffuse]);
		glUseProgram(0);
	}*/
	
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
		// TODO verify the multiplication order.
		m_modelMatrix = Mat4::identity();
		m_modelMatrix = m_modelMatrix * Mat4::rotateX(m_rotation.x) * Mat4::rotateY(m_rotation.y) * Mat4::rotateZ(m_rotation.z);
		m_modelMatrix = m_modelMatrix * Mat4::translate(m_position);
		m_modelMatrix = m_modelMatrix * Mat4::scale(m_scale);
		pushModelMatrix();

		updateModelViewMatrix();
	}

	void GlModel::updateViewMatrix()
	{
		pushViewMatrix();

		updateModelViewMatrix();
	}

	void GlModel::updateModelViewMatrix()
	{
		m_modelViewMatrix = (*m_viewMatrixPtr) * m_modelMatrix;
		pushModelViewMatrix();

		updateNormMatrix();
	}

	void GlModel::updateNormMatrix()
	{
		// TODO Verify this
		// Normal Matrix is supposedly Top Left 3x3 of ModelView Matrix
		m_normMatrix.d00 = m_modelViewMatrix.d00;
		m_normMatrix.d01 = m_modelViewMatrix.d01;
		m_normMatrix.d02 = m_modelViewMatrix.d02;
		m_normMatrix.d10 = m_modelViewMatrix.d10;
		m_normMatrix.d11 = m_modelViewMatrix.d11;
		m_normMatrix.d12 = m_modelViewMatrix.d12;
		m_normMatrix.d20 = m_modelViewMatrix.d20;
		m_normMatrix.d21 = m_modelViewMatrix.d21;
		m_normMatrix.d22 = m_modelViewMatrix.d22;

		pushNormMatrix();
	}

}
