//
//  tiny_model_loader_compact.cc
//  Application
//
//  Created by Narendra Umate on 3/26/14.
//
//

#include "tiny_model_loader_compact.h"

// Read Write Compact Obj Wrapper with Tangents and Bitangents
// http://swarminglogic.com/jotting/2013_10_gamedev01

namespace tinyobj {

	void writeString(std::ostream& stream, const std::string& str)
	{
		size_t sz = sizeof(uint32_t);
		size_t ssz = str.size() + 1;
		char* cstr = new char[ssz];
		strcpy(cstr, str.c_str());
		stream.write((const char*)&ssz, sz);
		stream.write((const char*)cstr, ssz);
		delete [] cstr;
	}

	void readString(std::istream& stream, std::string& str)
	{
		size_t sz = sizeof(uint32_t);
		size_t ssz = 0;
		stream.read((char*)&ssz, sz);
		char* cstr = new char[ssz];
		stream.read((char*)cstr, ssz);
		str = cstr;
		delete [] cstr;
	}

	void write(std::ostream& stream, const std::vector<tinyobj::shape_c_t> &shapes)
	{
		assert(sizeof(float) == sizeof(uint32_t));
		//size_t ssz = 0;
		const size_t sz = sizeof(uint32_t);
		const uint32_t nShapes = static_cast<uint32_t>(shapes.size());
		const uint32_t nMatProperties = 3;

		stream.write((const char*)&nShapes, sz);
		stream.write((const char*)&nMatProperties, sz);

		for (size_t i = 0 ; i < nShapes ; ++i) {
			const uint32_t nPositions  = (uint32_t)shapes[i].mesh.positions.size();
			const uint32_t nNormals    = (uint32_t)shapes[i].mesh.normals.size();
			const uint32_t nTexcoords  = (uint32_t)shapes[i].mesh.texcoords.size();
			const uint32_t nTangents   = (uint32_t)shapes[i].mesh.tangents.size();
			const uint32_t nBitangents = (uint32_t)shapes[i].mesh.bitangents.size();
			const uint32_t nIndices    = (uint32_t)shapes[i].mesh.indices.size();

			stream.write((const char*)&nPositions,  sz);
			stream.write((const char*)&nNormals,    sz);
			stream.write((const char*)&nTexcoords,  sz);
			stream.write((const char*)&nTangents,   sz);
			stream.write((const char*)&nBitangents, sz);
			stream.write((const char*)&nIndices,    sz);

			stream.write((const char*)&shapes[i].mesh.positions[0], nPositions * sz);
			stream.write((const char*)&shapes[i].mesh.normals[0], nNormals * sz);
			stream.write((const char*)&shapes[i].mesh.texcoords[0], nTexcoords * sz);
			stream.write((const char*)&shapes[i].mesh.tangents[0], nTangents * sz);
			stream.write((const char*)&shapes[i].mesh.bitangents[0], nBitangents * sz);
			stream.write((const char*)&shapes[i].mesh.indices[0], nIndices * sz);
			stream.write((const char*)&shapes[i].material.ambient[0], 3 * sz);
			stream.write((const char*)&shapes[i].material.diffuse[0], 3 * sz);
			stream.write((const char*)&shapes[i].material.specular[0], 3 * sz);
			stream.write((const char*)&shapes[i].material.transmittance[0], 3 * sz);
			stream.write((const char*)&shapes[i].material.emission[0], 3 * sz);
			stream.write((const char*)&shapes[i].material.shininess, sz);
			stream.write((const char*)&shapes[i].material.ior, sz);
			stream.write((const char*)&shapes[i].material.dissolve, sz);
			stream.write((const char*)&shapes[i].material.illum, sizeof(int));

			writeString(stream, shapes[i].name);
			writeString(stream, shapes[i].material.name);
			writeString(stream, shapes[i].material.ambient_texname);
			writeString(stream, shapes[i].material.diffuse_texname);
			writeString(stream, shapes[i].material.specular_texname);
			writeString(stream, shapes[i].material.normal_texname);

			const uint32_t nUnknownParameters = (uint32_t)shapes[i].material.unknown_parameter.size();
			stream.write((const char*)&nUnknownParameters, sz);//TODO
		}
	}

	void read(std::istream& stream, std::vector<tinyobj::shape_c_t> &shapes)
	{
		assert(sizeof(float) == sizeof(uint32_t));
		//size_t ssz = 0;
		const size_t sz = sizeof(uint32_t);

		uint32_t nShapes = 0;
		uint32_t nMatProperties = 0;
		stream.read((char*)&nShapes, sz);
		stream.read((char*)&nMatProperties, sz);
		shapes.resize(nShapes);
		for (size_t i = 0 ; i < nShapes ; ++i) {
			uint32_t nPositions = 0, nNormals = 0, nTexcoords = 0, nTangents = 0, nBitangents = 0, nIndices = 0;
			stream.read((char*)&nPositions,  sz);
			stream.read((char*)&nNormals,    sz);
			stream.read((char*)&nTexcoords,  sz);
			stream.read((char*)&nTangents,   sz);
			stream.read((char*)&nBitangents, sz);
			stream.read((char*)&nIndices,    sz);

			shapes[i].mesh.positions.resize(nPositions);
			shapes[i].mesh.normals.resize(nNormals);
			shapes[i].mesh.texcoords.resize(nTexcoords);
			shapes[i].mesh.tangents.resize(nTangents);
			shapes[i].mesh.bitangents.resize(nBitangents);
			shapes[i].mesh.indices.resize(nIndices);

			stream.read((char*)&shapes[i].mesh.positions[0], nPositions * sz);
			stream.read((char*)&shapes[i].mesh.normals[0], nNormals * sz);
			stream.read((char*)&shapes[i].mesh.texcoords[0], nTexcoords * sz);
			stream.read((char*)&shapes[i].mesh.tangents[0], nTangents * sz);
			stream.read((char*)&shapes[i].mesh.bitangents[0], nBitangents * sz);
			stream.read((char*)&shapes[i].mesh.indices[0], nIndices * sz);
			stream.read((char*)&shapes[i].material.ambient[0], 3 * sz);
			stream.read((char*)&shapes[i].material.diffuse[0], 3 * sz);
			stream.read((char*)&shapes[i].material.specular[0], 3 * sz);
			stream.read((char*)&shapes[i].material.transmittance[0], 3 * sz);
			stream.read((char*)&shapes[i].material.emission[0], 3 * sz);
			stream.read((char*)&shapes[i].material.shininess, sz);
			stream.read((char*)&shapes[i].material.ior, sz);
			stream.read((char*)&shapes[i].material.dissolve, sz);
			stream.read((char*)&shapes[i].material.illum, sizeof(int));

			readString(stream, shapes[i].name);
			readString(stream, shapes[i].material.name);
			readString(stream, shapes[i].material.ambient_texname);
			readString(stream, shapes[i].material.diffuse_texname);
			readString(stream, shapes[i].material.specular_texname);
			readString(stream, shapes[i].material.normal_texname);

			uint32_t nUnknownParameters = 0;
			stream.read((char*)&nUnknownParameters, sz);//TODO
		}
	}

	void printInfo(const std::vector<tinyobj::shape_c_t>& shapes, const std::string& filename)
	{
		std::cout << "# of shapes : " << shapes.size() << std::endl;

		for (size_t i = 0; i < shapes.size(); i++) {
			printf("shape[%ld].name = %s\n", i, shapes[i].name.c_str());
			printf("shape[%ld].indices: %ld\n", i, shapes[i].mesh.indices.size());
			assert((shapes[i].mesh.indices.size() % 3) == 0);
#ifdef PRINTINFO_DETAILS
			for (size_t f = 0; f < shapes[i].mesh.indices.size(); f++) {
				printf("  idx[%ld] = %d\n", f, shapes[i].mesh.indices[f]);
			}
#endif // PRINTINFO_DETAILS
			printf("shape[%ld].vertices: %ld\n", i, shapes[i].mesh.positions.size());
			assert((shapes[i].mesh.positions.size() % 3) == 0);
#ifdef PRINTINFO_DETAILS
			for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
				printf("  v[%ld] = (%f, %f, %f)\n", v,
					   shapes[i].mesh.positions[3*v+0],
					   shapes[i].mesh.positions[3*v+1],
					   shapes[i].mesh.positions[3*v+2]);
			}
#endif // PRINTINFO_DETAILS
			printf("shape[%ld].material.name = %s\n", i, shapes[i].material.name.c_str());
			printf("  material.Ka = (%f, %f ,%f)\n", shapes[i].material.ambient[0], shapes[i].material.ambient[1], shapes[i].material.ambient[2]);
			printf("  material.Kd = (%f, %f ,%f)\n", shapes[i].material.diffuse[0], shapes[i].material.diffuse[1], shapes[i].material.diffuse[2]);
			printf("  material.Ks = (%f, %f ,%f)\n", shapes[i].material.specular[0], shapes[i].material.specular[1], shapes[i].material.specular[2]);
			printf("  material.Tr = (%f, %f ,%f)\n", shapes[i].material.transmittance[0], shapes[i].material.transmittance[1], shapes[i].material.transmittance[2]);
			printf("  material.Ke = (%f, %f ,%f)\n", shapes[i].material.emission[0], shapes[i].material.emission[1], shapes[i].material.emission[2]);
			printf("  material.Ns = %f\n", shapes[i].material.shininess);
			printf("  material.Ni = %f\n", shapes[i].material.ior);
			printf("  material.dissolve = %f\n", shapes[i].material.dissolve);
			printf("  material.illum = %d\n", shapes[i].material.illum);
			printf("  material.map_Ka = %s\n", shapes[i].material.ambient_texname.c_str());
			printf("  material.map_Kd = %s\n", shapes[i].material.diffuse_texname.c_str());
			printf("  material.map_Ks = %s\n", shapes[i].material.specular_texname.c_str());
			printf("  material.map_Ns = %s\n", shapes[i].material.normal_texname.c_str());
			std::map<std::string, std::string>::const_iterator it(shapes[i].material.unknown_parameter.begin());
			std::map<std::string, std::string>::const_iterator itEnd(shapes[i].material.unknown_parameter.end());
			for (; it != itEnd; it++) {
				printf("  material.%s = %s\n", it->first.c_str(), it->second.c_str());
			}
			printf("\n");
		}
	}

	void computeTangentBasis(const std::vector<float>& positions,
							 const std::vector<float>& normals,
							 const std::vector<float>& texcoords,
							 const std::vector<unsigned int>& indices,
							 std::vector<float>& tangents,
							 std::vector<float>& bitangents)
	{
		tangents.resize(positions.size());
		bitangents.resize(positions.size());

		if (texcoords.size())
		{
			for (unsigned int k = 0; k < indices.size(); k += 3)
			{
				// Shortcuts for vertices
				Engine::Vec3* v0 = (Engine::Vec3*)&positions[3 * indices[k  ]];
				Engine::Vec3* v1 = (Engine::Vec3*)&positions[3 * indices[k+1]];
				Engine::Vec3* v2 = (Engine::Vec3*)&positions[3 * indices[k+2]];

				// Shortcuts for UVs
				Engine::Vec2* uv0 = (Engine::Vec2*)&texcoords[2 * indices[k  ]];
				Engine::Vec2* uv1 = (Engine::Vec2*)&texcoords[2 * indices[k+1]];
				Engine::Vec2* uv2 = (Engine::Vec2*)&texcoords[2 * indices[k+2]];

				// Edges of the triangle : postion delta
				Engine::Vec3 deltaPos1 = *v1-*v0;
				Engine::Vec3 deltaPos2 = *v2-*v0;

				// UV delta
				Engine::Vec2 deltaUV1 = *uv1-*uv0;
				Engine::Vec2 deltaUV2 = *uv2-*uv0;

				float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
				Engine::Vec3 tangent = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;
				Engine::Vec3 bitangent = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;

				// Set the same tangent for all three vertices of the triangle.
				// They will be merged later, in vboindexer.cpp
				tangents[3 * indices[k  ]] = tangent.x; tangents[3 * indices[k  ] + 1] = tangent.y; tangents[3 * indices[k  ] + 2] = tangent.z;
				tangents[3 * indices[k+1]] = tangent.x; tangents[3 * indices[k+1] + 1] = tangent.y; tangents[3 * indices[k+1] + 2] = tangent.z;
				tangents[3 * indices[k+2]] = tangent.x; tangents[3 * indices[k+2] + 1] = tangent.y; tangents[3 * indices[k+2] + 2] = tangent.z;

				// Same thing for binormals
				bitangents[3 * indices[k  ]] = bitangent.x; bitangents[3 * indices[k  ] + 1] = bitangent.y; bitangents[3 * indices[k  ] + 2] = bitangent.z;
				bitangents[3 * indices[k+1]] = bitangent.x; bitangents[3 * indices[k+1] + 1] = bitangent.y; bitangents[3 * indices[k+1] + 2] = bitangent.z;
				bitangents[3 * indices[k+2]] = bitangent.x; bitangents[3 * indices[k+2] + 1] = bitangent.y; bitangents[3 * indices[k+2] + 2] = bitangent.z;
			}

			// See "Going Further"
			if (normals.size())
			{
				for (unsigned int i = 0; i < positions.size(); i += 3)
				{
					Engine::Vec3 n(normals[i], normals[i+1], normals[i+2]);
					Engine::Vec3 t(tangents[i], tangents[i+1], tangents[i+2]);
					Engine::Vec3 b(bitangents[i], bitangents[i+1], bitangents[i+2]);

					// Gram-Schmidt orthogonalize
					t = (t - n * dot(n, t)).normal();

					// Calculate handedness
					if (dot(cross(n, t), b) < 0.0f)
					{
						t = t * -1.0f;
					}

					tangents[i  ] = t.x;
					tangents[i+1] = t.y;
					tangents[i+2] = t.z;
				}
			}
		}
	}	

	std::vector<shape_c_t> addTangentsAndBitangents(const std::vector<shape_t>& shapes)
	{
		std::vector<shape_c_t> shapes_c;
		shapes_c.resize(shapes.size());
		for (int i = 0; i < shapes.size(); ++i)
		{
			shapes_c[i].name = shapes[i].name;
			shapes_c[i].material = shapes[i].material;
			shapes_c[i].mesh.positions = shapes[i].mesh.positions;
			shapes_c[i].mesh.normals = shapes[i].mesh.normals;
			shapes_c[i].mesh.texcoords = shapes[i].mesh.texcoords;
			shapes_c[i].mesh.indices = shapes[i].mesh.indices;
			computeTangentBasis(shapes_c[i].mesh.positions, shapes_c[i].mesh.normals, shapes_c[i].mesh.texcoords, shapes_c[i].mesh.indices, shapes_c[i].mesh.tangents, shapes_c[i].mesh.bitangents);
		}
		return shapes_c;
	}

	std::string LoadModelCompact(std::vector<shape_c_t>& shapes_c, const char* filename, const char* model_basepath, const bool& enable_compact)
	{
		std::string returnString("");

		std::string compactFilename(filename);
		compactFilename.append(".compact");

		std::ifstream ifs(compactFilename.c_str());

		if (enable_compact && ifs)
		{
			read(ifs, shapes_c);
			//printInfo(shapes_c, compactFilename + ".r");
		}
		else
		{
			std::vector<shape_t> shapes;

			if (strcmp(filename, "") == 0)
				returnString = "Model file not found";
			else if (strstr(filename, ".obj"))
				returnString = LoadObj(shapes, filename, model_basepath);
			else if (strstr(filename, ".mesh"))
				returnString = LoadMesh(shapes, filename);
			else
				returnString = "Model format not supported";

			if (returnString.empty())
			{
				shapes_c = addTangentsAndBitangents(shapes);
				std::ofstream ofs(compactFilename.c_str());
				write(ofs, shapes_c);
				//printInfo(shapes_c, compactFilename + ".w");
				ofs.close();
			}
		}

		ifs.close();

		return returnString;
	}

}