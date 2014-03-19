//
//  GlModel.h
//  Application
//
//  Created by Narendra Umate on 3/16/14.
//
//

#ifndef __Application__GlModel__
#define __Application__GlModel__

#include <string>
#include "GlProgram.h"
#include "GlShader.h"
#include "../../../Mathematics/Matrix.h"
#include "../../../External/objloader/objloader.hpp"
#include "../../../External/tinyobjloader/tiny_obj_loader.h"

namespace Engine
{
	class GlModel
	{
	public:
		GlModel(GLuint programId, std::string objFilename);
		~GlModel();
		
		void setViewMatrix(const Mat4* viewMatrix);
		void setModelMatrix(const Mat4* modelMatrix);
		void setPerspectiveMatrix(const Mat4* perspectiveMatrix);
		void setOrthographicMatrix(const Mat4* orthographicMatrix);
		void setPosition(const Vec3& position);
		void setRotation(const Vec3& rotation);
		void setScale(const Vec3& scale);
		void updateModelMatrix();
		
		void draw();
		
	private:
		GLuint m_programId;
		
		Vec3 m_position;
		Vec3 m_rotation;
		Vec3 m_scale;
		
		Mat4 m_modelMatrix;		
//----------------------------------------------------------------------------//
		enum Vao { VaoTriangles, VaoCount };
		enum Vbo { VboPosition, VboNormal, VboTexCoord, VboCount };
		enum Attribute { AttributePosition, AttributeNormal, AttributeTexCoord, AttributeCount };
		
		GLuint m_vaos[VaoCount];
		GLuint m_vbos[VboCount];
		
		GLuint m_vertexCount;
#define BUFFER_OFFSET(offset) ((void *)(offset))
//----------------------------------------------------------------------------//
	};
}
#endif /* defined(__Application__GlModel__) */
