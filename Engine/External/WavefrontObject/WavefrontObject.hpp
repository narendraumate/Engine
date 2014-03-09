
// ===============================================================================================================
// -*- C++ -*-
//
// WavefrontObject.hpp - Wavefront OBJ mesh loader. (Implements the 'Mesh' interface).
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

#ifndef __WAVEFRONT_OBJECT_HPP__
#define __WAVEFRONT_OBJECT_HPP__

// == External Modules ======

#include "Mesh.hpp"
#include "Vector.hpp"
#include "Utility.hpp"

// ===================================
// Wavefront Object Model Loader Class
// ===================================

class WavefrontObject : public Mesh {

	// Here is where the OBJ loading action takes place.
	// Use this class like so:
	// Mesh * m = new WavefrontObject("MyObj.obj");
	// When not in use anymore, just 'delete' the mesh pointer:
	// delete m;

public:

	WavefrontObject(void);

	WavefrontObject(const std::string & filename);

	// Load a Wavefront .OBJ from a file. The file is actually loaded into memory and parsed from there.
	virtual void LoadFromFile(const std::string & filename);

	// Write the mesh back to a Wavefront .OBJ file, with the given file name.
	virtual bool WriteToFile(const std::string & filename);

private:

	// Parse a triangular or quadric face from the data buffer.
	Mesh::Face * ReadObjTriFace(const char * buffer) const;
	Mesh::Face * ReadObjQuadFace(const char * buffer) const;

	// Parse the .mtl material library file.
	bool ReadMaterialLibrary(const std::string & filename);

	// Strip the file path from the given file mane.
	std::string GetFilePath(const std::string & filename);

	// Copy and assignment are disabled.
	WavefrontObject(const WavefrontObject &) { }
	WavefrontObject & operator = (const WavefrontObject &) { return (*this); }
};

#endif // __WAVEFRONT_OBJECT_HPP__
