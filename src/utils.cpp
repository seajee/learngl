#include "utils.h"

#include <iostream>
#include <fstream>
#include <sstream>

std::string learngl::utils::ReadFile(const char* filePath)
{
    std::string content;

    std::ifstream file;

    file.exceptions(std::ifstream::badbit | std::ifstream::failbit);

    try {
        file.open(filePath);

        std::stringstream stream;
        stream << file.rdbuf();

        file.close();

        content = stream.str();
    } catch (std::ifstream::failure const& e) {
        std::cerr << "ERROR: Error while reading file \"" << filePath << "\"" << std::endl;
    }

    return content;
}