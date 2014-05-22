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

	void initialize(const vector<tinyobj::shape_t>& shapes);
	void deinitialize();

	void draw();

private:
	GLuint m_programId;
	TextureManager* m_textureManager;

	enum Ebo { EboTriangles, EboCount };
	enum Vao { VaoTriangles, VaoCount };
	enum Vbo { VboTriangles, VboCount };
	enum Tbo { TboTriangles, TboCount };

	enum AttributeType { AttributePosition, AttributeNormal, AttributeTexcoord, AttributeCount };
	enum TextureType { TextureAmbient, TextureDiffuse, TextureSpecular, TextureNormal, TextureCount };

	GLuint m_ebos[EboCount];
	GLuint m_vaos[VaoCount];
	GLuint m_vbos[VboCount];

	GLuint m_textures[TextureCount];

	GLuint m_indexCount;

	void pushMaterial(const tinyobj::material_t& material);
	void pushTextureSamplers();
	void pushMaterialParameters(const tinyobj::material_t& material);
	void loadTexture(const GLenum& textureIndex, const std::string& textureName, const TextureType& textureType);
//----------------------------------------------------------------------------//
	vector<tinyobj::material_t> materials;
	vector<float> positions;
	vector<float> normals;
	vector<float> texcoords;
	vector<unsigned int> indices;

	vector<unsigned int> shapeBeginIndices;
	vector<unsigned int> shapeEndIndices;

	unsigned int sizeOfPositions;
	unsigned int sizeOfNormals;
	unsigned int sizeOfTexcoords;
	unsigned int sizeOfIndices;
//----------------------------------------------------------------------------//
};

#endif /* defined(__Application__GlModelData__) */
