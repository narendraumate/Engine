//
//  GlModel.cpp
//  Application
//
//  Created by Narendra Umate on 3/16/14.
//
//

#include "GlModel.h"

namespace Engine
{

	GlModel::GlModel(const GLuint& programId, const Mat4* viewMatrixPtr, const std::string& modelFilePath, const std::string& modelBasePath)
	:	m_programId(programId)
	,	m_position(0.0f, 0.0f, 0.0f)
	,	m_rotation(0.0f, 0.0f, 0.0f)
	,	m_scale(1.0f, 1.0f, 1.0f)
	,	m_modelMatrix()
	,	m_viewMatrixPtr(viewMatrixPtr)
	,	m_modelViewMatrix()
	,	m_normMatrix()
	,	m_modelFilePath(modelFilePath)
	,	m_modelBasePath(modelBasePath)
	,	m_textureManager(modelBasePath)
#ifdef SEPARATE_VBO
	,	m_glModelShapes()
#else
	,	m_glModelData(programId, &m_textureManager)
#endif // SEPARATE_VBO
	{
//----------------------------------------------------------------------------//
		std::vector<tinyobj::shape_c_t> shapes_c;
		std::string error = tinyobj::LoadModelCompact(shapes_c, modelFilePath.c_str(), modelBasePath.c_str(), false);

		if (error.empty())
		{
			glUseProgram(m_programId);

#ifdef SEPARATE_VBO
			for (std::vector<tinyobj::shape_c_t>::iterator it = shapes_c.begin(); it != shapes_c.end(); ++it)
			{
				m_glModelShapes.push_back(new GlModelShape(*it, m_programId, &m_textureManager));
			}
#else
			m_glModelData.initialize(shapes_c);
#endif // SEPARATE_VBO

			glUseProgram(0);
		}
		else
		{
			std::cerr << error;
		}
//----------------------------------------------------------------------------//
		updateModelMatrix();
	}

	GlModel::~GlModel()
	{
//----------------------------------------------------------------------------//
#ifdef SEPARATE_VBO
		for (std::vector<GlModelShape*>::iterator it = m_glModelShapes.begin(); it != m_glModelShapes.end(); ++it)
		{
			delete (*it);
		}
#else
		m_glModelData.deinitialize();
#endif // SEPARATE_VBO
//----------------------------------------------------------------------------//
	}

	void GlModel::draw()
	{
		// TODO Why is this needed for small models
#define ROTATE_MODEL
#if defined(ROTATE_MODEL)
		setRotation(Vec3(m_rotation.x, m_rotation.y + 0.5f, m_rotation.z));
#else
		setRotation(Vec3(m_rotation.x, m_rotation.y, m_rotation.z));
#endif // (ROTATE_MODEL)
//----------------------------------------------------------------------------//
		glUseProgram(m_programId);
#ifdef SEPARATE_VBO
		for (std::vector<GlModelShape*>::iterator it = m_glModelShapes.begin(); it != m_glModelShapes.end(); ++it)
		{
			(*it)->draw();
		}
#else
		m_glModelData.draw();
#endif // SEPARATE_VBO
		glUseProgram(0);
//----------------------------------------------------------------------------//
	}
	
	void GlModel::pushModelMatrix()
	{
		glUseProgram(m_programId);
		GLint modelMatrixLocation = glGetUniformLocation(m_programId, "model");
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, (float*)&m_modelMatrix);
		glUseProgram(0);
	}

	void GlModel::pushViewMatrix()
	{
		glUseProgram(m_programId);
		GLint viewMatrixLocation = glGetUniformLocation(m_programId, "view");
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, (float*)m_viewMatrixPtr);
		glUseProgram(0);
	}

	void GlModel::pushModelViewMatrix()
	{
		glUseProgram(m_programId);
		GLint modelViewMatrixLocation = glGetUniformLocation(m_programId, "modelView");
		glUniformMatrix4fv(modelViewMatrixLocation, 1, GL_FALSE, (float*)&m_modelViewMatrix);
		glUseProgram(0);
	}

	void GlModel::pushNormMatrix()
	{
		glUseProgram(m_programId);
		GLint normMatrixLocation = glGetUniformLocation(m_programId, "norm");
		glUniformMatrix3fv(normMatrixLocation, 1, GL_FALSE, (float*)&m_normMatrix);
		glUseProgram(0);
	}
		
	void GlModel::pushPerspectiveMatrix(const Mat4* perspectiveMatrix)
	{
		glUseProgram(m_programId);
		GLint perspectiveMatrixLocation = glGetUniformLocation(m_programId, "perspective");
		glUniformMatrix4fv(perspectiveMatrixLocation, 1, GL_FALSE, (float*)perspectiveMatrix);
		glUseProgram(0);
	}
	
	void GlModel::pushOrthographicMatrix(const Mat4* orthographicMatrix)
	{
		glUseProgram(m_programId);
		GLint orthographicMatrixLocation = glGetUniformLocation(m_programId, "orthographic");
		glUniformMatrix4fv(orthographicMatrixLocation, 1, GL_FALSE, (float*)orthographicMatrix);
		glUseProgram(0);
	}
	
	void GlModel::setPosition(const Vec3& position)
	{
		m_position = position;
		updateModelMatrix();
	}
	
	void GlModel::setRotation(const Vec3& rotation)
	{
		m_rotation = rotation;
		updateModelMatrix();
	}
	
	void GlModel::setScale(const Vec3& scale)
	{
		m_scale = scale;
		updateModelMatrix();
	}
	
	void GlModel::updateModelMatrix()
	{
		// TODO verify the multiplication order.
		m_modelMatrix = Mat4::identity();
		m_modelMatrix = m_modelMatrix * Mat4::rotateX(m_rotation.x) * Mat4::rotateY(m_rotation.y) * Mat4::rotateZ(m_rotation.z);
		m_modelMatrix = m_modelMatrix * Mat4::translate(m_position);
		m_modelMatrix = m_modelMatrix * Mat4::scale(m_scale);
		pushModelMatrix();

		updateModelViewMatrix();
	}

	void GlModel::updateViewMatrix()
	{
		pushViewMatrix();

		updateModelViewMatrix();
	}

	void GlModel::updateModelViewMatrix()
	{
		m_modelViewMatrix = (*m_viewMatrixPtr) * m_modelMatrix;
		pushModelViewMatrix();

		updateNormMatrix();
	}

	void GlModel::updateNormMatrix()
	{
		// TODO Verify this
		// Normal Matrix is supposedly Top Left 3x3 of ModelView Matrix
		m_normMatrix.d00 = m_modelViewMatrix.d00;
		m_normMatrix.d01 = m_modelViewMatrix.d01;
		m_normMatrix.d02 = m_modelViewMatrix.d02;
		m_normMatrix.d10 = m_modelViewMatrix.d10;
		m_normMatrix.d11 = m_modelViewMatrix.d11;
		m_normMatrix.d12 = m_modelViewMatrix.d12;
		m_normMatrix.d20 = m_modelViewMatrix.d20;
		m_normMatrix.d21 = m_modelViewMatrix.d21;
		m_normMatrix.d22 = m_modelViewMatrix.d22;

		pushNormMatrix();
	}

}
