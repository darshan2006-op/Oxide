#pragma once
#include <memory>

namespace Oxide {
	class VertexBuffer {
	public:
		static std::shared_ptr<VertexBuffer> create();
		virtual void destroy() = 0;
		virtual void addData(void* data, size_t size) = 0;
		virtual void use() = 0;
		virtual ~VertexBuffer() = default;
	protected:
		VertexBuffer() = default;
	};
}