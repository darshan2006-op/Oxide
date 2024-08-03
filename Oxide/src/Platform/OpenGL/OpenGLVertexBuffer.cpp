#include "OpenGLVertexBuffer.h"
#include "glad/glad.h"

namespace Oxide {
	OpenGLVertexBuffer::OpenGLVertexBuffer(): m_id(0)
	{
		glGenBuffers(1, &m_id);
	}
	void OpenGLVertexBuffer::destroy()
	{
		glDeleteBuffers(1, &m_id);
	}
	void OpenGLVertexBuffer::addData(void* data, size_t size)
	{
		use();
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
	}
	void OpenGLVertexBuffer::use()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		if (m_id != 0) destroy();
	}
}