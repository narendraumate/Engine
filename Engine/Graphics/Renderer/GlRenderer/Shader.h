//
//  Shader.h
//  Application
//
//  Created by Narendra Umate on 9/28/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#ifndef __Application__Shader__
#define __Application__Shader__

#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <vector>

#define LOCAL_FILE_DIR "Data/"
#define GLOBAL_FILE_DIR "/Users/ardneran/Documents/Projects/GitHub/Engine/Data/"

class Shader
{
public:
	static GLuint LoadShader(GLenum eShaderType, const std::string &strShaderFilename);
	static GLuint CreateShader(GLenum shader_type, const char *shader_string);
	static GLuint CreateProgram(const std::vector<GLuint> &shaderList);

private:
	static std::string FindFileOrThrow(const std::string &strBasename);
};

#endif /* defined(__Application__Shader__) */
