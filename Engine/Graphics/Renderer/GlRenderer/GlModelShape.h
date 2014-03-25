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
#include "../../../External/stbi/StbImage.h"
#include "../../../External/tinyobjloader/tiny_obj_loader.h"

namespace Engine
{

	class GlModelShape
	{
	public:
		GlModelShape(const tinyobj::shape_t& shape);
		~GlModelShape();

		void draw();

	private:
		enum Ebo { EboTriangles, EboCount };
		enum Vao { VaoTriangles, VaoCount };
		enum Vbo { VboTriangles, VboCount };
		enum Tbo { TboTriangles, TboCount };
		
		enum Attribute { AttributePosition, AttributeNormal, AttributeTexCoord, AttributeCount };
		enum Texture { TextureDiffuse, TextureCount };
		enum TextureSampler { TextureSamplerDiffuse, TextureSamplerCount };

		GLuint m_ebos[EboCount];
		GLuint m_vaos[VaoCount];
		GLuint m_vbos[VboCount];


		GLuint m_textures[TextureCount];
		GLuint m_textureSamplers[TextureCount];

		GLuint m_indexCount;
	};

}
#endif /* defined(__Application__GlModelShape__) */
