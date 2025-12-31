#include "Render/VertexBuffer.h"
#include <glad/glad.h>
namespace Core {
	
	VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size , data, GL_STATIC_DRAW);

		// vertex attrib
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}
	VertexBuffer::~VertexBuffer() {
		glDeleteBuffers(1, &m_RendererID);
	}
	void VertexBuffer::Bind() const{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}
	void VertexBuffer::UnBind() const{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	unsigned int VertexBuffer::GetID() {
		return m_RendererID;
	}
}