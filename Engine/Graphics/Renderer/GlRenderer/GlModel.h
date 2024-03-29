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
#include "../../SceneGraph/Camera.h"
#include "../../../Mathematics/Matrix.h"
#include "../../../External/tiny_model_loader_compact/tiny_model_loader_compact.h"

namespace Engine
{
	class GlModel
	{
	public:
		GlModel(const GLuint& programId, const Camera* cameraPtr, const std::string& modelFilePath, const std::string& modelBasePath);
		~GlModel();

		void draw();

		void updateViewMatrix();

		void pushPerspectiveMatrix();
		void pushModelViewPerspectiveMatrix();
		void pushOrthographicMatrix();
		void pushModelViewOrthographicMatrix();

		void setPosition(const Vec3& position);
		void setRotation(const Vec3& rotation);
		void setScale(const Vec3& scale);

	private:
		void updateModelMatrix();
		void updateModelViewMatrix();
		void updateNormMatrix();
		void updateModelViewPerspectiveMatrix();
		void updateModelViewOrthographicMatrix();

		void pushModelMatrix();
		void pushViewMatrix();
		void pushModelViewMatrix();
		void pushNormMatrix();

		GLuint m_programId;

		Vec3 m_position;
		Vec3 m_rotation;
		Vec3 m_scale;

		const Camera* m_cameraPtr;
		Mat4 m_modelMatrix;
		Mat4 m_modelViewMatrix;
		Mat3 m_normMatrix;

		std::string m_modelFilePath;
		std::string m_modelBasePath;

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
