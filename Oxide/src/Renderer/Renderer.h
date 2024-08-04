#pragma once
#include "RenderingApi.h"
#include "VertexArrayObject.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture2D.h"

#include <inttypes.h>

namespace Oxide {
	class Renderer {
	public:
		static void setClearColour(float r, float g, float b, float a);
		static void setClearColour(uint32_t color);
		static void clear();
		static void setRenderingApi(RenderingApis api);
		static RenderingApis getCurrentRenderingApi();
		static void Draw(const std::shared_ptr<VertexArrayObject>& vao, const std::shared_ptr<IndexBuffer>& ib, const std::shared_ptr<Shader>& shader, uint32_t count);
		static void Draw(const std::shared_ptr<VertexArrayObject>& vao, const std::shared_ptr<IndexBuffer>& ib, const std::shared_ptr<Shader>& shader, 
			const std::shared_ptr<Texture2D>& text, uint32_t count);
	private:
		Renderer() = default;
	};
}