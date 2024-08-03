#pragma once
#include "Renderer/Renderer.h"

namespace Oxide {
	class OpenGLRenderer {
	public:
		static void setClearColour(float r, float g, float b, float a);
		static void setClearColour(uint32_t color);
		static void clear();
		static void Draw(const std::shared_ptr<VertexArrayObject>& vao, const std::shared_ptr<IndexBuffer>& ib, const std::shared_ptr<Shader>& shader, uint32_t count);
	};
}