#include "Renderer.h"
#include <glad/glad.h>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>

namespace Core {
	Renderer::Renderer() : m_VAO(0), m_VBO(0), m_ShaderProgram(0),m_IBO(0) {}
	Renderer::~Renderer() {
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteProgram(m_ShaderProgram);
	}
	void Renderer::Init() {
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
		//VAO
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);
		// VBO 
		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vertices, GL_STATIC_DRAW);

		//tells opengl how to interpt the data on VBO
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		//index buffer 
		glGenBuffers(1, &m_IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indecies, GL_STATIC_DRAW); 

		//shaders
		Renderer::ShaderProgramSources source=ParseShader("../Core/res/Shaders/Basic.shader");
		m_ShaderProgram=CreateShader(source.VertexSource, source.FragmentSource);
		std::cout << "Renderer initialized.\n";
	}
	void Renderer::Clear() {
		glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void Renderer::Draw() {
		glUseProgram(m_ShaderProgram);	
		glBindVertexArray(m_VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	}
	unsigned int Renderer::CreateShader(const std::string& vertexShader,const std::string& fragmentShader) {
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
	unsigned int Renderer::CompileShader(unsigned int type, const std::string source) {
		unsigned int id=glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id,1,&src,nullptr);
		glCompileShader(id);

		//Error handling 
		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			//Shader did not compile 
			
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH,&length);

			char* message = (char*)alloca(length *sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			const char* typeMessage = (type == GL_VERTEX_SHADER ? "vertex" : "fragment");
			std::cout << typeMessage <<"failed to compile shader" << std::endl;
			std::cout << message << std::endl;
			glDeleteShader(id);
			return 0;
		}
		return id;
	}
	Renderer::ShaderProgramSources Renderer::ParseShader(const std::string& filepath) {
		std::ifstream stream(filepath);
		if (!stream.is_open()) {
			std::cerr << "FAILED TO OPEN SHADER FILE: " << filepath << std::endl;
			return {};
		}
		enum class ShaderType {
			NONE = -1, VERTEX = 0,FRAGMENT=1
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
		return{ss[0].str(),ss[1].str()};
	}

}