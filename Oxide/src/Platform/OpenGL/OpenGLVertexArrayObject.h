#pragma once
#include "Renderer/VertexArrayObject.h"

namespace Oxide {
	class OpenGLVertexArrayObject: public VertexArrayObject{
	public:
		OpenGLVertexArrayObject();
		virtual void destroy() override;
		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer, Attributes& attr) override;
		virtual void use() override;
		virtual ~OpenGLVertexArrayObject();
	private:
		uint32_t m_id;
		uint32_t m_attributeId;
	};
}