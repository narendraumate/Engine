//
//  tiny_obj_loader_compact.cc
//  Application
//
//  Created by Narendra Umate on 3/26/14.
//
//

#include "tiny_obj_loader_compact.h"

// Read Write Compact Obj Wrapper
// http://swarminglogic.com/jotting/2013_10_gamedev01

namespace tinyobj {

	void write(std::ostream& stream,
			   const std::vector<tinyobj::shape_t>& shapes)
	{
		//assert(sizeof(float) == sizeof(uint32_t));
		size_t ssz = 0;
		const auto sz = sizeof(uint32_t);
		const uint32_t nMeshes = static_cast<uint32_t>(shapes.size());
		const uint32_t nMatProperties = 3;

		stream.write((const char*)&nMeshes, sz);        // nMeshes
		stream.write((const char*)&nMatProperties, sz); // nMatProperties

		for (size_t i = 0 ; i < nMeshes ; ++i) {
			const uint32_t nPositions = (uint32_t)shapes[i].mesh.positions.size();
			const uint32_t nNormals   = (uint32_t)shapes[i].mesh.normals.size();
			const uint32_t nTexcoords = (uint32_t)shapes[i].mesh.texcoords.size();
			const uint32_t nIndices   = (uint32_t)shapes[i].mesh.indices.size();

			// Write nPositions, nNormals, nTexcoords, nIndices
			// Write #nVertices positions
			// Write #nVertices normals
			// Write #nVertices texcoord
			// Write #nIndices  indices
			// Write #nMatProperties material properties
			stream.write((const char*)&nPositions, sz);
			stream.write((const char*)&nNormals,   sz);
			stream.write((const char*)&nTexcoords, sz);
			stream.write((const char*)&nIndices,   sz);

			stream.write((const char*)&shapes[i].mesh.positions[0], nPositions  * sz);
			stream.write((const char*)&shapes[i].mesh.normals[0],   nNormals   * sz);
			stream.write((const char*)&shapes[i].mesh.texcoords[0], nTexcoords * sz);
			stream.write((const char*)&shapes[i].mesh.indices[0],   nIndices   * sz);
			stream.write((const char*)&shapes[i].material.ambient[0], 3 * sz);
			stream.write((const char*)&shapes[i].material.diffuse[0], 3 * sz);
			stream.write((const char*)&shapes[i].material.specular[0], 3 * sz);
			stream.write((const char*)&shapes[i].material.transmittance[0], 3 * sz);
			stream.write((const char*)&shapes[i].material.emission[0], 3 * sz);
			stream.write((const char*)&shapes[i].material.shininess, sz);
			stream.write((const char*)&shapes[i].material.ior, sz);

			ssz = shapes[i].material.ambient_texname.size() + 1;
			stream.write((const char*)&ssz, sz);
			stream.write((const char*)&shapes[i].material.ambient_texname, ssz);
			ssz = shapes[i].material.diffuse_texname.size() + 1;
			stream.write((const char*)&ssz, sz);
			stream.write((const char*)&shapes[i].material.diffuse_texname, ssz);
			ssz = shapes[i].material.specular_texname.size() + 1;
			stream.write((const char*)&ssz, sz);
			stream.write((const char*)&shapes[i].material.specular_texname, ssz);
			ssz = shapes[i].material.normal_texname.size() + 1;
			stream.write((const char*)&ssz, sz);
			stream.write((const char*)&shapes[i].material.normal_texname, ssz);
		}
	}

	std::vector<tinyobj::shape_t> read(std::istream& stream)
	{
		//assert(sizeof(float) == sizeof(uint32_t));
		size_t ssz = 0;
		const auto sz = sizeof(uint32_t);

		std::vector<tinyobj::shape_t> shapes;

		uint32_t nMeshes = 0;
		uint32_t nMatProperties = 0;
		stream.read((char*)&nMeshes, sz);
		stream.read((char*)&nMatProperties, sz);
		shapes.resize(nMeshes);
		for (size_t i = 0 ; i < nMeshes ; ++i) {
			uint32_t nPositions = 0, nNormals = 0, nTexcoords = 0, nIndices = 0;
			stream.read((char*)&nPositions, sz);
			stream.read((char*)&nNormals,   sz);
			stream.read((char*)&nTexcoords, sz);
			stream.read((char*)&nIndices,   sz);

			shapes[i].mesh.positions.resize(nPositions);
			shapes[i].mesh.normals.resize(nNormals);
			shapes[i].mesh.texcoords.resize(nTexcoords);
			shapes[i].mesh.indices.resize(nIndices);

			stream.read((char*)&shapes[i].mesh.positions[0], nPositions  * sz);
			stream.read((char*)&shapes[i].mesh.normals[0],   nNormals   * sz);
			stream.read((char*)&shapes[i].mesh.texcoords[0], nTexcoords * sz);
			stream.read((char*)&shapes[i].mesh.indices[0],   nIndices   * sz);
			stream.read((char*)&shapes[i].material.ambient[0], 3 * sz);
			stream.read((char*)&shapes[i].material.diffuse[0], 3 * sz);
			stream.read((char*)&shapes[i].material.specular[0], 3 * sz);
			stream.read((char*)&shapes[i].material.transmittance[0], 3 * sz);
			stream.read((char*)&shapes[i].material.emission[0], 3 * sz);
			stream.read((char*)&shapes[i].material.shininess, sz);
			stream.read((char*)&shapes[i].material.ior, sz);

			stream.read((char*)&ssz, sz);
			stream.read((char*)&shapes[i].material.ambient_texname, ssz);
			stream.read((char*)&ssz, sz);
			stream.read((char*)&shapes[i].material.diffuse_texname, ssz);
			stream.read((char*)&ssz, sz);
			stream.read((char*)&shapes[i].material.specular_texname, ssz);
			stream.read((char*)&ssz, sz);
			stream.read((char*)&shapes[i].material.normal_texname, ssz);
		}
		return shapes;
	}

	std::string LoadObjCompact(
							   std::vector<shape_t>& shapes,
							   const char* filename,
							   const char* mtl_basepath)
	{
		std::string returnString;

		char extension[] = ".compact";
		char compactFilename[strlen(filename) + strlen(extension)];
		compactFilename[0] = '\0';

		strcat(compactFilename, filename);
		strcat(compactFilename, extension);

		std::ifstream ifs(compactFilename);

		if (ifs)
		{
			shapes = read(ifs);
		}
		else
		{
			std::string returnString = LoadObj(shapes, filename, mtl_basepath);

			if (returnString.empty())
			{
				std::ofstream ofs(compactFilename);
				write(ofs, shapes);
			}
		}
		
		return returnString;
	}

}