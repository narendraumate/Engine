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
	materials.push_back(shape.material);
	positions.insert(positions.end(), shape.mesh.positions.begin(), shape.mesh.positions.end());
	normals.insert(normals.end(), shape.mesh.normals.begin(), shape.mesh.normals.end());
	texcoords.insert(texcoords.end(), shape.mesh.texcoords.begin(), shape.mesh.texcoords.end());
	indices.insert(indices.end(), shape.mesh.indices.begin(), shape.mesh.indices.end());

	shapeBeginIndices.push_back(m_indexCount);
	m_indexCount += shape.mesh.indices.size();
	shapeEndIndices.push_back(m_indexCount - 1);
}

void GlModelData::combine()
{
	sizeOfPositions = sizeof(positions[0]) * positions.size();
	sizeOfNormals = sizeof(normals[0]) * normals.size();
	sizeOfTexcoords = sizeof(texcoords[0]) * texcoords.size();
	sizeOfIndices = sizeof(indices[0]) * indices.size();

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

	glGenTextures(TextureCount, m_textures);
	////

	glEnableVertexAttribArray(AttributePosition);
	glEnableVertexAttribArray(AttributeNormal);
	glEnableVertexAttribArray(AttributeTexcoord);

	glVertexAttribPointer(AttributePosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(AttributeNormal, 3, GL_FLOAT, GL_TRUE, 0, BUFFER_OFFSET(sizeOfPositions));
	glVertexAttribPointer(AttributeTexcoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeOfPositions + sizeOfNormals));

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void GlModelData::draw()
{
	glBindVertexArray(m_vaos[VaoTriangles]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebos[EboTriangles]);

#define ONE_GROUP
#if defined(ONE_GROUP)
	for (int materialIndex = 0; materialIndex < materials.size(); ++materialIndex)
	{
		////cout << "material: " << materialIndex << "\tstart: "<< shapeBeginIndices[materialIndex] << "\tcount: " << shapeEndIndices[materialIndex] - shapeBeginIndices[materialIndex] + 1 << endl;
		glDrawElements(GL_TRIANGLES, shapeEndIndices[materialIndex] - shapeBeginIndices[materialIndex] + 1, GL_UNSIGNED_INT, BUFFER_OFFSET(shapeBeginIndices[materialIndex]));
		break;
	}
#else
#endif

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
///*
void GlModelData::pushMaterial(const tinyobj::material_t& material)
{
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

	pushTextureSamplers();
	pushMaterialParameters(material);
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

void GlModelData::pushMaterialParameters(const tinyobj::material_t& material)
{
	glUseProgram(m_programId);

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

	glUseProgram(0);
}

void GlModelData::loadTexture(const GLenum& textureIndex, const std::string& textureName, const TextureType& textureType)
{
	m_textureManager->loadTexture(textureName);

	glActiveTexture(textureIndex);

	glBindTexture(GL_TEXTURE_2D, m_textures[textureType]);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_textureManager->getSizeX(textureName), m_textureManager->getSizeY(textureName), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_textureManager->getPixels(textureName));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(0);
}
