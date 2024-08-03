#pragma once
#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArrayObject.h"
#include "Renderer.h"
#include "glm/glm.hpp"

#include <vector>

namespace Oxide {
	class Renderer2D;
	
	struct VertexData2D {
		glm::vec3 pos;
		glm::vec3 color;
	};

	struct RendererData {
		uint32_t numQuads = 0;
		uint32_t numVertices = 0;
		uint32_t numIndices = 0;

		const uint32_t numMaxVertices = 4 * 200;
		const uint32_t numMaxIndices = 6 * 200;

		friend class Renderer2D;
	private:
		uint32_t m_renderedVertices = 0;
		//uint32_t m_renderedIndices = 0;
		glm::mat4 m_proj = glm::mat4(1.0f);
		std::vector<uint32_t> m_indices;
		std::vector<VertexData2D> m_vertices;
		std::shared_ptr<VertexBuffer> m_vb;
		std::shared_ptr<IndexBuffer> m_ib;
		std::shared_ptr<VertexArrayObject> m_vao;
		std::shared_ptr<Shader> m_shader;
	};

	class Renderer2D {
	public:
		static void init();
		static void setViewportHeight(glm::vec2& size);
		static void begin();
		static void draw(glm::vec3& pos, glm::vec2& scale, glm::vec3& colour);
		static void draw(glm::vec3& pos, glm::vec2& scale, float angle, glm::vec3& colour);
		static void end();
	private:
		void drawQuad(glm::vec3& pos, glm::vec2& scale, float angle, glm::vec3& colour);
		void flush();
		static Renderer2D s_renderer;
		RendererData m_data;
		Renderer2D() = default;
		~Renderer2D() = default;
	};
}