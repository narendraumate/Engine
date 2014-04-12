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
	GlModelShape::GlModelShape(const tinyobj::shape_t& shape, const GLuint& programId)
	:	m_programId(programId)
	{
		std::vector<float> positions;
		std::vector<float> normals;
		std::vector<float> texCoords;
		std::vector<unsigned int> indices;
		tinyobj::material_t material;

		std::cout << "shape " << shape.name << std::endl;

		material = shape.material;
		positions = shape.mesh.positions;
		normals = shape.mesh.normals;
		texCoords = shape.mesh.texcoords;
		indices = shape.mesh.indices;
		m_indexCount = indices.size();

		unsigned int sizeOfPositions = sizeof(positions[0]) * positions.size();
		unsigned int sizeOfNormals = sizeof(normals[0]) * normals.size();
		unsigned int sizeOfTexCoords = sizeof(texCoords[0]) * texCoords.size();
		unsigned int sizeOfIndices = sizeof(indices[0]) * indices.size();

		glGenBuffers(EboCount, m_ebos);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebos[EboTriangles]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices, &indices[0], GL_STATIC_DRAW);
		//No Vertex Attrib Pointer for Index buffer

		glGenVertexArrays(VaoCount, m_vaos);
		glBindVertexArray(m_vaos[VaoTriangles]);

		glGenBuffers(VboCount, m_vbos);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbos[VboTriangles]);
		glBufferData(GL_ARRAY_BUFFER,
					 sizeOfPositions + sizeOfNormals + sizeOfTexCoords,
					 NULL, GL_STATIC_DRAW);

		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeOfPositions, &positions[0]);
		glBufferSubData(GL_ARRAY_BUFFER, sizeOfPositions, sizeOfNormals, &normals[0]);
		glBufferSubData(GL_ARRAY_BUFFER, sizeOfPositions + sizeOfNormals, sizeOfTexCoords, &texCoords[0]);

		glVertexAttribPointer(AttributePosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glVertexAttribPointer(AttributeNormal, 3, GL_FLOAT, GL_TRUE, 0, BUFFER_OFFSET(sizeOfPositions));
		glVertexAttribPointer(AttributeTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeOfPositions + sizeOfNormals));

		// Ambient TODO
		if (!material.ambient_texname.empty())
		{
			cout << "ambient_texname " << material.ambient_texname << endl;
		}

		// Diffuse
		if (!material.diffuse_texname.empty())
		{
			cout << "diffuse_texname " << material.diffuse_texname << endl;

			StbImage texture(Utils::singleton()->findFilePath(material.diffuse_texname));
			texture.flipY();
#define TEXTURE_2D
#ifdef TEXTURE_2D
			glGenTextures(TextureCount, m_textures);
			glBindTexture(GL_TEXTURE_2D, m_textures[TextureDiffuse]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.getSizeX(), texture.getSizeY(), 0, GL_RGBA, GL_UNSIGNED_BYTE, &(texture.getPixels()[0]));

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);
#else
			glGenBuffers(TboCount, m_tbos);
			glBindBuffer(GL_TEXTURE_BUFFER, m_tbos[TboTriangles]);
			glBufferData(GL_TEXTURE_BUFFER, texture.getSizeX() * texture.getSizeY(), &(texture.getPixels()[0]), GL_STATIC_DRAW);

			glGenTextures(TextureCount, m_textures);
			glBindTexture(GL_TEXTURE_BUFFER, m_textures[TextureDiffuse]);
			glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA, m_tbos[TboTriangles]);
#endif
		}

		// Specular TODO
		if (!material.specular_texname.empty())
		{
			cout << "specular_texname " << material.specular_texname << endl;
		}

		// Normal TODO
		if (!material.normal_texname.empty())
		{
			cout << "normal_texname " << material.normal_texname << endl;
		}

		//pushTextureSamplers();//??
		//pushTextureBuffers();//??
		pushMaterialParameters(material);

		glEnableVertexAttribArray(AttributePosition);
		glEnableVertexAttribArray(AttributeNormal);
		glEnableVertexAttribArray(AttributeTexCoord);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	GlModelShape::~GlModelShape()
	{
		glDisableVertexAttribArray(AttributePosition);
		glDisableVertexAttribArray(AttributeNormal);
		glDisableVertexAttribArray(AttributeTexCoord);

		glDeleteTextures(TextureCount, m_textures);
		glDeleteBuffers(VboCount, m_vbos);
		glDeleteVertexArrays(VaoCount, m_vaos);
		glDeleteBuffers(EboCount, m_ebos);
	}

	void GlModelShape::draw()
	{
		glBindVertexArray(m_vaos[VaoTriangles]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebos[EboTriangles]);
		glBindTexture(GL_TEXTURE_2D, m_textures[TextureDiffuse]);
		glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);//??
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void GlModelShape::pushMaterialParameters(const tinyobj::material_t& material)
	{
		glUseProgram(m_programId);

		GLint ambientLocation = glGetUniformLocation(m_programId, "ambient");
		glUniform3fv(ambientLocation, 1, material.ambient);
		Logger::singleton()->print3("ambient", material.ambient, 3);

		GLint diffuseLocation = glGetUniformLocation(m_programId, "diffuse");
		glUniform3fv(diffuseLocation, 1, material.diffuse);
		Logger::singleton()->print3("diffuse", material.diffuse, 3);

		GLint specularLocation = glGetUniformLocation(m_programId, "specular");
		glUniform3fv(specularLocation, 1, material.specular);
		Logger::singleton()->print3("specular", material.specular, 3);

		GLint transmittanceLocation = glGetUniformLocation(m_programId, "transmittance");
		glUniform3fv(transmittanceLocation, 1, material.transmittance);
		Logger::singleton()->print3("transmittance", material.transmittance, 3);

		GLint emissionLocation = glGetUniformLocation(m_programId, "emission");
		glUniform3fv(emissionLocation, 1, material.emission);
		Logger::singleton()->print3("emission", material.emission, 3);

		GLint shininessLocation = glGetUniformLocation(m_programId, "shininess");
		glUniform1f(shininessLocation, material.shininess);
		Logger::singleton()->print3("shininess", &material.shininess, 1);

		GLint iorLocation = glGetUniformLocation(m_programId, "ior");
		glUniform1f(iorLocation, material.ior);
		Logger::singleton()->print3("ior", &material.ior, 1);

		glUseProgram(0);
	}
}