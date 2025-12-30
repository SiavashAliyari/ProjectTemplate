#include "Core/Core.h"
#include <Core/Window.h>
#include <iostream>
#include "Core/Renderer.h"
#include <filesystem>

int main()
{
    try
    {
        std::cout << std::filesystem::current_path() << std::endl;
        Core::Window window(1280, 720, "2d Engine");
        Core::Renderer renderer;
        unsigned int shaderProgram=0;

        renderer.Init(shaderProgram);


        while (!window.ShouldClose())
        {
            renderer.Clear();
            renderer.Draw(shaderProgram);

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