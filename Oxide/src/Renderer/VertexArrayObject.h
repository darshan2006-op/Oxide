#pragma once
#include "IndexBuffer.h"
#include "VertexBuffer.h"

#include <vector>

namespace Oxide {
	enum class VertexAttributeTypes {
		Int, 
		Float, Float2, Float3, Float4,
	};

	struct Attributes {
		std::vector<VertexAttributeTypes> m_types;
		size_t m_stride = 0;

		void addAttribute(VertexAttributeTypes type) {
			m_types.push_back(type);
			m_stride += getTypeSize(type);
		}

		static size_t getTypeSize(VertexAttributeTypes type) {
			switch (type)
			{
			case Oxide::VertexAttributeTypes::Int:
				return sizeof(int) * 1;
				break;
			case Oxide::VertexAttributeTypes::Float:
				return sizeof(float) * 1;
				break;
			case Oxide::VertexAttributeTypes::Float2:
				return sizeof(float) * 2;
				break;
			case Oxide::VertexAttributeTypes::Float3:
				return sizeof(float) * 3;
				break;
			case Oxide::VertexAttributeTypes::Float4:
				return sizeof(float) * 4;
				break;
			default:
				break;
			}
		}
	};

	class VertexArrayObject {
	public:
		static std::shared_ptr<VertexArrayObject> create();
		virtual void destroy() = 0;
		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer, Attributes& attr) = 0;
		virtual void use() = 0;
		virtual ~VertexArrayObject() = default;
	protected:
		VertexArrayObject() = default;
	};
}