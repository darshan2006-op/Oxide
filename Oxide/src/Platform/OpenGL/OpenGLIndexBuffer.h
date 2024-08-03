#pragma once
#include "Renderer/IndexBuffer.h"

namespace Oxide {
	class OpenGLIndexBuffer: public IndexBuffer {
	public:
		OpenGLIndexBuffer();
		virtual void destroy() override;
		virtual void addData(void* data, size_t size) override;
		virtual void use() override;
		virtual ~OpenGLIndexBuffer();
	private:
		uint32_t m_id;
	};
}