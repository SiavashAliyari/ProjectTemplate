#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>
#include "GLDebug.h"


namespace Core {

    Window::Window(int width, int height, const char* title)
    {
        if (!glfwInit())
            throw std::runtime_error("Failed to initialize GLFW");

        m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!m_Window)
        {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }

        glfwMakeContextCurrent(m_Window);
 
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            glfwDestroyWindow(m_Window);
            glfwTerminate();
            throw std::runtime_error("Failed to initialize GLAD!");
        }
        //Enable debugging for Opengl
        Core::EnableGLDebugOutput();
        std::cout<< "OpenGl version is: " << glGetString(GL_VERSION) << std::endl;
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    void Window::PollEvents()
    {
        glfwPollEvents();
    }

    bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(m_Window);
    }
    void Window::SwapBuffers() {
        glfwSwapBuffers(m_Window);

    }

}