#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>
#include "GLDebug.h"
#include "Event/Event.h"
#include "Event/ApplicationEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"

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
        glfwSwapInterval(1);
        //Enable debugging for Opengl
        Core::EnableGLDebugOutput();
        std::cout<< "OpenGl version is: " << glGetString(GL_VERSION) << std::endl;

        m_Data.Width = width;
        m_Data.Height = height;
        glfwSetWindowUserPointer(m_Window, &m_Data);
        InitCallbacks();
        
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

    void Window::InitCallbacks()
    {
        // Window resize
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int w, int h)
        {
            auto& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = w;
            data.Height = h;

            WindowResizeEvent e((unsigned)w, (unsigned)h);
            if (data.EventCallback) data.EventCallback(e);
        });

        // Window close
        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
        {
            auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowCloseEvent e;
            if (data.EventCallback) data.EventCallback(e);
        });

        // Key input
        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/)
        {
            auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
            case GLFW_PRESS:
            {
                KeyPressedEvent e(key, 0);
                if (data.EventCallback) data.EventCallback(e);
                break;
            }
            case GLFW_RELEASE:
            {
                KeyReleasedEvent e(key);
                if (data.EventCallback) data.EventCallback(e);
                break;
            }
            case GLFW_REPEAT:
            {
                // GLFW doesn't give repeat count; Hazel often passes 1 for "repeated"
                KeyPressedEvent e(key, 1);
                if (data.EventCallback) data.EventCallback(e);
                break;
            }
            }
        });

        // Mouse button
        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int /*mods*/)
        {
            auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

            if (action == GLFW_PRESS)
            {
                MouseButtonPressedEvent e(button);
                if (data.EventCallback) data.EventCallback(e);
            }
            else if (action == GLFW_RELEASE)
            {
                MouseButtonReleasedEvent e(button);
                if (data.EventCallback) data.EventCallback(e);
            }
        });

        // Mouse move
        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y)
        {
            auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent e((float)x, (float)y);
            if (data.EventCallback) data.EventCallback(e);
        });

        // Mouse scroll
        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent e((float)xOffset, (float)yOffset);
            if (data.EventCallback) data.EventCallback(e);
        });
    }

}