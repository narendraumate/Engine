//
//  Shader.h
//  Application
//
//  Created by Narendra Umate on 9/28/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#ifndef __Application__Shader__
#define __Application__Shader__

#if defined(__APPLE__)
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#elif defined(__linux__)
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h> // sudo apt-get install mesa-common-dev mesa-utils freeglut3 freeglut3-dev
#endif //defined(__linux__)

#include <string>
#include <fstream>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <vector>

#define LOCAL_FILE_DIR "Data/"
#if defined(__APPLE__)
#define GLOBAL_FILE_DIR "/Users/ardneran/Documents/Projects/GitHub/Engine/Data/"
#elif defined(__linux__)
#define GLOBAL_FILE_DIR "/home/ardneran/Documents/Engine/Data/"
#endif //defined(__linux__)

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
