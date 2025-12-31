#include "Core/Core.h"
#include <Core/Window.h>
#include <iostream>
#include "Core/Renderer.h"
#include "Render/VertexBuffer.h"
#include "Render/IndexBuffer.h"

#include <filesystem>

int main()
{
    try
    {
        std::cout << std::filesystem::current_path() << std::endl;
        Core::Window window(1280, 720, "2d Engine");
        Core::Renderer renderer;
        renderer.Init();
     
        float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
        };
        unsigned int indecies[] = {
            0,1,2,
            2,3,0
        };

        Core::VertexBuffer vbo(vertices, sizeof(float) * 12);
        Core::IndexBuffer ibo(indecies, 6);


        while (!window.ShouldClose())
        {
            renderer.Clear();
            renderer.Draw();

            window.PollEvents();
            window.SwapBuffers();
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}