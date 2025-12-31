#include "Renderer.h"
#include <glad/glad.h>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>
#include <Shader/Shader.h>
#include "Render/IndexBuffer.h"
#include "Render/VertexBuffer.h"

namespace Core {
	Renderer::Renderer() : m_VAO(0), m_VBO(0),m_IBO(0) {}
	Renderer::~Renderer() {
		//should be moved to other files 
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
	}
	void Renderer::Init() {
		//VAO
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);
		// VBO 
		//VertexBuffer vbo(vertices, sizeof(float) * 12);
		//glGenBuffers(1, &m_VBO);
		//glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vertices, GL_STATIC_DRAW);

		//tells opengl how to interpt the data on VBO
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		//glEnableVertexAttribArray(0);
		//index buffer 
		//IndexBuffer ibo(indecies, 6);
		//glGenBuffers(1, &m_IBO);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_IBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indecies, GL_STATIC_DRAW); 

		//shaders
		Shader::ShaderProgramSources source= Shader::ParseShader("../Core/res/Shaders/Basic.shader");
		unsigned int shaderProgram =Shader::CreateShader(source.VertexSource, source.FragmentSource);
		glUseProgram(shaderProgram);
		//uniforms 
		int location = glGetUniformLocation(shaderProgram, "u_Color");
		glUniform4f(location, 0.8, 0.1, 0.2, 1.0);
		std::cout << "Renderer initialized.\n";
	}
	void Renderer::Clear() {
		glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void Renderer::Draw() {
		//glBindVertexArray(m_VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	}
	
	

}