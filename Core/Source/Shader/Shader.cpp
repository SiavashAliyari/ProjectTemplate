#include <Shader/Shader.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>


namespace Core {
	Shader::ShaderProgramSources Shader::ParseShader(const std::string& filepath) {
		std::ifstream stream(filepath);
		if (!stream.is_open()) {
			std::cerr << "FAILED TO OPEN SHADER FILE: " << filepath << std::endl;
			return {};
		}
		enum class ShaderType {
			NONE = -1, VERTEX = 0, FRAGMENT = 1
		};

		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;

		while (std::getline(stream, line)) {
			if (line.find("#shader") != std::string::npos) {
				//shader block found 
				if (line.find("vertex") != std::string::npos) {
					type = ShaderType::VERTEX;
				}
				else if (line.find("fragment") != std::string::npos) {
					type = ShaderType::FRAGMENT;
				}
			}
			else {
				if (type != ShaderType::NONE) {
					ss[(int)type] << line << '\n';
				}
			}

		}
		return{ ss[0].str(),ss[1].str() };
	}


	unsigned int Shader::CompileShader(unsigned int type, const std::string source) {
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		//Error handling 
		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			//Shader did not compile 

			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			const char* typeMessage = (type == GL_VERTEX_SHADER ? "vertex" : "fragment");
			std::cout << typeMessage << "failed to compile shader" << std::endl;
			std::cout << message << std::endl;
			glDeleteShader(id);
			return 0;
		}
		return id;
	}
	unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
		unsigned int program = glCreateProgram();
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}
	void Shader::DeleteShader(unsigned int& shaderProgram) {
		glDeleteProgram(shaderProgram);
	}

}