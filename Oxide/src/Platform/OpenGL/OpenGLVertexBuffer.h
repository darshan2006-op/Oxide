#pragma once
#include "Renderer/VertexBuffer.h"

namespace Oxide {
	class OpenGLVertexBuffer: public VertexBuffer {
	public:
		OpenGLVertexBuffer();
		virtual void destroy() override;
		virtual void addData(void* data, size_t size) override;
		virtual void use() override;
		virtual ~OpenGLVertexBuffer();
	private:
		uint32_t m_id;
	};
}