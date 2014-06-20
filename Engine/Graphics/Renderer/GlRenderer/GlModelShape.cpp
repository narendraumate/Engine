//
//  GlModelShape.cpp
//  Application
//
//  Created by Narendra Umate on 3/21/14.
//
//

#include "GlModelShape.h"

#define BUFFER_OFFSET(offset) (void*)((char*)NULL + offset)

namespace Engine
{
	GlModelShape::GlModelShape(const tinyobj::shape_c_t& shape_c, const GLuint& programId, TextureManager* textureManager)
	:	m_programId(programId)
	,	m_textureManager(textureManager)
	{
		tinyobj::material_t material;
		std::vector<float> positions;
		std::vector<float> normals;
		std::vector<float> texcoords;
		std::vector<float> tangents;
		std::vector<float> bitangents;
		std::vector<unsigned int> indices;

		//std::cout << "shape " << shape.name << std::endl;

		material = shape_c.material;
		positions = shape_c.mesh.positions;
		normals = shape_c.mesh.normals;
		texcoords = shape_c.mesh.texcoords;
		tangents = shape_c.mesh.tangents;
		bitangents = shape_c.mesh.bitangents;
		indices = shape_c.mesh.indices;
		m_indexCount = shape_c.mesh.indices.size();

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

		glGenVertexArrays(VaoCount, m_vaos);
		glBindVertexArray(m_vaos[VaoTriangles]);

		glGenBuffers(VboCount, m_vbos);
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

		glGenTextures(TextureCount, m_textures);
		pushMaterial(material);
		
		glEnableVertexAttribArray(AttributePosition);
		glEnableVertexAttribArray(AttributeNormal);
		glEnableVertexAttribArray(AttributeTexcoord);
		glEnableVertexAttribArray(AttributeTangent);
		glEnableVertexAttribArray(AttributeBitangent);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		positions.clear();
		normals.clear();
		texcoords.clear();
		tangents.clear();
		bitangents.clear();
		indices.clear();
	}

	GlModelShape::~GlModelShape()
	{
		glDisableVertexAttribArray(AttributePosition);
		glDisableVertexAttribArray(AttributeNormal);
		glDisableVertexAttribArray(AttributeTexcoord);
		glDisableVertexAttribArray(AttributeTangent);
		glDisableVertexAttribArray(AttributeBitangent);

		glDeleteTextures(TextureCount, m_textures);
		glDeleteVertexArrays(VaoCount, m_vaos);
		glDeleteBuffers(VboCount, m_vbos);
		glDeleteBuffers(EboCount, m_ebos);
	}

	void GlModelShape::draw()
	{
		glBindVertexArray(m_vaos[VaoTriangles]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebos[EboTriangles]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_textures[TextureAmbient]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_textures[TextureDiffuse]);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, m_textures[TextureSpecular]);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, m_textures[TextureNormal]);
		glActiveTexture(0);

		glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void GlModelShape::pushMaterial(const tinyobj::material_t& material)
	{
		// Ambient
		if (!material.ambient_texname.empty())
		{
			//cout << "ambient_texname " << material.ambient_texname << endl;
			loadTexture(GL_TEXTURE0, material.ambient_texname, TextureAmbient);
		}

		// Diffuse
		if (!material.diffuse_texname.empty())
		{
			//cout << "diffuse_texname " << material.diffuse_texname << endl;
			loadTexture(GL_TEXTURE1, material.diffuse_texname, TextureDiffuse);
		}

		// Specular
		if (!material.specular_texname.empty())
		{
			//cout << "specular_texname " << material.specular_texname << endl;
			loadTexture(GL_TEXTURE2, material.specular_texname, TextureSpecular);
		}

		// Normal
		if (!material.normal_texname.empty())
		{
			//cout << "normal_texname " << material.normal_texname << endl;
			loadTexture(GL_TEXTURE3, material.normal_texname, TextureNormal);
		}

		pushTextureSamplers();
		pushMaterialParameters(material);
	}

	void GlModelShape::pushTextureSamplers()
	{
		glUniform1i(glGetUniformLocation(m_programId, "ambientTextureSampler"), 0);
		glUniform1i(glGetUniformLocation(m_programId, "diffuseTextureSampler"), 1);
		glUniform1i(glGetUniformLocation(m_programId, "specularTextureSampler"), 2);
		glUniform1i(glGetUniformLocation(m_programId, "normalTextureSampler"), 3);
	}

	void GlModelShape::pushMaterialParameters(const tinyobj::material_t& material)
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

	void GlModelShape::loadTexture(const GLenum& textureIndex, const std::string& textureName, const TextureType& textureType)
	{
		m_textureManager->loadTexture(textureName);

		glActiveTexture(textureIndex);
		glBindTexture(GL_TEXTURE_2D, m_textures[textureType]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_textureManager->getSizeX(textureName), m_textureManager->getSizeY(textureName), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_textureManager->getPixels(textureName));
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(0);
	}

}
