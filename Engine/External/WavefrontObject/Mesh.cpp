
// ===============================================================================================================
// -*- C++ -*-
//
// Mesh.cpp - Mesh base class.
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

#include "Mesh.hpp"

// == Class Mesh (Abstract) ==

Mesh::Mesh(void) : m_VertexCount(0), m_NormalCount(0), m_TexCoordCount(0),
	m_pVertices(0), m_pNormals(0), m_pTexCoords(0), m_FaceGroups(), m_Materials(),
	m_RenderMode(Solid), m_ScaleFactor(1.0f), m_DisplayList((GLuint)-1)
{
}

void Mesh::Render(const Mesh::GroupMap::const_iterator & GroupIndex) const
{
	glScalef(m_ScaleFactor, m_ScaleFactor, m_ScaleFactor);

	Mesh::MaterialMap::const_iterator GroupMaterial = m_Materials.find((*GroupIndex).second->MaterialName);
	Mesh::MaterialMap::const_iterator NoMaterial = m_Materials.end();

	if (GroupMaterial != NoMaterial)
		(*GroupMaterial).second->Enable(m_RenderMode == Solid);

	unsigned int nFace = (*GroupIndex).second->vFaces.size();

	while (nFace--)
	{
		const Mesh::Face * pFace = (*GroupIndex).second->vFaces[nFace];

		glBegin(SelectGLRenderMode(pFace));

		for (int i = 0; i < pFace->nVertexCount; ++i)
		{
			if (pFace->pNormalIndex)
			{
				glNormal3fv(m_pNormals[pFace->pNormalIndex[i]].v);
			}

			if (pFace->pTexCoordIndex)
			{
				glTexCoord2fv(m_pTexCoords[pFace->pTexCoordIndex[i]].v);
			}

			glVertex3fv(m_pVertices[pFace->pVertexIndex[i]].v);
		}

		glEnd();
	}

	if (GroupMaterial != NoMaterial)
		(*GroupMaterial).second->Disable();
}

void Mesh::Render(void) const
{
	glScalef(m_ScaleFactor, m_ScaleFactor, m_ScaleFactor);

	if (m_DisplayList != (GLuint)-1)
	{
		// Use display list
		glCallList(m_DisplayList);
	}
	else
	{
		Mesh::GroupMap::const_iterator GroupIndex = m_FaceGroups.begin();
		Mesh::GroupMap::const_iterator GroupEnd = m_FaceGroups.end();

		while (GroupIndex != GroupEnd)
		{
			Mesh::MaterialMap::const_iterator GroupMaterial = m_Materials.find((*GroupIndex).second->MaterialName);
			Mesh::MaterialMap::const_iterator NoMaterial = m_Materials.end();

			if (GroupMaterial != NoMaterial)
				(*GroupMaterial).second->Enable(m_RenderMode == Solid);

			unsigned int nFace = (*GroupIndex).second->vFaces.size();

			while (nFace--)
			{
				const Mesh::Face * pFace = (*GroupIndex).second->vFaces[nFace];

				glBegin(SelectGLRenderMode(pFace));

				for (int i = 0; i < pFace->nVertexCount; ++i)
				{
					if (pFace->pNormalIndex)
					{
						glNormal3fv(m_pNormals[pFace->pNormalIndex[i]].v);
					}

					if (pFace->pTexCoordIndex)
					{
						glTexCoord2fv(m_pTexCoords[pFace->pTexCoordIndex[i]].v);
					}

					glVertex3fv(m_pVertices[pFace->pVertexIndex[i]].v);
				}

				glEnd();
			}

			if (GroupMaterial != NoMaterial)
				(*GroupMaterial).second->Disable();

			++GroupIndex;
		}
	}
}

void Mesh::Release(void)
{
	Mesh::GroupMap::const_iterator GroupIndex = m_FaceGroups.begin();
	Mesh::GroupMap::const_iterator GroupEnd = m_FaceGroups.end();

	while (GroupIndex != GroupEnd)
	{
		delete (GroupIndex->second);
		++GroupIndex;
	}

	m_FaceGroups.clear();

	Mesh::MaterialMap::const_iterator MatIndex = m_Materials.begin();
	Mesh::MaterialMap::const_iterator MatEnd = m_Materials.end();

	while (MatIndex != MatEnd)
	{
		delete (MatIndex->second);
		++MatIndex;
	}

	m_Materials.clear();

	delete[] m_pVertices;
	m_pVertices = 0;

	delete[] m_pNormals;
	m_pNormals = 0;

	delete[] m_pTexCoords;
	m_pTexCoords = 0;

	if (m_DisplayList != (GLuint)-1)
	{
		glDeleteLists(m_DisplayList, 1);
	}
}

GLenum Mesh::SelectGLRenderMode(const Mesh::Face * pFace) const
{
	switch (m_RenderMode)
	{
	case Solid:
		return ((pFace->nVertexCount == 4) ? GL_QUADS : GL_TRIANGLES);

	case Points:
		return (GL_POINTS);

	case Wireframe:
		return (GL_LINE_STRIP);

	default: // Dummy statement, it never gets here anyway ...
		assert(false);
		return (GL_POLYGON);

	} // End switch (m_RenderMode)
}

void Mesh::CreateDisplayList(void) const
{
	if (m_DisplayList != (GLuint)-1)
	{
		// Free old list, if any
		glDeleteLists(m_DisplayList, 1);
		m_DisplayList = (GLuint)-1;
	}

	GLuint newList = glGenLists(1);
	glNewList(newList, GL_COMPILE);
	this->Render();
	glEndList();

	m_DisplayList = newList;
}

Mesh::~Mesh(void)
{
	Release();
}

void Mesh::SetScale(float s)
{
	m_ScaleFactor = s;
}

void Mesh::SetRenderMode(const Mesh::RenderMode m)
{
	m_RenderMode = m;
}

const Mesh::GroupMap & Mesh::Groups(void) const
{
	return (m_FaceGroups);
}

const Mesh::MaterialMap & Mesh::Materials(void) const
{
	return (m_Materials);
}

const Vec3 * Mesh::Normals(void) const
{
	return (m_pNormals);
}

const Vec3 * Mesh::Vertices(void) const
{
	return (m_pVertices);
}

const Vec2 * Mesh::TexCoords(void) const
{
	return (m_pTexCoords);
}

unsigned int Mesh::NormalCount(void) const
{
	return (m_NormalCount);
}

unsigned int Mesh::VertexCount(void) const
{
	return (m_VertexCount);
}

unsigned int Mesh::TexCoordCount(void) const
{
	return (m_TexCoordCount);
}

// == Class Mesh::Face ==

Mesh::Face::Face(void)
	: nVertexCount(0), nNormalCount(0), nTexCoordCount(0),
	pVertexIndex(0), pNormalIndex(0), pTexCoordIndex(0)
{
}

Mesh::Face::Face(unsigned short v, unsigned short n, unsigned short t)
	: nVertexCount(v), nNormalCount(n), nTexCoordCount(t),
	pVertexIndex(0), pNormalIndex(0), pTexCoordIndex(0)
{
	if (nVertexCount > 0)
		pVertexIndex = new unsigned int [nVertexCount];

	if (nNormalCount > 0)
		pNormalIndex = new unsigned int [nNormalCount];

	if (nTexCoordCount > 0)
		pTexCoordIndex = new unsigned int [nTexCoordCount];
}

Mesh::Face::~Face(void)
{
	if (pVertexIndex)
		delete[] pVertexIndex;

	if (pNormalIndex)
		delete[] pNormalIndex;

	if (pTexCoordIndex)
		delete[] pTexCoordIndex;
}

// == Class Mesh::Material ==

Mesh::Material::Material(void)
	: Ambient(), Diffuse(), Specular(), Shininess(0), m_pTexture(0), m_flags(0)
{
}

Mesh::Material::Material(const Vec3 & ambient, const Vec3 & diffuse,
	const Vec3 & specular, int shininess, Texture2D * pTex, int flags)
	: Ambient(ambient), Diffuse(diffuse), Specular(specular),
	Shininess(shininess), m_pTexture(pTex), m_flags(flags)
{
}

void Mesh::Material::Enable(bool withTexture) const
{
	if (m_flags & Color)
	{
		glEnable(GL_COLOR_MATERIAL);
		glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient.v);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse.v);
		glLightfv(GL_LIGHT0, GL_SPECULAR, Specular.v);
		glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, Shininess);
	}

	if ((m_flags & TexMap) && withTexture)
	{
		glEnable(GL_TEXTURE_2D);
		m_pTexture->Bind();
	}
}

void Mesh::Material::Disable(void) const
{
	if (m_flags & Color)
	{
		glDisable(GL_COLOR_MATERIAL);
	}

	if (m_flags & TexMap)
	{
		glDisable(GL_TEXTURE_2D);
	}
}

Mesh::Material::~Material(void) { }
