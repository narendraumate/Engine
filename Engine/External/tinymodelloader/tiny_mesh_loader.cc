//
//  tiny_mesh_loader.cc
//  Application
//
//  Created by Narendra Umate on 6/7/14.
//
//

#include "tiny_mesh_loader.h"

namespace tinyobj {

	std::string readCString(std::istream& stream)
	{
		std::string str = "";
		size_t sz = sizeof(char);
		size_t ssz = 0;
		stream.read((char*)&ssz, sz);
		char* cstr = new char[ssz + 1];
		stream.read((char*)cstr, ssz);
		cstr[ssz] = '\0';
		str = cstr;
		delete [] cstr;
		return str;
	}

	void read(std::istream& stream, float& value)
	{
		const size_t sz = sizeof(float);
		stream.read((char*)&value, sz);
	}

	void read(std::istream& stream, uint8_t& value)
	{
		const size_t sz = sizeof(uint8_t);
		stream.read((char*)&value, sz);
	}

	/*void read(std::istream& stream, int8_t& value)
	{
		const size_t sz = sizeof(int8_t);
		stream.read((char*)&value, sz);
	}*/

	void read(std::istream& stream, uint16_t& value)
	{
		const size_t sz = sizeof(uint16_t);
		stream.read((char*)&value, sz);
	}

	void read(std::istream& stream, int16_t& value)
	{
		const size_t sz = sizeof(int16_t);
		stream.read((char*)&value, sz);
	}

	void read(std::istream& stream, uint32_t& value)
	{
		const size_t sz = sizeof(uint32_t);
		stream.read((char*)&value, sz);
	}

	bool loadArmature(std::istream& stream)
	{
		uint32_t nBones = 0;
		read(stream, nBones);

		if (nBones == 0)
		{
			return false;
		}

		for (int boneIndex = 0; boneIndex < nBones; ++boneIndex)
		{
			std::string boneName = readCString(stream);

			int16_t parentId = 0;
			read(stream, parentId);

			float absPosX = 0.0f;
			read(stream, absPosX);
			float absPosY = 0.0f;
			read(stream, absPosY);
			float absPosZ = 0.0f;
			read(stream, absPosZ);
		}
		return true;
	}

	void loadShape(std::istream& stream, const bool& hasArmature, shape_t &shape)
	{
		shape.name = readCString(stream);

		uint32_t uvLayerCount = 0;
		read(stream, uvLayerCount);
		uint32_t textureCount = 0;
		read(stream, textureCount);

		for (int textureIndex = 0; textureIndex < textureCount; ++textureIndex)
		{
			std::string textureFilename = readCString(stream);

			uint32_t textureUvLayerIndex = 0;
			read(stream, textureUvLayerIndex);
		}

		uint32_t vertexCount = 0;
		read(stream, vertexCount);

		shape.mesh.positions.resize(vertexCount * 3);
		shape.mesh.normals.resize(vertexCount * 3);
		shape.mesh.texcoords.resize(vertexCount * 2);

		for (int vertexIndex = 0; vertexIndex < vertexCount; ++vertexIndex)
		{
			read(stream, shape.mesh.positions[3 * vertexIndex    ]);
			read(stream, shape.mesh.positions[3 * vertexIndex + 1]);
			read(stream, shape.mesh.positions[3 * vertexIndex + 2]);

			read(stream, shape.mesh.normals[3 * vertexIndex    ]);
			read(stream, shape.mesh.normals[3 * vertexIndex + 1]);
			read(stream, shape.mesh.normals[3 * vertexIndex + 2]);

			uint8_t colorR = 0; read(stream, colorR); colorR /= 255.0f;
			uint8_t colorG = 0; read(stream, colorG); colorG /= 255.0f;
			uint8_t colorB = 0; read(stream, colorB); colorB /= 255.0f;
			uint8_t colorA = 0; read(stream, colorA); colorA /= 255.0f;

			for (int uvLayerIndex = 0; uvLayerIndex < uvLayerCount; ++uvLayerIndex)
			{
				read(stream, shape.mesh.texcoords[2 * vertexIndex    ]);
				read(stream, shape.mesh.texcoords[2 * vertexIndex + 1]);
			}

			for (int uvLayerIndex = 0; uvLayerIndex < uvLayerCount; ++uvLayerIndex)
			{
				float tangentX = 0.0f; read(stream, tangentX);
				float tangentY = 0.0f; read(stream, tangentY);
				float tangentZ = 0.0f; read(stream, tangentZ);
				float tangentW = 0.0f; read(stream, tangentW);
			}

			if (hasArmature)
			{
				uint16_t boneIndex = 0;
				for (int i = 0; i < 4; ++i)
				{
					read(stream, boneIndex);
				}
				float boneWeight = 0;
				for (int i = 0; i < 4; ++i)
				{
					read(stream, boneWeight);
				}
			}

		}

		uint32_t faceCount = 0;
		read(stream, faceCount);
		shape.mesh.indices.resize(faceCount * 3);

		int index = 0;
		uint32_t value = 0;
		for (int faceIndex = 0; faceIndex < faceCount; ++faceIndex)
		{
			read(stream, value); shape.mesh.indices[index    ] = value;
			read(stream, value); shape.mesh.indices[index + 1] = value;
			read(stream, value); shape.mesh.indices[index + 2] = value;
			index += 3;
		}

	}

	std::string LoadMesh(std::vector<shape_t>& shapes, const char* filename)
	{
		std::ifstream ifs(filename);

		if (ifs)
		{
			bool hasArmature = loadArmature(ifs);

			uint32_t shapeCount = 0;
			read(ifs, shapeCount);
			shapes.resize(shapeCount);

			for (int shapeIndex = 0; shapeIndex < shapeCount; ++shapeIndex)
			{
				loadShape(ifs, hasArmature, shapes[shapeIndex]);
			}

			return "";
		}
		else
		{
			return "Mesh file not found";
		}
	}

}
