//
//  GlProgram.cpp
//  Application
//
//  Created by Narendra Umate on 3/14/14.
//
//

#include "GlProgram.h"

namespace Engine
{
	GlProgram::GlProgram()
	{ }
	
	GlProgram::~GlProgram()
	{ }
	
	GLuint GlProgram::createProgram(const std::vector<GLuint>& shaders)
	{
		GLuint program = glCreateProgram();
		
		std::vector<GLuint>::const_iterator shader;
		
		for (shader = shaders.begin(); shader != shaders.end(); ++shader)
		{
			glAttachShader(program, *shader);
		}
		
		glLinkProgram(program);
		
		GLint status;
		
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		
		if (status == GL_FALSE)
		{
			GLint logLenth;
			glGetShaderiv(program, GL_INFO_LOG_LENGTH, &logLenth);
			GLchar *logString = new GLchar[logLenth + 1];
			glGetProgramInfoLog(program, logLenth, NULL, logString);
			std::cout << "Link Error: " << logString;
			delete [] logString;
		}
		
		for (shader = shaders.begin(); shader != shaders.end(); ++shader)
		{
			glDetachShader(program, *shader);
			glDeleteShader(*shader);
		}
		
		return program;
	}
	
	void GlProgram::deleteProgram(const GLuint& program)
	{
		glDeleteProgram(program);
	}
	
}
