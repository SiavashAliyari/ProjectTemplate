#pragma once

namespace Core {
	class VertexBuffer {
	public:
		VertexBuffer(const void* data,unsigned int size);
		~VertexBuffer();
		void Bind() const;
		void UnBind() const;
		unsigned int GetID();
	private:
		unsigned int m_RendererID;
	};
}