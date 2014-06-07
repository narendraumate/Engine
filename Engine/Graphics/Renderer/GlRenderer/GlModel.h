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
#include "GlModelData.h"
#include "GlModelShape.h"
#include "../Common/TextureManager.h"
#include "../../../Mathematics/Matrix.h"
#include "../../../External/tinymodelloader/tiny_model_loader_compact.h"

namespace Engine
{
	class GlModel
	{
	public:
		GlModel(const GLuint& programId, const Mat4* viewMatrixPtr, const std::string& objFilePath, const std::string& mtlBasePath);
		~GlModel();

		void draw();

		void updateViewMatrix();

		void pushPerspectiveMatrix(const Mat4* perspectiveMatrix);
		void pushOrthographicMatrix(const Mat4* orthographicMatrix);

		void setPosition(const Vec3& position);
		void setRotation(const Vec3& rotation);
		void setScale(const Vec3& scale);

	private:
		void updateModelMatrix();
		void updateModelViewMatrix();
		void updateNormMatrix();

		void pushModelMatrix();
		void pushViewMatrix();
		void pushModelViewMatrix();
		void pushNormMatrix();

		GLuint m_programId;

		Vec3 m_position;
		Vec3 m_rotation;
		Vec3 m_scale;

		Mat4 m_modelMatrix;
		const Mat4* m_viewMatrixPtr;
		Mat4 m_modelViewMatrix;
		Mat3 m_normMatrix;

		std::string m_objFilePath;
		std::string m_mtlBasePath;

		TextureManager m_textureManager;
//----------------------------------------------------------------------------//
//#define SEPARATE_VBO
#ifdef SEPARATE_VBO
		vector<GlModelShape*> m_glModelShapes;
#else
		GlModelData m_glModelData;
#endif // SEPARATE_VBO
//----------------------------------------------------------------------------//
	};
}
#endif /* defined(__Application__GlModel__) */
