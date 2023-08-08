#include "shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>

learngl::Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexSource;
    std::string fragmentSource;

    std::ifstream vFile;
    std::ifstream fFile;

    vFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    fFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);

    // Read shader files
    try {
        vFile.open(vertexPath);
        fFile.open(fragmentPath);

        std::stringstream vStream;
        std::stringstream fStream;

        vStream << vFile.rdbuf();
        fStream << fFile.rdbuf();

        vFile.close();
        fFile.close();

        vertexSource = vStream.str();
        fragmentSource = fStream.str();
    } catch (std::ifstream::failure const& e) {
        std::cerr << "ERROR: Error while reading shader file" << std::endl;
    }

    // Compile shader files
    const char* vCode = vertexSource.c_str();
    const char* fCode = fragmentSource.c_str();

    uint32_t vertex, fragment;
    int32_t success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cerr << "ERROR: Failed to compile vertex shader" << std::endl << infoLog << std::endl;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cerr << "ERROR: Failed to compile fragment shader" << std::endl << infoLog << std::endl;
    }

    // Create shader program and link shaders
    m_ShaderProgramId = glCreateProgram();
    glAttachShader(m_ShaderProgramId, vertex);
    glAttachShader(m_ShaderProgramId, fragment);
    glLinkProgram(m_ShaderProgramId);
    glGetProgramiv(m_ShaderProgramId, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_ShaderProgramId, 512, NULL, infoLog);
        std::cerr << "ERROR: Failed to link shaders" << std::endl << infoLog << std::endl;
    }

    // Finally, delete the shader objects as they're no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

learngl::Shader::~Shader()
{
    glDeleteShader(m_ShaderProgramId);
}

void learngl::Shader::Use()
{
    glUseProgram(m_ShaderProgramId);
}

void learngl::Shader::SetBool(const std::string& name, bool value)
{
    glUniform1i(glGetUniformLocation(m_ShaderProgramId, name.c_str()), (int32_t)value);
}

void learngl::Shader::SetInt(const std::string& name, int32_t value)
{
    glUniform1i(glGetUniformLocation(m_ShaderProgramId, name.c_str()), value);
}

void learngl::Shader::SetFloat(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(m_ShaderProgramId, name.c_str()), value);
}