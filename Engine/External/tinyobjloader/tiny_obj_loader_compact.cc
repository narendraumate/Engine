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

	void write(std::ostream& stream, const std::vector<tinyobj::shape_t> &shapes)
	{
		assert(sizeof(float) == sizeof(uint32_t));
		//size_t ssz = 0;
		const size_t sz = sizeof(uint32_t);
		const uint32_t nShapes = static_cast<uint32_t>(shapes.size());
		const uint32_t nMatProperties = 3;

		stream.write((const char*)&nShapes, sz);
		stream.write((const char*)&nMatProperties, sz);

		for (size_t i = 0 ; i < nShapes ; ++i) {
			const uint32_t nPositions = (uint32_t)shapes[i].mesh.positions.size();
			const uint32_t nNormals   = (uint32_t)shapes[i].mesh.normals.size();
			const uint32_t nTexcoords = (uint32_t)shapes[i].mesh.texcoords.size();
			const uint32_t nIndices   = (uint32_t)shapes[i].mesh.indices.size();

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

	void read(std::istream& stream, std::vector<tinyobj::shape_t> &shapes)
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

	void printInfo(const std::vector<tinyobj::shape_t>& shapes, const std::string& filename)
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

	std::string LoadObjCompact(std::vector<shape_t>& shapes, const char* filename, const char* mtl_basepath, const bool& enable_compact)
	{
		std::string returnString("");

		std::string compactFilename(filename);
		compactFilename.append(".compact");

		std::ifstream ifs(compactFilename.c_str());

		if (enable_compact && ifs)
		{
			read(ifs, shapes);
			//printInfo(shapes, compactFilename + ".r");
		}
		else
		{
			std::string returnString = LoadObj(shapes, filename, mtl_basepath);

			if (returnString.empty())
			{
				std::ofstream ofs(compactFilename.c_str());
				write(ofs, shapes);
				//printInfo(shapes, compactFilename + ".w");
				ofs.close();
			}
			else
			{
				std::cout << returnString << std::endl;
			}
		}

		ifs.close();

		return returnString;
	}

}