//
//  GlModelShape.h
//  Application
//
//  Created by Narendra Umate on 3/21/14.
//
//

#ifndef __Application__GlModelShape__
#define __Application__GlModelShape__

#include <iostream>
#include "GlProgram.h"
#include "GlShader.h"
#include "../Common/TextureManager.h"
#include "../../../../Application/Common/Logger.h"
#include "../../../External/stbi/StbImage.h"
#include "../../../External/tinymodelloader/tiny_model_loader_compact.h"

namespace Engine
{

	class GlModelShape
	{
	public:
		GlModelShape(const tinyobj::shape_c_t& shape, const GLuint& programId, TextureManager* textureManager);
		~GlModelShape();

		void draw();

	private:
		GLuint m_programId;
		TextureManager* m_textureManager;

		enum Ebo { EboTriangles, EboCount };
		enum Vao { VaoTriangles, VaoCount };
		enum Vbo { VboTriangles, VboCount };
		
		enum AttributeType { AttributePosition, AttributeNormal, AttributeTexcoord, AttributeTangent, AttributeBitangent, AttributeCount };
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
	};

}
#endif /* defined(__Application__GlModelShape__) */
