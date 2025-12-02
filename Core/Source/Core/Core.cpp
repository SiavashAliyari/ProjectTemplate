#include "Core.h"
#include <iostream>
#include <GLFW/glfw3.h>

namespace Core {

	void PrintHelloWorld()
	{
		int result =glfwInit();
		std::cout << result << std::endl;
		std::cout << "Hello World!\n";
		std::cin.get();
	}

}