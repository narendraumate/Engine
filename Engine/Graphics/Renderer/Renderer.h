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

#include "../../Mathematics/Camera.h"
#include "../../Mathematics/Color.h"
#include "../../Mathematics/Matrix.h"

#if defined(__APPLE__)
#include <OpenGL/OpenGL.h>
#define ContextObj CGLContextObj
#elif defined(__linux__)
#include <GL/gl.h>
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

		Renderer(const int& width, const int& height, const char* applicationName);
		virtual ~Renderer() = 0;

		virtual bool initialize() = 0;
		virtual void run() = 0;
		virtual void shutdown() = 0;

		virtual void setContextObj(const ContextObj& contextObj) = 0;
		virtual ContextObj getContextObj() = 0;

		int getWidth() const;
		int getHeight() const;
		char* getApplicationName() const;

		void setCamera(Camera* camera);
		Camera* getCamera() const;

		Mat4* getViewMatrix() const;
		Mat4* getProjectionMatrix() const;
		Mat4* getPostProjectionMatrix() const;

		inline void setClearColor(const Color4f& clearColor);
		inline Color4f getClearColor() const;
		inline void setClearDepth(const float& clearDepth);
		inline float getClearDepth() const;
		inline void setClearStencil(unsigned int& clearStencil);
		inline unsigned int getClearStencil() const;

		// viewport, depth range, resize.
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

		// Support for predraw and postdraw semantics.  All Renderer abstract
		// interface functions and drawing functions must occur within a block of
		// code bounded by PreDraw() and PostDraw().  The general format is
		//   if (renderer->PreDraw())
		//   {
		//       <abstract-interface renderer calls and draw calls>;
		//       renderer->PostDraw();
		//   }
		virtual bool preDraw() = 0;
		virtual void postDraw() = 0;

		// The entry point for drawing 2D buffers (for 2D applications).
		virtual void draw(const unsigned char* screenBuffer, const bool& reflectY = false) = 0;

		// The entry point for drawing 2D text.
		virtual void draw(const int& x, const int& y, const Color4f& color, const std::string& message) = 0;

	protected:

		ContextObj m_contextObj;
		int m_width;
		int m_height;
		char* m_applicationName;

		Camera* m_camera;

		Mat4* m_viewMatrix;
		Mat4* m_projectionMatrix;
		Mat4* m_postProjectionMatrix;

		Color4f m_clearColor;
		float m_clearDepth;
		unsigned int m_clearStencil;

	private:

		// The entry point for drawing 3D objects, called by the single-object
		// Draw function.
		virtual void drawPrimitive() = 0;
		
	};
	
}

#endif /* defined(__Application__Renderer__) */
