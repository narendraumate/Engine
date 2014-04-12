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
#include "../../../../Application/Common/Logger.h"
#include "../../../External/stbi/StbImage.h"
#include "../../../External/tinyobjloader/tiny_obj_loader_compact.h"

namespace Engine
{

	class GlModelShape
	{
	public:
		GlModelShape(const tinyobj::shape_t& shape, const GLuint& programId);
		~GlModelShape();

		void draw();
		/*void pushTextureBuffers()
		{
			//glUseProgram(m_programId);
			//GLint diffuseTextureBufferLocation = glGetUniformLocation(m_programId, "diffuseTextureBuffer");
			//glUniform1i(diffuseTextureBufferLocation, m_textureBuffers[TextureBufferDiffuse]);
			//glUseProgram(0);
		}*/

	private:
		GLuint m_programId;

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
		GLuint m_tbos[TboCount];

		GLuint m_textures[TextureCount];
		GLuint m_textureSamplers[TextureCount];

		GLuint m_indexCount;

		void pushMaterialParameters(const tinyobj::material_t& material);
	};

}
#endif /* defined(__Application__GlModelShape__) */
