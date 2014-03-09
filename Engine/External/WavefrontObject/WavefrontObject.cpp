
// ===============================================================================================================
// -*- C++ -*-
//
// WavefrontObject.cpp - Wavefront OBJ mesh loader. (Implements the 'Mesh' interface).
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

#include "WavefrontObject.hpp"

// == Class WavefrontObject ==

WavefrontObject::WavefrontObject(void) : Mesh()
{
}

WavefrontObject::WavefrontObject(const std::string & filename) : Mesh()
{
	LoadFromFile(filename);
}

void WavefrontObject::LoadFromFile(const std::string & filename)
{
	FILE * fp;
	char buffer[512];
	char bufferAux[512];
	MemoryBuffer objDataBuf; // Memory buffer to hold the file data.

	Group * pGroup = NULL;
	float x, y, z, u, v;

	if ((fp = fopen(filename.c_str(), "rt")) == NULL)
	{
		std::string msg("Unable To Find Or Open The File: "); msg.append(filename);
		throw std::runtime_error(msg);
	}

	// Here I load the entire .obj file into memory to speed up
	// the process of counting all the objects and reading the model data.

	fseek(fp, 0, SEEK_END);
	const long fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	objDataBuf.Allocate(fileSize);

	fread(objDataBuf.GetBufferPointer(), 1, fileSize, fp);
	fclose(fp); // File will no longer be used, so close it.

	// Count all vertices, tex coords and normals, to allocate exact memory:

	while (objDataBuf.ReadLine(buffer, sizeof(buffer)))
	{
		switch (buffer[0])
		{
		case 'v':
			{
				switch (buffer[1])
				{
				case ' ':
					m_VertexCount++;
					break;

				case 't':
					m_TexCoordCount++;
					break;

				case 'n':
					m_NormalCount++;
					break;

				default:
					break;
				} // End switch (buffer[1])
			}
			break;

		default:
			break;
		} // End switch (buffer[0])
	}

	// Allocate memory:

	try {

		if (m_VertexCount > 0)
			m_pVertices = new Vec3 [m_VertexCount];

		if (m_NormalCount > 0)
			m_pNormals = new Vec3 [m_NormalCount];

		if (m_TexCoordCount > 0)
			m_pTexCoords = new Vec2 [m_TexCoordCount];
	}
	catch (std::bad_alloc) {

		Mesh::Release();
		objDataBuf.Free();

		std::string msg("Memory Allocation Failure When Trying To Load The File: "); msg.append(filename);
		throw std::runtime_error(msg);
	}

	// Now read in the data:

	objDataBuf.Seek(0, SEEK_SET);

	unsigned int nVert = 0, nNorm = 0, nTex = 0;

	// Read thru the file, line-by-line...
	while (objDataBuf.ReadLine(buffer, sizeof(buffer)))
	{
		switch (buffer[0])
		{
		case 'v':
			{
				// Vertex position
				if (sscanf(buffer, "v %f %f %f", &x, &y, &z) == 3)
				{
					m_pVertices[nVert].x = x;
					m_pVertices[nVert].y = y;
					m_pVertices[nVert].z = z;
					nVert++;
				}
				// Texture coordinate
				else if (sscanf(buffer, "vt %f %f", &u, &v) == 2)
				{
					m_pTexCoords[nTex].x = u;
					m_pTexCoords[nTex].y = v;
					nTex++;
				}
				// Normal vector
				else if (sscanf(buffer, "vn %f %f %f", &x, &y, &z) == 3)
				{
					m_pNormals[nNorm].x = x;
					m_pNormals[nNorm].y = y;
					m_pNormals[nNorm].z = z;
					nNorm++;
				}
			}
			break;

		case 'g':
			{
				// OBJ mesh group
				if (sscanf(buffer, "g %s", bufferAux) > 0)
				{
					Mesh::GroupMap::const_iterator _Ptr = m_FaceGroups.find(bufferAux);

					if (_Ptr == m_FaceGroups.end())
					{
						pGroup = new Group;
						m_FaceGroups.insert(Mesh::GroupMap::value_type(bufferAux, pGroup));
					}
					else
					{
						pGroup = (*_Ptr).second;
					}
				}
			}
			break;

		case 'f':
			{
				// Group face
				int i = 0, cnt = 0;
				do {

					i++;
					if (buffer[i] == ' ')
						cnt++;

				} while ((buffer[i] != '\0') && (buffer[i] != '\n'));

				if (cnt == 3)
				{
					if (!pGroup)
					{
						pGroup = new Group;
						m_FaceGroups.insert(Mesh::GroupMap::value_type("default", pGroup));
					}

					pGroup->vFaces.push_back(ReadObjTriFace(buffer));
				}
				else if (cnt == 4)
				{
					if (!pGroup)
					{
						pGroup = new Group;
						m_FaceGroups.insert(Mesh::GroupMap::value_type("default", pGroup));
					}

					pGroup->vFaces.push_back(ReadObjQuadFace(buffer));
				}
				else
				{
					LOG_ERROR("Unhandled Polygon Type Found. This OBJ Loader Only Support Polygons Made Of Quads Or Triangles.");
				}
			}
			break;

		default:
			{
				// Material library
				if (sscanf(buffer, "usemtl %s", bufferAux) > 0)
				{
					if (pGroup != NULL)
					{
						pGroup->MaterialName = bufferAux;
					}
				}
				else if (sscanf(buffer, "mtllib %s", bufferAux) > 0)
				{
					std::string mtlPath(GetFilePath(filename));
					mtlPath.append(bufferAux);

					// Read the .mtl file:
					if (!ReadMaterialLibrary(mtlPath))
					{
						LOG_ERROR("Failed To Read The Object Material Library. Object .mtl File : " << bufferAux);
					}
				}
			}
			break;

		} // End switch (buffer[0])
	}

	objDataBuf.Free();
}

Mesh::Face * WavefrontObject::ReadObjTriFace(const char * buffer) const
{
	Face * pFace = NULL;
	unsigned int v1, t1, n1, v2, t2, n2, v3, t3, n3;

	if (sscanf(buffer, "f %u/%u/%u %u/%u/%u %u/%u/%u", &v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3) == 9)
	{
		pFace = new Face(3, 3, 3); // Triagle Face. Vertex + Texture + Normal.

		pFace->pVertexIndex[0] = --v1;   pFace->pVertexIndex[1] = --v2;   pFace->pVertexIndex[2] = --v3;
		pFace->pNormalIndex[0] = --n1;   pFace->pNormalIndex[1] = --n2;   pFace->pNormalIndex[2] = --n3;
		pFace->pTexCoordIndex[0] = --t1; pFace->pTexCoordIndex[1] = --t2; pFace->pTexCoordIndex[2] = --t3;
	}
	else if (sscanf(buffer, "f %u/%u %u/%u %u/%u", &v1, &t1, &v2, &t2, &v3, &t3) == 6)
	{
		pFace = new Face(3, 0, 3); // Triagle Face. Vertex + Texture.

		pFace->pVertexIndex[0] = --v1;   pFace->pVertexIndex[1] = --v2;   pFace->pVertexIndex[2] = --v3;
		pFace->pTexCoordIndex[0] = --t1; pFace->pTexCoordIndex[1] = --t2; pFace->pTexCoordIndex[2] = --t3;
	}
	else if (sscanf(buffer, "f %u//%u %u//%u %u//%u", &v1, &n1, &v2, &n2, &v3, &n3) == 6)
	{
		pFace = new Face(3, 3, 0); // Triagle Face. Vertex + Normal.

		pFace->pVertexIndex[0] = --v1; pFace->pVertexIndex[1] = --v2; pFace->pVertexIndex[2] = --v3;
		pFace->pNormalIndex[0] = --n1; pFace->pNormalIndex[1] = --n2; pFace->pNormalIndex[2] = --n3;
	}
	else if (sscanf(buffer, "f %u %u %u", &v1, &v2, &v3) == 3)
	{
		pFace = new Face(3, 0, 0); // Triagle Face. Vertex Only.

		pFace->pVertexIndex[0] = --v1; pFace->pVertexIndex[1] = --v2; pFace->pVertexIndex[2] = --v3;
	}

	return (pFace);
}

Mesh::Face * WavefrontObject::ReadObjQuadFace(const char * buffer) const
{
	Face * pFace = NULL;
	unsigned int v1, t1, n1, v2, t2, n2, v3, t3, n3, v4, t4, n4;

	if (sscanf(buffer, "f %u/%u/%u %u/%u/%u %u/%u/%u %u/%u/%u", &v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3, &v4, &t4, &n4) == 12)
	{
		pFace = new Face(4, 4, 4); // Quad Face. Vertex + Texture + Normal.

		pFace->pVertexIndex[0] = --v1;   pFace->pVertexIndex[1] = --v2;   pFace->pVertexIndex[2] = --v3;   pFace->pVertexIndex[3] = --v4;
		pFace->pNormalIndex[0] = --n1;   pFace->pNormalIndex[1] = --n2;   pFace->pNormalIndex[2] = --n3;   pFace->pNormalIndex[3] = --n4;
		pFace->pTexCoordIndex[0] = --t1; pFace->pTexCoordIndex[1] = --t2; pFace->pTexCoordIndex[2] = --t3; pFace->pTexCoordIndex[3] = --t4;
	}
	else if (sscanf(buffer, "f %u/%u %u/%u %u/%u %u/%u", &v1, &t1, &v2, &t2, &v3, &t3, &v4, &t4) == 8)
	{
		pFace = new Face(4, 0, 4); // Quad Face. Vertex + Texture.

		pFace->pVertexIndex[0] = --v1;   pFace->pVertexIndex[1] = --v2;   pFace->pVertexIndex[2] = --v3;   pFace->pVertexIndex[3] = --v4;
		pFace->pTexCoordIndex[0] = --t1; pFace->pTexCoordIndex[1] = --t2; pFace->pTexCoordIndex[2] = --t3; pFace->pTexCoordIndex[3] = --t4;
	}
	else if (sscanf(buffer, "f %u//%u %u//%u %u//%u %u//%u", &v1, &n1, &v2, &n2, &v3, &n3, &v4, &n4) == 8)
	{
		pFace = new Face(4, 4, 0); // Quad Face. Vertex + Normal.

		pFace->pVertexIndex[0] = --v1; pFace->pVertexIndex[1] = --v2; pFace->pVertexIndex[2] = --v3; pFace->pVertexIndex[3] = --v4;
		pFace->pNormalIndex[0] = --n1; pFace->pNormalIndex[1] = --n2; pFace->pNormalIndex[2] = --n3; pFace->pNormalIndex[3] = --n4;
	}
	else if (sscanf(buffer, "f %u %u %u %u", &v1, &v2, &v3, &v4) == 4)
	{
		pFace = new Face(4, 0, 0); // Quad Face. Vertex Only.

		pFace->pVertexIndex[0] = --v1; pFace->pVertexIndex[1] = --v2; pFace->pVertexIndex[2] = --v3; pFace->pVertexIndex[3] = --v4;
	}

	return (pFace);
}

bool WavefrontObject::ReadMaterialLibrary(const std::string & filename)
{
	FILE * fp;
	char buffer[512];
	char bufferAux[512];

	int iVal;
	Vec3 vColor;
	Material * pMaterial;

	if ((fp = fopen(filename.c_str(), "rt")) == NULL)
	{
		return (false);
	}

	while (fgets(buffer, sizeof(buffer), fp))
	{
		if (sscanf(buffer, "newmtl %s", bufferAux) > 0)
		{
			Mesh::MaterialMap::const_iterator _Ptr = m_Materials.find(bufferAux);

			if (_Ptr == m_Materials.end())
			{
				pMaterial = new Material;
				m_Materials.insert(Mesh::MaterialMap::value_type(bufferAux, pMaterial));
			}
			else
			{
				pMaterial = (*_Ptr).second;
			}
		}
		else if (sscanf(buffer, "Ns %d", &iVal) == 1)
		{
			pMaterial->Shininess = iVal; // Shininess.
			pMaterial->m_flags |= Material::Color;
		}
		else if (sscanf(buffer, "Kd %f %f %f", &vColor.x, &vColor.y, &vColor.z) == 3)
		{
			pMaterial->Diffuse = vColor; // Diffuse Color.
			pMaterial->m_flags |= Material::Color;
		}
		else if (sscanf(buffer, "Ka %f %f %f", &vColor.x, &vColor.y, &vColor.z) == 3)
		{
			pMaterial->Ambient = vColor; // Ambient Color.
			pMaterial->m_flags |= Material::Color;
		}
		else if (sscanf(buffer, "Ks %f %f %f", &vColor.x, &vColor.y, &vColor.z) == 3)
		{
			pMaterial->Specular = vColor; // Specular Color.
			pMaterial->m_flags |= Material::Color;
		}
		else if (sscanf(buffer, "map_Kd %s", bufferAux) > 0)
		{
			try { // Texture throws std::runtime_error()...

				std::string texturePath(GetFilePath(filename));
				texturePath.append(bufferAux);

				pMaterial->m_pTexture = Texture2DManager::Instance()->LoadFromFile(texturePath);
				pMaterial->m_flags |= Material::TexMap; // Mesh has a texture map.
			}
			catch (std::runtime_error & except) {

				LOG_ERROR(except.what());
				continue;
			}
		}
		else
		{
			continue;
		}
	}

	fclose(fp);

	return (true);
}

bool WavefrontObject::WriteToFile(const std::string & filename)
{
	FILE * fp = fopen(filename.c_str(), "wt"); // Write text, overwrite previous.

	if (!fp)
	{
		// Failed to open file.
		return (false);
	}

	fputc('\n', fp);
	fprintf(fp, "#\n");
	fprintf(fp, "# Wavefront Object file generated by the OBJ Viewer.\n");
	fprintf(fp, "# Copyright (c) 2010 Guilherme R. Lampert\n");
	fprintf(fp, "# guilherme.ronaldo.lampert@gmail.com\n");
	fprintf(fp, "#\n");
	fprintf(fp, "# Long live John Carmack !!!\n");
	fprintf(fp, "#\n");
	fputc('\n', fp);

	unsigned int nFaces, i, j;

	// Write all the vertices
	for (i = 0; i < m_VertexCount; ++i)
	{
		// Vertex pos
		fprintf(fp, "v %f %f %f\n", m_pVertices[i].x, m_pVertices[i].y, m_pVertices[i].z);
	}

	// Must have at least 1 vertex, so no if() here...
	fprintf(fp, "# Num vertices = %u\n", m_VertexCount);
	fputc('\n', fp);

	// Write all normals, if any
	for (i = 0; i < m_NormalCount; ++i)
	{
		// Normal vertex
		fprintf(fp, "vn %f %f %f\n", m_pNormals[i].x, m_pNormals[i].y, m_pNormals[i].z);
	}

	if (m_NormalCount > 0)
	{
		fprintf(fp, "# Num normals = %u\n", m_NormalCount);
		fputc('\n', fp);
	}

	// Write all texcoords, if any
	for (i = 0; i < m_TexCoordCount; ++i)
	{
		// Tex coord
		fprintf(fp, "vt %f %f\n", m_pTexCoords[i].x, m_pTexCoords[i].y);
	}

	if (m_TexCoordCount > 0)
	{
		fprintf(fp, "# Num tex coords = %u\n", m_TexCoordCount);
		fputc('\n', fp);
	}

	// Now write the face indices:
	Mesh::GroupMap::const_iterator GroupIndex = m_FaceGroups.begin();
	Mesh::GroupMap::const_iterator GroupEnd = m_FaceGroups.end();

	while (GroupIndex != GroupEnd)
	{
		fprintf(fp, "g %s\n", (*GroupIndex).first.c_str());

		nFaces = (*GroupIndex).second->vFaces.size();

		for (j = 0; j < nFaces; ++j)
		{
			const Mesh::Face * pFace = (*GroupIndex).second->vFaces[j];

			if (pFace->nVertexCount == 3)
			{
				// Write a triangle face:

				if (pFace->pNormalIndex && pFace->pTexCoordIndex)
				{
					// Triagle Face. Vertex + Texture + Normal.
					fprintf(fp, "f %u/%u/%u %u/%u/%u %u/%u/%u\n",
						pFace->pVertexIndex[0]+1, pFace->pTexCoordIndex[0]+1, pFace->pNormalIndex[0]+1,
						pFace->pVertexIndex[1]+1, pFace->pTexCoordIndex[1]+1, pFace->pNormalIndex[1]+1,
						pFace->pVertexIndex[2]+1, pFace->pTexCoordIndex[2]+1, pFace->pNormalIndex[2]+1);
				}
				else if (pFace->pTexCoordIndex)
				{
					// Triagle Face. Vertex + Texture.
					fprintf(fp, "f %u/%u %u/%u %u/%u\n",
						pFace->pVertexIndex[0]+1, pFace->pTexCoordIndex[0]+1,
						pFace->pVertexIndex[1]+1, pFace->pTexCoordIndex[1]+1,
						pFace->pVertexIndex[2]+1, pFace->pTexCoordIndex[2]+1);
				}
				else if (pFace->pNormalIndex)
				{
					// Triagle Face. Vertex + Normal.
					fprintf(fp, "f %u//%u %u//%u %u//%u\n",
						pFace->pVertexIndex[0]+1, pFace->pNormalIndex[0]+1,
						pFace->pVertexIndex[1]+1, pFace->pNormalIndex[1]+1,
						pFace->pVertexIndex[2]+1, pFace->pNormalIndex[2]+1);
				}
				else
				{
					// Triagle Face. Vertex Only.
					fprintf(fp, "f %u %u %u\n", pFace->pVertexIndex[0]+1, pFace->pVertexIndex[1]+1, pFace->pVertexIndex[2]+1);
				}
			}
			else if (pFace->nVertexCount == 4)
			{
				// Write a quad face:
				// TODO
			}
		}

		if (nFaces > 0)
		{
			fprintf(fp, "# Num of faces in group \"%s\" = %u\n", (*GroupIndex).first.c_str(), nFaces);
			fputc('\n', fp);
		}

		++GroupIndex;
	}

	fclose(fp); // Close file

	return (true);
}

std::string WavefrontObject::GetFilePath(const std::string & filename)
{
	std::string::size_type lastSlash = filename.find_last_of('\\');

	if (lastSlash == std::string::npos)
	{
		lastSlash = filename.find_last_of('/');
	}

	std::string path = ((lastSlash != std::string::npos) ? filename.substr(0, lastSlash + 1) : "");

	return (path);
}
