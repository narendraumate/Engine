
// ===============================================================================================================
// -*- C++ -*-
//
// Texture.cpp - Texture creation and management.
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

#include "Texture.hpp"

// == Class Texture2D ==

Texture2D::Texture2D(void) : m_fail_flag(true), m_handle(0)
{
}

Texture2D::Texture2D(const std::string & filename) : m_fail_flag(true), m_handle(0)
{
	int width, height, bytesPerPixel;
	unsigned char * buffer = LoadUncompressedTGA(filename.c_str(), width, height, bytesPerPixel);

	if (buffer != 0) // LoadUncompressedTGA() will return a null pointer on failure.
	{
		// TGAs are in BGR/BGRA format
		const unsigned short format = ((bytesPerPixel == 4) ? (GL_BGRA_EXT) : (GL_BGR_EXT));
		const unsigned short internalFormat = bytesPerPixel;

		glGenTextures(1, &m_handle);
		glBindTexture(GL_TEXTURE_2D, m_handle);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// The code below generates dependency with the GLEW library.
		// It's not worth have this dependency just to add such small functionality...
		/*if (GLEW_SGIS_generate_mipmap) // Hardware mipmap generation:
		{
			glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
			glHint(GL_GENERATE_MIPMAP_HINT_SGIS, GL_NICEST);

			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, bitmapInfoHeader.biWidth,
					bitmapInfoHeader.biHeight, 0, format, GL_UNSIGNED_BYTE, buffer);
		}*/

		gluBuild2DMipmaps(GL_TEXTURE_2D, internalFormat, width, height, format, GL_UNSIGNED_BYTE, buffer);

		free(buffer);
		m_file_name = filename;
		m_fail_flag = false;
	}
}

bool Texture2D::Fail(void) const
{
	return (m_fail_flag);
}

void Texture2D::Bind(unsigned int texUnit) const
{
	glActiveTexture(GL_TEXTURE0 + texUnit);
	glBindTexture(GL_TEXTURE_2D, m_handle);
}

int Texture2D::GetHandle(void) const
{
	return (m_handle);
}

const std::string & Texture2D::Name(void) const
{
	return (m_file_name);
}

Texture2D::~Texture2D(void)
{
	if (!m_fail_flag)
	{
		glDeleteTextures(1, &m_handle);
	}
}
