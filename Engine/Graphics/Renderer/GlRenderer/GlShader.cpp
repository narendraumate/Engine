//
//  GlShader.cpp
//  Application
//
//  Created by Narendra Umate on 9/28/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#include "GlShader.h"

namespace Engine
{
	GlShader::GlShader()
	{ }
	
	GlShader::~GlShader()
	{ }

	GLuint GlShader::loadShader(const std::string& shaderName)
	{
		//TODO
		return 0;
	}

	GLuint GlShader::loadShader(const std::string& shaderFilename, const GLenum& shaderType)
	{
		std::string strFilename = Utils::singleton()->findFilePath(shaderFilename);
		if (!strFilename.empty())
		{			
			char* shaderString = loadShaderSourceFile(strFilename.c_str());
			//std::cout << shaderString << std::endl;
			GLuint shader = glCreateShader(shaderType);
			glShaderSource(shader, 1, &shaderString, NULL);
			glCompileShader(shader);
			delete [] shaderString;
			
			GLint status;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
			if (status == GL_FALSE)
			{
				GLint logLength;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
				GLchar *logString = new GLchar[logLength + 1];
				glGetProgramInfoLog(shader, logLength, NULL, logString);
				
				fprintf(stderr, "Compile Error: %s\n%s", shaderFilename.c_str(), logString);
				delete [] logString;
			}
			return shader;
		}
		else
		{
			fprintf(stderr, "File Missing: %s\n", shaderFilename.c_str());
			return 0;
		}
	}
	
	std::vector<GLuint> GlShader::loadShaderMap(const std::map<std::string, GLenum>& shaderFilenameTypePairs)
	{
		std::vector<GLuint> shaders;
		for (std::map<std::string, GLuint>::const_iterator shaderPair = shaderFilenameTypePairs.begin(); shaderPair != shaderFilenameTypePairs.end(); ++shaderPair)
		{
			if (GLuint shader = loadShader(shaderPair->first, shaderPair->second))
			{
				shaders.push_back(shader);
			}
		}
		return shaders;
	}
	
	char* GlShader::loadShaderSourceFile(const char* shaderSourceFile)
	{
		std::ifstream fin;
		long int fileSize = 0;
		char* buffer;
		
		// Open the shader source file
		fin.open(shaderSourceFile);
		
		// If it could not open the file then exit
		if (fin.fail() == true)
		{
			return 0;
		}
		
		// Find filesize
		fin.seekg(0, fin.end);
		fileSize = fin.tellg();
		
		// Place get pointer at the beginning
		fin.seekg(0, fin.beg);
		
		// Initialize the buffer to read the shader source file into
		// Not sure if I should add 1
		buffer = new char[fileSize];
		if (buffer == nullptr)
		{
			fin.close();
			return 0;
		}
		
		// Read the shader text file into the buffer as a block
		fin.read(buffer, fileSize);
		
		// Close the file
		fin.close();
		
		// Null terminate the buffer
		// Don't know if this is needed
		buffer[fileSize] = '\0';
		
		return buffer;
	}
	
}
