#pragma once
#include <string>

namespace Core{
	class Shader {
	public:
		struct ShaderProgramSources {
			std::string VertexSource;
			std::string FragmentSource;
		};
		static ShaderProgramSources ParseShader(const std::string& filepath);
		static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
		static void DeleteShader(unsigned int& shaderProgram); 
	private:
		static unsigned int CompileShader(unsigned int type, const std::string source);
		unsigned int m_ShaderProgram;
	};

}