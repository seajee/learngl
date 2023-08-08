#include "shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>

learngl::Shader::Shader(const char* vertex_path, const char* fragment_path)
{
    std::string vertex_source;
    std::string fragment_source;

    std::ifstream v_file;
    std::ifstream f_file;

    v_file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    f_file.exceptions(std::ifstream::badbit | std::ifstream::failbit);

    // Read shader files
    try {
        v_file.open(vertex_path);
        f_file.open(fragment_path);

        std::stringstream v_stream;
        std::stringstream f_stream;

        v_stream << v_file.rdbuf();
        f_stream << f_file.rdbuf();

        v_file.close();
        f_file.close();

        vertex_source = v_stream.str();
        fragment_source = f_stream.str();
    } catch (std::ifstream::failure e) {
        std::cerr << "ERROR: Error while reading shader file" << std::endl;
    }

    // Compile shader files
    const char* v_code = vertex_source.c_str();
    const char* f_code = fragment_source.c_str();

    uint32_t vertex, fragment;
    int32_t success;
    char info_log[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &v_code, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, info_log);
        std::cerr << "ERROR: Failed to compile vertex shader" << std::endl << info_log << std::endl;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &f_code, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, info_log);
        std::cerr << "ERROR: Failed to compile fragment shader" << std::endl << info_log << std::endl;
    }

    // Create shader program and link shaders
    m_id = glCreateProgram();
    glAttachShader(m_id, vertex);
    glAttachShader(m_id, fragment);
    glLinkProgram(m_id);
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_id, 512, NULL, info_log);
        std::cerr << "ERROR: Failed to link shaders" << std::endl << info_log << std::endl;
    }

    // Finally, delete the shader objects as they're no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

learngl::Shader::~Shader()
{
    glDeleteShader(m_id);
}

void learngl::Shader::use()
{
    glUseProgram(m_id);
}

void learngl::Shader::set_bool(const std::string& name, bool value)
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int32_t)value);
}

void learngl::Shader::set_int(const std::string& name, int32_t value)
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void learngl::Shader::set_float(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}