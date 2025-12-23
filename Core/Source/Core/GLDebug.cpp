#include "GLDebug.h"
#include <glad/glad.h>
#include <iostream>

static void APIENTRY GLDebugCallback(
    GLenum source, GLenum type, GLuint id, GLenum severity,
    GLsizei, const GLchar* message, const void*)
{
    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) return;

    std::cerr << "\n[OpenGL Debug] ID=" << id
        << " severity=" << severity
        << " type=" << type
        << "\n" << message << "\n\n";
}

namespace Core {
	void EnableGLDebugOutput() {
        if (!GLAD_GL_VERSION_4_3) {
            std::cout << "Opengl debug not available \n" << std::endl;
            return;
        }
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(GLDebugCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

	}
}