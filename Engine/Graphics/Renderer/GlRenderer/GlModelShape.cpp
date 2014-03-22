//
//  GlModelShape.cpp
//  Application
//
//  Created by Narendra Umate on 3/21/14.
//
//

#include "GlModelShape.h"

namespace Engine
{
	GlModelShape::GlModelShape(const tinyobj::shape_t& shape)
	{
		std::vector<float> positions;
		std::vector<float> normals;
		std::vector<float> texCoords;
		std::vector<unsigned int> indices;
		tinyobj::material_t material;

		std::cout << "Shape " << shape.name << std::endl;

		material = shape.material;
		positions = shape.mesh.positions;
		normals = shape.mesh.normals;
		texCoords = shape.mesh.texcoords;
		indices = shape.mesh.indices;
		m_indexCount = indices.size();

		glGenBuffers(1, m_ebos);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebos[EboIndex]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);
		//No Vertex Attrib Pointer for Index buffer

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
	}

	void GlModelShape::draw()
	{
		glBindVertexArray(m_vaos[VaoTriangles]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebos[EboIndex]);
		glBindTexture(GL_TEXTURE_2D, m_textures[TextureDiffuse]);
		glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);//??
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

}