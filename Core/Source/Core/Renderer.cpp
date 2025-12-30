#include "Renderer.h"
#include <glad/glad.h>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>
#include <Shader/Shader.h>

namespace Core {
	Renderer::Renderer() : m_VAO(0), m_VBO(0),m_IBO(0) {}
	Renderer::~Renderer() {
		
		//should be moved to other files 
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
	}
	void Renderer::Init(unsigned int& shaderProgram) {
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
		Shader::ShaderProgramSources source= Shader::ParseShader("../Core/res/Shaders/Basic.shader");
		shaderProgram =Shader::CreateShader(source.VertexSource, source.FragmentSource);
		std::cout << "Renderer initialized.\n";
	}
	void Renderer::Clear() {
		glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void Renderer::Draw(unsigned int& shaderProgram) {
		glUseProgram(shaderProgram);
		glBindVertexArray(m_VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	}
	
	

}