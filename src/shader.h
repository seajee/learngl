#pragma once

#include <cstdint>
#include <string>

namespace learngl
{
    class Shader
    {
    public:
        Shader(const char* vertexPath, const char* fragmentPath);
        ~Shader();

        // Activate the shader
        void Use();

        // Utility uniform functions
        void SetBool(const std::string& name, bool value);
        void SetInt(const std::string& name, int32_t value);
        void SetFloat(const std::string& name, float value);

    private:
        uint32_t m_ShaderProgramId = 0;
    };
}