#pragma once
#include <iostream>

namespace Core {
	class Renderer {
	public:
		Renderer();
		~Renderer();
		unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
		unsigned int CompileShader(unsigned int type, const std::string source);
		void Init();
		void Clear();
		void Draw();
		struct ShaderProgramSources {
			std::string VertexSource;
			std::string FragmentSource;
		};
	private:
		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_IBO;

		unsigned int m_ShaderProgram;
		ShaderProgramSources ParseShader(const std::string& filepath);
	};
}