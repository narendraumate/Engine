//
//  GlModelData.cpp
//  Application
//
//  Created by Narendra Umate on 5/13/14.
//
//

#include "GlModelData.h"

#define BUFFER_OFFSET(offset) (void*)((char*)NULL + offset)

namespace Engine
{

	GlModelData::GlModelData(const GLuint& programId, TextureManager* textureManager)
	:	m_programId(programId)
	,	m_textureManager(textureManager)
	{
		glGetIntegerv(GL_MAX_ELEMENTS_INDICES, (GLint*)&m_indexBatchSize);
	}

	GlModelData::~GlModelData()
	{ }

	void GlModelData::initialize(const vector<tinyobj::shape_c_t>& shapes_c)
	{
		vector<float> positions;
		vector<float> normals;
		vector<float> texcoords;
		vector<float> tangents;
		vector<float> bitangents;
		vector<unsigned int> indices;

		int indexCount = 0;
		int shapeMeshIndexOffset = 0;

		for (vector<tinyobj::shape_c_t>::const_iterator shape = shapes_c.begin(); shape != shapes_c.end(); ++shape)
		{
			shapeMeshIndexOffset = positions.size() / 3;

			positions.insert(positions.end(), shape->mesh.positions.begin(), shape->mesh.positions.end());
			normals.insert(normals.end(), shape->mesh.normals.begin(), shape->mesh.normals.end());
			texcoords.insert(texcoords.end(), shape->mesh.texcoords.begin(), shape->mesh.texcoords.end());
			tangents.insert(tangents.end(), shape->mesh.tangents.begin(), shape->mesh.tangents.end());
			bitangents.insert(bitangents.end(), shape->mesh.bitangents.begin(), shape->mesh.bitangents.end());

			// Offset new shape indices by previously pushed unique indices
			for (std::vector<unsigned int>::const_iterator shapeMeshIndex = shape->mesh.indices.begin(); shapeMeshIndex != shape->mesh.indices.end(); ++shapeMeshIndex)
			{
				indices.push_back(*shapeMeshIndex + shapeMeshIndexOffset);
			}

			shapeIndexStart.push_back(indexCount);
			shapeIndexCount.push_back(shape->mesh.indices.size());
			indexCount += shape->mesh.indices.size();

			materials.push_back(shape->material);
			pushMaterial(shape->material);
		}

		pushTextureSamplers();

		unsigned int sizeOfPositions = sizeof(positions[0]) * positions.size();
		unsigned int sizeOfNormals = sizeof(normals[0]) * normals.size();
		unsigned int sizeOfTexcoords = sizeof(texcoords[0]) * texcoords.size();
		unsigned int sizeOfTangents = sizeof(tangents[0]) * tangents.size();
		unsigned int sizeOfBitangents = sizeof(bitangents[0]) * bitangents.size();
		unsigned int sizeOfIndices = sizeof(indices[0]) * indices.size();

		glGenBuffers(EboCount, m_ebos);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebos[EboTriangles]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices, &indices[0], GL_STATIC_DRAW);
		//No Vertex Attrib Pointer for Index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glGenVertexArrays(VaoCount, m_vaos);
		glGenBuffers(VboCount, m_vbos);

		glBindVertexArray(m_vaos[VaoTriangles]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbos[VboTriangles]);

		glBufferData(GL_ARRAY_BUFFER, sizeOfPositions + sizeOfNormals + sizeOfTexcoords + sizeOfTangents + sizeOfBitangents, NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeOfPositions, &positions[0]);
		glBufferSubData(GL_ARRAY_BUFFER, sizeOfPositions, sizeOfNormals, &normals[0]);
		glBufferSubData(GL_ARRAY_BUFFER, sizeOfPositions + sizeOfNormals, sizeOfTexcoords, &texcoords[0]);
		glBufferSubData(GL_ARRAY_BUFFER, sizeOfPositions + sizeOfNormals + sizeOfTexcoords, sizeOfTangents, &tangents[0]);
		glBufferSubData(GL_ARRAY_BUFFER, sizeOfPositions + sizeOfNormals + sizeOfTexcoords + sizeOfTangents, sizeOfBitangents, &bitangents[0]);

		glVertexAttribPointer(AttributePosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glVertexAttribPointer(AttributeNormal, 3, GL_FLOAT, GL_TRUE, 0, BUFFER_OFFSET(sizeOfPositions));
		glVertexAttribPointer(AttributeTexcoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeOfPositions + sizeOfNormals));
		glVertexAttribPointer(AttributeTangent, 3, GL_FLOAT, GL_TRUE, 0, BUFFER_OFFSET(sizeOfPositions + sizeOfNormals + sizeOfTexcoords));
		glVertexAttribPointer(AttributeBitangent, 3, GL_FLOAT, GL_TRUE, 0, BUFFER_OFFSET(sizeOfPositions + sizeOfNormals + sizeOfTexcoords + sizeOfTangents));
		glEnableVertexAttribArray(AttributePosition);
		glEnableVertexAttribArray(AttributeNormal);
		glEnableVertexAttribArray(AttributeTexcoord);
		glEnableVertexAttribArray(AttributeTangent);
		glEnableVertexAttribArray(AttributeBitangent);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		positions.clear();
		normals.clear();
		texcoords.clear();
		tangents.clear();
		bitangents.clear();
		indices.clear();
	}

	void GlModelData::deinitialize()
	{
		glDisableVertexAttribArray(AttributePosition);
		glDisableVertexAttribArray(AttributeNormal);
		glDisableVertexAttribArray(AttributeTexcoord);
		glDisableVertexAttribArray(AttributeTangent);
		glDisableVertexAttribArray(AttributeBitangent);

		for (vector<GlTextureCollection>::const_iterator textureCollection = textureCollections.begin(); textureCollection != textureCollections.end(); ++textureCollection)
		{
			glDeleteTextures(1, &textureCollection->m_textures[TextureAmbient]);
			glDeleteTextures(1, &textureCollection->m_textures[TextureDiffuse]);
			glDeleteTextures(1, &textureCollection->m_textures[TextureSpecular]);
			glDeleteTextures(1, &textureCollection->m_textures[TextureNormal]);
		}

		glDeleteBuffers(VboCount, m_vbos);
		glDeleteVertexArrays(VaoCount, m_vaos);
		glDeleteBuffers(EboCount, m_ebos);
	}

	void GlModelData::draw()
	{
		glBindVertexArray(m_vaos[VaoTriangles]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebos[EboTriangles]);

		for (int shapeIndex = 0; shapeIndex < shapeIndexStart.size(); ++shapeIndex)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textureCollections[shapeIndex].m_textures[TextureAmbient]);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, textureCollections[shapeIndex].m_textures[TextureDiffuse]);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, textureCollections[shapeIndex].m_textures[TextureSpecular]);
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, textureCollections[shapeIndex].m_textures[TextureNormal]);
			glActiveTexture(0);

			pushMaterialParameters(materials[shapeIndex]);

			for (unsigned int currentIndex = 0; currentIndex < shapeIndexCount[shapeIndex];)
			{
				if (currentIndex + m_indexBatchSize < shapeIndexCount[shapeIndex])
				{
					// Multiplying by sizeof(GLuint) is critical
					glDrawElements(GL_TRIANGLES, m_indexBatchSize, GL_UNSIGNED_INT, BUFFER_OFFSET((currentIndex + shapeIndexStart[shapeIndex]) * sizeof(GLuint)));
					currentIndex += m_indexBatchSize;
				}
				else
				{
					// Multiplying by sizeof(GLuint) is critical
					glDrawElements(GL_TRIANGLES, shapeIndexCount[shapeIndex] - currentIndex, GL_UNSIGNED_INT, BUFFER_OFFSET((currentIndex + shapeIndexStart[shapeIndex]) * sizeof(GLuint)));
					currentIndex = shapeIndexCount[shapeIndex];
				}
			}
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void GlModelData::pushMaterial(const tinyobj::material_t& material)
	{
		textureCollections.push_back(GlTextureCollection());

		// Ambient
		if (!material.ambient_texname.empty())
		{
			//cout << "ambient_texname " << material.ambient_texname << endl;
			textureCollections.back().m_textures[TextureAmbient] = loadTexture(GL_TEXTURE0, material.ambient_texname, TextureAmbient);
		}

		// Diffuse
		if (!material.diffuse_texname.empty())
		{
			//cout << "diffuse_texname " << material.diffuse_texname << endl;
			textureCollections.back().m_textures[TextureDiffuse] = loadTexture(GL_TEXTURE1, material.diffuse_texname, TextureDiffuse);
		}

		// Specular
		if (!material.specular_texname.empty())
		{
			//cout << "specular_texname " << material.specular_texname << endl;
			textureCollections.back().m_textures[TextureSpecular] = loadTexture(GL_TEXTURE2, material.specular_texname, TextureSpecular);
		}

		// Normal
		if (!material.normal_texname.empty())
		{
			//cout << "normal_texname " << material.normal_texname << endl;
			textureCollections.back().m_textures[TextureNormal] = loadTexture(GL_TEXTURE3, material.normal_texname, TextureNormal);
		}
	}

	void GlModelData::pushTextureSamplers()
	{
		glUniform1i(glGetUniformLocation(m_programId, "ambientTextureSampler"), 0);
		glUniform1i(glGetUniformLocation(m_programId, "diffuseTextureSampler"), 1);
		glUniform1i(glGetUniformLocation(m_programId, "specularTextureSampler"), 2);
		glUniform1i(glGetUniformLocation(m_programId, "normalTextureSampler"), 3);
	}

	void GlModelData::pushMaterialParameters(const tinyobj::material_t& material)
	{
		GLint ambientLocation = glGetUniformLocation(m_programId, "ambient");
		glUniform3fv(ambientLocation, 1, material.ambient);
		//Logger::singleton()->print3("ambient", material.ambient, 3);

		GLint diffuseLocation = glGetUniformLocation(m_programId, "diffuse");
		glUniform3fv(diffuseLocation, 1, material.diffuse);
		//Logger::singleton()->print3("diffuse", material.diffuse, 3);

		GLint specularLocation = glGetUniformLocation(m_programId, "specular");
		glUniform3fv(specularLocation, 1, material.specular);
		//Logger::singleton()->print3("specular", material.specular, 3);

		GLint transmittanceLocation = glGetUniformLocation(m_programId, "transmittance");
		glUniform3fv(transmittanceLocation, 1, material.transmittance);
		//Logger::singleton()->print3("transmittance", material.transmittance, 3);

		GLint emissionLocation = glGetUniformLocation(m_programId, "emission");
		glUniform3fv(emissionLocation, 1, material.emission);
		//Logger::singleton()->print3("emission", material.emission, 3);

		GLint shininessLocation = glGetUniformLocation(m_programId, "shininess");
		glUniform1f(shininessLocation, material.shininess);
		//Logger::singleton()->print3("shininess", &material.shininess, 1);

		GLint iorLocation = glGetUniformLocation(m_programId, "ior");
		glUniform1f(iorLocation, material.ior);
		//Logger::singleton()->print3("ior", &material.ior, 1);
	}

	// TODO Is textureIndex and textureType necessary?
	GLuint GlModelData::loadTexture(const GLenum& textureIndex, const std::string& textureName, const TextureType& textureType)
	{
		m_textureManager->loadTexture(textureName);

		GLuint texture = 0;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_textureManager->getSizeX(textureName), m_textureManager->getSizeY(textureName), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_textureManager->getPixels(textureName));
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		return texture;
	}

}
