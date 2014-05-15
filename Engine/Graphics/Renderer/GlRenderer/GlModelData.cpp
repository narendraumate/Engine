//
//  GlModelData.cpp
//  Application
//
//  Created by Narendra Umate on 5/13/14.
//
//

#include "GlModelData.h"

#define BUFFER_OFFSET(offset) (void*)((char*)NULL + offset)

GlModelData::GlModelData(const GLuint& programId, TextureManager* textureManager)
:	m_programId(programId)
,	m_textureManager(textureManager)
{
	m_indexCount = 0;
}

GlModelData::~GlModelData()
{
	glDisableVertexAttribArray(AttributePosition);
	glDisableVertexAttribArray(AttributeNormal);
	glDisableVertexAttribArray(AttributeTexcoord);

	glDeleteTextures(TextureCount, m_textures);
	glDeleteBuffers(VboCount, m_vbos);
	glDeleteVertexArrays(VaoCount, m_vaos);
	glDeleteBuffers(EboCount, m_ebos);
}

void GlModelData::addShape(const tinyobj::shape_t& shape)
{
	positions.insert(positions.end(), shape.mesh.positions.begin(), shape.mesh.positions.end());
	normals.insert(normals.end(), shape.mesh.normals.begin(), shape.mesh.normals.end());
	texcoords.insert(texcoords.end(), shape.mesh.texcoords.begin(), shape.mesh.texcoords.end());
	indices.insert(indices.end(), shape.mesh.indices.begin(), shape.mesh.indices.end());
	m_indexCount += shape.mesh.indices.size();
}

void GlModelData::combine()
{
	unsigned int sizeOfPositions = sizeof(positions[0]) * positions.size();
	unsigned int sizeOfNormals = sizeof(normals[0]) * normals.size();
	unsigned int sizeOfTexcoords = sizeof(texcoords[0]) * texcoords.size();
	unsigned int sizeOfIndices = sizeof(indices[0]) * indices.size();

	glGenBuffers(EboCount, m_ebos);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebos[EboTriangles]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices, &indices[0], GL_STATIC_DRAW);
	//No Vertex Attrib Pointer for Index buffer

	glGenVertexArrays(VaoCount, m_vaos);
	glBindVertexArray(m_vaos[VaoTriangles]);

	glGenBuffers(VboCount, m_vbos);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbos[VboTriangles]);
	glBufferData(GL_ARRAY_BUFFER, sizeOfPositions + sizeOfNormals + sizeOfTexcoords, NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeOfPositions, &positions[0]);
	glBufferSubData(GL_ARRAY_BUFFER, sizeOfPositions, sizeOfNormals, &normals[0]);
	glBufferSubData(GL_ARRAY_BUFFER, sizeOfPositions + sizeOfNormals, sizeOfTexcoords, &texcoords[0]);

	glVertexAttribPointer(AttributePosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(AttributeNormal, 3, GL_FLOAT, GL_TRUE, 0, BUFFER_OFFSET(sizeOfPositions));
	glVertexAttribPointer(AttributeTexcoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeOfPositions + sizeOfNormals));

#define TEXTURE_2D

#ifdef TEXTURE_2D
	glGenTextures(TextureCount, m_textures);
#endif
	/*
	// Ambient TODO
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

	// Specular TODO
	if (!material.specular_texname.empty())
	{
		//cout << "specular_texname " << material.specular_texname << endl;
		loadTexture(GL_TEXTURE2, material.specular_texname, TextureSpecular);
	}

	// Normal TODO
	if (!material.normal_texname.empty())
	{
		//cout << "normal_texname " << material.normal_texname << endl;
		loadTexture(GL_TEXTURE3, material.normal_texname, TextureNormal);
	}
	*/
	pushTextureSamplers();
	////pushMaterialParameters(material);

	glEnableVertexAttribArray(AttributePosition);
	glEnableVertexAttribArray(AttributeNormal);
	glEnableVertexAttribArray(AttributeTexcoord);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void GlModelData::draw()
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

	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void GlModelData::pushTextureSamplers()
{
	glUseProgram(m_programId);

	glUniform1i(glGetUniformLocation(m_programId, "ambientTextureSampler"), 0);
	glUniform1i(glGetUniformLocation(m_programId, "diffuseTextureSampler"), 1);
	glUniform1i(glGetUniformLocation(m_programId, "specularTextureSampler"), 2);
	glUniform1i(glGetUniformLocation(m_programId, "normalTextureSampler"), 3);

	glUseProgram(0);
}
