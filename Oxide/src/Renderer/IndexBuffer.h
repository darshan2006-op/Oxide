#pragma once
#include <memory>

namespace Oxide {
	class IndexBuffer {
	public:
		static std::shared_ptr<IndexBuffer> create();
		virtual void destroy() = 0;
		virtual void addData(void* data, size_t size) = 0;
		virtual void use() = 0;
		virtual ~IndexBuffer() = default;
	protected:
		IndexBuffer() = default;
	};
}