//
//  GlModelData.h
//  Application
//
//  Created by Narendra Umate on 5/13/14.
//
//

#ifndef __Application__GlModelData__
#define __Application__GlModelData__

#include <iostream>
#include "GlProgram.h"
#include "GlShader.h"
#include "../Common/TextureManager.h"
#include "../../../../Application/Common/Logger.h"
#include "../../../External/stbi/StbImage.h"
#include "../../../External/tinyobjloader/tiny_obj_loader_compact.h"

class GlModelData
{
public:
	GlModelData(const GLuint& programId, TextureManager* textureManager);
	~GlModelData();

	void addShape(const tinyobj::shape_t& shape);
	void combine();
	void draw();

private:
	GLuint m_programId;
	TextureManager* m_textureManager;

	enum Ebo { EboTriangles, EboCount };
	enum Vao { VaoTriangles, VaoCount };
	enum Vbo { VboTriangles, VboCount };
	enum Tbo { TboTriangles, TboCount };

	enum AttributeType { AttributePosition, AttributeNormal, AttributeTexCoord, AttributeCount };
	enum TextureType { TextureAmbient, TextureDiffuse, TextureSpecular, TextureNormal, TextureCount };

	GLuint m_ebos[EboCount];
	GLuint m_vaos[VaoCount];
	GLuint m_vbos[VboCount];

	GLuint m_textures[TextureCount];

	GLuint m_indexCount;

	////void pushMaterialParameters(const tinyobj::material_t& material);
	void pushTextureSamplers();

	////void loadTexture(const GLenum& textureIndex, const std::string& textureName, const TextureType& textureType);
//----------------------------------------------------------------------------//
	std::vector<float> positions;
	std::vector<float> normals;
	std::vector<float> texcoords;
	std::vector<unsigned int> indices;
//----------------------------------------------------------------------------//
};

#endif /* defined(__Application__GlModelData__) */
