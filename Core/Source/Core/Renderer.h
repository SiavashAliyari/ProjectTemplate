#pragma once
#include <iostream>

namespace Core {
	class Renderer {
	public:
		Renderer();
		~Renderer();
		void Init(unsigned int& shaderProgram);
		void Clear();
		void Draw(unsigned int& shaderProgram);
		
	private:
		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_IBO;

		
	};
}