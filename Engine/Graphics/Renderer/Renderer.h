//
//  Renderer.h
//  Application
//
//  Created by Narendra Umate on 9/7/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#ifndef __Application__Renderer__
#define __Application__Renderer__

#include <iostream>
#include <string.h>

#include "../../Graphics/SceneGraph/Camera.h"
#include "../../Core/Color.h"
#include "../../Mathematics/Matrix.h"

#if defined(__APPLE__)
#include <OpenGL/OpenGL.h>
#define ContextObj CGLContextObj
#elif defined(__linux__)
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h> // sudo apt-get install mesa-common-dev mesa-utils freeglut3 freeglut3-dev
#include <GL/glx.h>
#define ContextObj GLXContext
#elif defined(_WIN32)
#define ContextObj WGLContextObj
#endif //defined(_WIN32)

namespace Engine
{

	class Renderer
	{

	public:

		Renderer(const int& width, const int& height);
		virtual ~Renderer() = 0;

		void setContextObj(const ContextObj& contextObj);
		ContextObj getContextObj();

		int getWidth() const;
		int getHeight() const;
		const char* getApplicationName() const;

		void setCamera(Camera* camera);
		const Camera* getCamera() const;

		const Mat4* getViewMatrix() const;
		const Mat4* getPerspectiveProjectionMatrix() const;
		const Mat4* getOrthographicProjectionMatrix() const;

		void setClearColor(const Color4f& clearColor);
		Color4f getClearColor() const;
		void setClearDepth(const float& clearDepth);
		float getClearDepth() const;
		void setClearStencil(unsigned int& clearStencil);
		unsigned int getClearStencil() const;

		virtual bool initialize() = 0;
		virtual void run() = 0;
		virtual void shutdown() = 0;

		// Support for viewport, depth range, resize.
		virtual void setViewport(const int& xPos, const int& yPos, const int& w, const int& h) = 0;
		virtual void getViewport(int& xPos, int& yPos, int& w, int& h) const = 0;
		virtual void setDepthRange(const float& zMin, const float& zMax) = 0;
		virtual void getDepthRange(float& zMin, float& zMax) const = 0;
		virtual void resize(const int& width, const int& height) = 0;

		// Support for clearing the color, depth, and stencil buffers.
		virtual void clearColorBuffer() = 0;
		virtual void clearDepthBuffer() = 0;
		virtual void clearStencilBuffer() = 0;
		virtual void clearBuffers() = 0;
		virtual void clearColorBuffer(const int& x, const int& y, const int& w, const int& h) = 0;
		virtual void clearDepthBuffer(const int& x, const int& y, const int& w, const int& h) = 0;
		virtual void clearStencilBuffer(const int& x, const int& y, const int& w, const int& h) = 0;
		virtual void clearBuffers(const int& x, const int& y, const int& w, const int& h) = 0;
		virtual void displayColorBuffer() = 0;

		virtual bool preDraw() = 0;
		virtual void postDraw() = 0;

	protected:

		ContextObj m_contextObj;
		int m_width;
		int m_height;

		Camera m_camera;

		Color4f m_clearColor;
		float m_clearDepth;
		unsigned int m_clearStencil;

	};
	
}

#endif /* defined(__Application__Renderer__) */
