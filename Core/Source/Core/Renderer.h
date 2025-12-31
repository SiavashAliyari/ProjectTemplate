#pragma once
#include <iostream>

namespace Core {
	class Renderer {
	public:
		Renderer();
		~Renderer();
		void Init();
		void Clear();
		void Draw();
		
	private:
		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_IBO;

		
	};
}