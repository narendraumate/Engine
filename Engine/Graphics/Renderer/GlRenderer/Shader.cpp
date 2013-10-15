//
//  Shader.cpp
//  Application
//
//  Created by Narendra Umate on 9/28/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#include "Shader.h"

GLuint Shader::LoadShader(GLenum eShaderType, const std::string &strShaderFilename)
{
    std::string strFilename = FindFileOrThrow(strShaderFilename);
    std::ifstream shaderFile(strFilename.c_str());
    std::stringstream shaderData;
    shaderData << shaderFile.rdbuf();
    shaderFile.close();

    try {
        return CreateShader(eShaderType, shaderData.str().c_str());
    } catch(std::exception &e) {
        fprintf(stderr, "%s\n", e.what());
        throw;
    }
}

GLuint Shader::CreateShader(GLenum shader_type, const char *shader_string)
{
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_string, NULL);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint log_len;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);
        GLchar *log_str = new GLchar[log_len + 1];
        glGetProgramInfoLog(shader, log_len, NULL, log_str);

        const char *shader_type_str = NULL;
        switch(shader_type) {
            case GL_VERTEX_SHADER:   shader_type_str = "vertex"; break;
				//            case GL_GEOMETRY_SHADER: shader_type_str = "geometry"; break;
            case GL_FRAGMENT_SHADER: shader_type_str = "fragment"; break;
        }

        fprintf(stderr, "Compile failure in %s shader:\n%s\n",
				shader_type_str, log_str);
    }
    return shader;
}

GLuint Shader::CreateProgram(const std::vector<GLuint> &shader_list)
{
    GLuint program = glCreateProgram();

    for (std::vector<GLuint>::const_iterator shader = shader_list.begin(); shader != shader_list.end(); shader++)
        glAttachShader(program, *shader);

    glLinkProgram(program);

    GLint status;
    glGetProgramiv (program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint log_len;
        glGetShaderiv(program, GL_INFO_LOG_LENGTH, &log_len);
        GLchar *log_str = new GLchar[log_len + 1];
        glGetProgramInfoLog(program, log_len, NULL, log_str);
        fprintf(stderr, "Linker failure: %s\n", log_str);
    }

    for (std::vector<GLuint>::const_iterator shader = shader_list.begin(); shader != shader_list.end(); shader++)
        glDetachShader(program, *shader);

    return program;
}

std::string Shader::FindFileOrThrow(const std::string &strBasename)
{
    std::string strFilename = LOCAL_FILE_DIR + strBasename;
    std::ifstream testFile(strFilename.c_str());
    if(testFile.is_open())
        return strFilename;


    strFilename = GLOBAL_FILE_DIR + strBasename;
    testFile.open(strFilename.c_str());
    if(testFile.is_open())
        return strFilename;

    throw std::runtime_error("Could not find the file " + strBasename);
}
