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

	GLuint GlShader::loadShader(GLenum shaderType, const std::string &strShaderFilename)
	{
		std::string strFilename = Utils::singleton()->findFile(strShaderFilename);
		if (strFilename != "")
		{
			std::ifstream shaderFile(strFilename.c_str());
			std::stringstream shaderData;
			shaderData << shaderFile.rdbuf();
			shaderFile.close();

			const char *shaderString = shaderData.str().c_str();

			GLuint shader = glCreateShader(shaderType);
			glShaderSource(shader, 1, &shaderString, NULL);
			glCompileShader(shader);

			GLint status;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
			if (status == GL_FALSE)
			{
				GLint logLength;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
				GLchar *logString = new GLchar[logLength + 1];
				glGetProgramInfoLog(shader, logLength, NULL, logString);

				const char *shaderTypeString = NULL;
				switch(shaderType)
				{
					case GL_VERTEX_SHADER:
						shaderTypeString = "vertex";
						break;
						//case GL_GEOMETRY_SHADER:
						//	shader_type_str = "geometry";
						//	break;
					case GL_FRAGMENT_SHADER:
						shaderTypeString = "fragment";
						break;
				}

				fprintf(stderr, "Compile failure in %s shader:\n%s\n", shaderTypeString, logString);
			}
			return shader;
		}
		else
		{
			return NULL;
		}
	}

	GLuint GlShader::createProgram(const std::vector<GLuint> &shaderList)
	{
		GLuint program = glCreateProgram();

		for (std::vector<GLuint>::const_iterator shader = shaderList.begin(); shader != shaderList.end(); shader++)
			glAttachShader(program, *shader);

		glLinkProgram(program);

		GLint status;
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint logLenth;
			glGetShaderiv(program, GL_INFO_LOG_LENGTH, &logLenth);
			GLchar *logString = new GLchar[logLenth + 1];
			glGetProgramInfoLog(program, logLenth, NULL, logString);
			fprintf(stderr, "Linker failure: %s\n", logString);
		}

		for (std::vector<GLuint>::const_iterator shader = shaderList.begin(); shader != shaderList.end(); shader++)
		{
				glDetachShader(program, *shader);
				glDeleteShader(*shader);
		}

		return program;
	}

}
