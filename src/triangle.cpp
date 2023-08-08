#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "shader.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define INFO_LOG_SIZE 512

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);

float vertices[] = {
    // positions          // colors
     0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, // bottom right
    -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f, // bottom left
     0.0f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f  // top
};

const char* vertex_shader_path = "./shaders/triangle/vertex.vert";
const char* fragment_shader_path = "./shaders/triangle/fragment.frag";

char info_log[INFO_LOG_SIZE];

int main()
{
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Initialize GLFW window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL", NULL, NULL);
    if (window == NULL) {
        std::cerr << "ERROR: Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Set the resize window callback function
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "ERROR: Failed to initialize GLAD" << std::endl;
        return -1;
    }

    learngl::Shader shader(vertex_shader_path, fragment_shader_path);

    // Generate the VBO and VAO
    uint32_t vbo, vao;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    // Bind the Vertex Array Object first, then bind and set vertex buffer and then configure vertex attributes
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); // Unbind to be sure that other VAO calls won't accidentally modify this VAO

    // Event loop
    while (!glfwWindowShouldClose(window)) {
        // Input
        process_input(window);

        // Rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw triangle
        shader.use();
        glBindVertexArray(vao); // Seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0); // No need to unbind it every time

        // Check and call events and swap buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // De-allocate resources and terminate
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    (void) window;
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}