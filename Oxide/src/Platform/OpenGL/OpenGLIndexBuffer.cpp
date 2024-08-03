#include "OpenGLIndexBuffer.h"
#include "glad/glad.h"

namespace Oxide {
	OpenGLIndexBuffer::OpenGLIndexBuffer(): m_id(0)
	{
		glGenBuffers(1, &m_id);
	}
	void OpenGLIndexBuffer::destroy()
	{
		glDeleteBuffers(1, &m_id);
	}
	void OpenGLIndexBuffer::addData(void* data, size_t size)
	{
		use();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
	}
	void OpenGLIndexBuffer::use()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		if (m_id != 0) destroy();
	}
}