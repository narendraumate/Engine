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
#include "../Renderer.h"
#include "../Common/TextureManager.h"
#include "../../../Mathematics/Vector.h"
#include "../../../External/stbi/StbImage.h"
#include "../../../External/tinymodelloader/tiny_model_loader_compact.h"
#include "../../../Application/Common/Logger.h"

namespace Engine
{
class GlModelData
{
public:
	GlModelData(const GLuint& programId, TextureManager* textureManager);
	~GlModelData();

	void initialize(const vector<tinyobj::shape_c_t>& shapes_c);
	void deinitialize();

	void draw();

private:
	GLuint m_programId;
	TextureManager* m_textureManager;

	enum Ebo { EboTriangles, EboCount };
	enum Vao { VaoTriangles, VaoCount };
	enum Vbo { VboTriangles, VboCount };
	enum Tbo { TboTriangles, TboCount };

	enum AttributeType { AttributePosition, AttributeNormal, AttributeTexcoord, AttributeTangent, AttributeBitangent, AttributeCount };
	enum TextureType { TextureAmbient, TextureDiffuse, TextureSpecular, TextureNormal, TextureCount };

	GLuint m_ebos[EboCount];
	GLuint m_vaos[VaoCount];
	GLuint m_vbos[VboCount];

	void pushMaterial(const tinyobj::material_t& material);
	void pushTextureSamplers();
	void pushMaterialParameters(const tinyobj::material_t& material);
	GLuint loadTexture(const GLenum& textureIndex, const std::string& textureName, const TextureType& textureType);
//----------------------------------------------------------------------------//
	unsigned int m_indexBatchSize;
	vector<unsigned int> shapeIndexStart;
	vector<unsigned int> shapeIndexCount;

	struct GlTextureCollection
	{
		GLuint m_textures[TextureCount];
	};
	vector<GlTextureCollection> textureCollections;

	vector<tinyobj::material_t> materials;
//----------------------------------------------------------------------------//
};
}
#endif /* defined(__Application__GlModelData__) */
