//
//  ObjLoader.cpp
//  Application
//
//  Created by Narendra Umate on 1/1/14.
//
//

#include "ObjLoader.h"

Engine::ObjLoader* Engine::ObjLoader::s_instance = NULL;

namespace Engine
{

	ObjLoader::ObjLoader()
	{ }

	ObjLoader::~ObjLoader()
	{ }

	ObjLoader* ObjLoader::singleton()
	{
		if (s_instance == NULL)
		{
			s_instance = new ObjLoader();
		}
		return s_instance;
	}

	void ObjLoader::destroySingleton()
	{
		if (s_instance)
		{
			delete s_instance;
			s_instance = NULL;
		}
	}

	Mesh ObjLoader::loadObj(const std::string& strObjFileName)
	{
		Mesh mesh;

		std::string strFilename = Utils::singleton()->findFile(strObjFileName);
		if (strFilename != "")
		{
			std::vector<unsigned int> vertexIndices;
			std::vector<unsigned int> uvIndices;
			std::vector<unsigned int> normalIndices;

			std::vector<Vec3> vertices;
			std::vector<Vec2> uvs;
			std::vector<Vec3> normals;

			std::string line;
			std::string token;
			std::istringstream lineStream;

			std::ifstream objFile(strFilename.c_str());

			float x, y, z;
			float u, v;

			while (!objFile.eof())
			{
				getline(objFile, line);
				if (line.length() > 0 && line.at(0) != '#')
				{
					lineStream.str(line);

					lineStream >> token;

					if (token == "v")
					{
						lineStream >> x >> y >> z;
						vertices.push_back(Vec3(x, y, z));
					}
					else if (token == "vt")
					{
						lineStream >> u >> v;
						uvs.push_back(Vec2(u, v));
					}
					else if (token == "vn")
					{
						lineStream >> x >> y >> z;
						normals.push_back(Vec3(x, y, z));
					}
					else if (token == "f")
					{
						unsigned int vertexIndex[3];
						unsigned int uvIndex[3];
						unsigned int normalIndex[3];

						/*
						lineStream >> vertexIndex[0] >> uvIndex[0] >> normalIndex[0] >> vertexIndex[1] >> uvIndex[1] >> normalIndex[1] >> vertexIndex[2] >> uvIndex[2] >> normalIndex[2];
						vertexIndices.push_back(vertexIndex[0]);
						vertexIndices.push_back(vertexIndex[1]);
						vertexIndices.push_back(vertexIndex[2]);
						uvIndices.push_back(uvIndex[0]);
						uvIndices.push_back(uvIndex[1]);
						uvIndices.push_back(uvIndex[2]);
						normalIndices.push_back(normalIndex[0]);
						normalIndices.push_back(normalIndex[1]);
						normalIndices.push_back(normalIndex[2]);
						*/
						
						lineStream >> vertexIndex[0] >> vertexIndex[1] >> vertexIndex[2];
						vertexIndices.push_back(vertexIndex[0]);
						vertexIndices.push_back(vertexIndex[1]);
						vertexIndices.push_back(vertexIndex[2]);
					}
				}
			}

			objFile.close();


			// For each vertex of each triangle
			for (unsigned int i = 0; i < vertexIndices.size(); ++i)
			{
				// Get the indices of its attributes
				unsigned int vertexIndex = vertexIndices[i];
				//unsigned int uvIndex = uvIndices[i];
				//unsigned int normalIndex = normalIndices[i];

				// Get the attributes thanks to the index
				Vec3 vertex = vertices[ vertexIndex-1 ];
				//Vec2 uv = uvs[ uvIndex-1 ];
				//Vec3 normal = normals[ normalIndex-1 ];

				// Put the attributes in buffers
				mesh.pushVertex(vertex);
				//mesh.pushUv(uv);
				//mesh.pushNormal(normal);
			}
		}
		return mesh;
	}
}
