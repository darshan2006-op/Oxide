#include "OpenGLVertexArrayObject.h"
#include "Logging/logger.h"
#include "glad/glad.h"

namespace Oxide {
	static uint32_t getCount(VertexAttributeTypes type) {
		switch (type)
		{
		case Oxide::VertexAttributeTypes::Int:
			return 1;
			break;
		case Oxide::VertexAttributeTypes::Float:
			return 1;
			break;
		case Oxide::VertexAttributeTypes::Float2:
			return 2;
			break;
		case Oxide::VertexAttributeTypes::Float3:
			return 3;
			break;
		case Oxide::VertexAttributeTypes::Float4:
			return 4;
			break;
		default:
			OX_CORE_ERROR("Unknown Attribute Type")
			return 0;
			break;
		}
	}

	static uint32_t getType(VertexAttributeTypes type) {
		switch (type)
		{
		case Oxide::VertexAttributeTypes::Int:
			return GL_INT;
			break;
		case Oxide::VertexAttributeTypes::Float:
		case Oxide::VertexAttributeTypes::Float2:
		case Oxide::VertexAttributeTypes::Float3:
		case Oxide::VertexAttributeTypes::Float4:
			return GL_FLOAT;
			break;
		default:
			break;
		}
	}

	OpenGLVertexArrayObject::OpenGLVertexArrayObject(): m_id(0), m_attributeId(0)
	{
		glGenVertexArrays(1, &m_id);
	}
	void OpenGLVertexArrayObject::destroy()
	{
		glDeleteVertexArrays(1, &m_id);
	}
	void OpenGLVertexArrayObject::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer, Attributes& attr)
	{
		use();
		vertexBuffer->use();

		size_t offset = 0;

		for (int i = 0; i < attr.m_types.size(); i++) {
			VertexAttributeTypes type = attr.m_types.at(i);

			glEnableVertexAttribArray(m_attributeId);
			glVertexAttribPointer(m_attributeId,
				getCount(type),
				getType(type), GL_FALSE,
				attr.m_stride, (const void*)offset);

			offset += Attributes::getTypeSize(type);
			m_attributeId++;
		}

	}
	void OpenGLVertexArrayObject::use()
	{
		glBindVertexArray(m_id);
	}
	OpenGLVertexArrayObject::~OpenGLVertexArrayObject()
	{
		if (m_id != 0) destroy();
	}
}