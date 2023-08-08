#pragma once

#include <cstdint>
#include <string>

namespace learngl
{
    class Shader
    {
    public:
        Shader(const char* vertex_path, const char* fragment_path);
        ~Shader();

        // Activate the shader
        void use();

        // Utility uniform functions
        void set_bool(const std::string& name, bool value);
        void set_int(const std::string& name, int32_t value);
        void set_float(const std::string& name, float value);

    private:
        uint32_t m_id;
    };
}