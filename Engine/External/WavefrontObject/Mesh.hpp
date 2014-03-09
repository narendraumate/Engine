
// ===============================================================================================================
// -*- C++ -*-
//
// Mesh.hpp - Mesh base class.
//
// Copyright (c) 2010 Guilherme R. Lampert
// guilherme.ronaldo.lampert@gmail.com
//
// This code is licenced under the MIT license.
//
// This software is provided "as is" without express or implied
// warranties. You may freely copy and compile this source into
// applications you distribute provided that the copyright text
// above is included in the resulting source code.
//
// ===============================================================================================================

#ifndef __MESH_HPP__
#define __MESH_HPP__

// == External Modules ======

#include "Vector.hpp"
#include "Utility.hpp"
#include "Texture.hpp"

#include <vector>
using std::vector;

#include <map>
using std::map;

// =============================
// Polygon Mesh Class (Abstract)
// =============================

class Mesh {

public:

	// Forward declaration of some classes defined latter on.
	class Face;
	class Group;
	class Material;

	// Nested types:
	typedef std::map<std::string, Group *> GroupMap;
	typedef std::map<std::string, Material *> MaterialMap;

public:

	Mesh(void);

	// Load a mesh from a file.
	virtual void LoadFromFile(const std::string & filename) = 0;

	// Write the mesh back to a file.
	virtual bool WriteToFile(const std::string & filename) = 0;

	// Render a mesh group.
	virtual void Render(const GroupMap::const_iterator & GroupIndex) const;

	// Render all the mesh groups.
	virtual void Render(void) const;

	// Free memory. (Optional, called by the destructor).
	virtual void Release(void);

	virtual ~Mesh(void);

public:

	// ================
	// Mesh Render Mode
	// ================

	enum RenderMode {

		Solid,
		Points,
		Wireframe
	};

	// Get/Set methods:

	void SetScale(float s);
	void SetRenderMode(const RenderMode m);

	const GroupMap & Groups(void) const;
	const MaterialMap & Materials(void) const;

	const Vec3 * Normals(void) const;
	const Vec3 * Vertices(void) const;
	const Vec2 * TexCoords(void) const;

	unsigned int NormalCount(void) const;
	unsigned int VertexCount(void) const;
	unsigned int TexCoordCount(void) const;

	// Generate an OpenGL display list for better rendering performance.
	// Only useful if rendering all groups with a single Render() call.
	void CreateDisplayList(void) const;

public:

	// ===============
	// Mesh Face Class
	// ===============

	class Face {

	public:

		Face(void);
		~Face(void);
		Face(unsigned short v, unsigned short n, unsigned short t);

		unsigned short nVertexCount;
		unsigned short nNormalCount;
		unsigned short nTexCoordCount;

		unsigned int * pVertexIndex;
		unsigned int * pNormalIndex;
		unsigned int * pTexCoordIndex;
	};

	// =====================
	// Mesh Face Group Class
	// =====================

	class Group {

	public:

		inline Group(void)
			: vFaces()
			{
			}

		inline ~Group(void)
			{
			unsigned int i = vFaces.size();
			while (i--)
				delete vFaces[i];
			}

		std::vector<const Face *> vFaces;
		std::string MaterialName;
	};

	// ===================
	// Mesh Material Class
	// ===================

	class Material {

	public:

		Material(void);
		Material(const Vec3 & ambient, const Vec3 & diffuse,
		         const Vec3 & specular, int shininess, Texture2D * pTex, int flags);

		void Enable(bool withTexture = true) const;
		void Disable(void) const;

		~Material(void);

	public:

		static const int TexMap = (1 << 1);
		static const int Color  = (1 << 2);

		Vec3 Ambient;
		Vec3 Diffuse;
		Vec3 Specular;
		int Shininess;

		int m_flags;
		Texture2D * m_pTexture;
	};

private:

	// Disable copy and assignment.
	Mesh(const Mesh &) { }
	Mesh & operator = (const Mesh &) { return (*this); }

protected:

	// Mesh Data:

	float m_ScaleFactor;
	RenderMode m_RenderMode;

	GroupMap m_FaceGroups;
	MaterialMap m_Materials;

	unsigned int m_VertexCount;
	unsigned int m_NormalCount;
	unsigned int m_TexCoordCount;

	Vec3 * m_pVertices;
	Vec3 * m_pNormals;
	Vec2 * m_pTexCoords;

	// Helper GL compatibility stuff:

	mutable GLuint m_DisplayList;
	virtual GLenum SelectGLRenderMode(const Face * pFace) const;
};

#endif // __MESH_HPP__
