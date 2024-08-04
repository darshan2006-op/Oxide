#include "Renderer2D.h"
#include "Logging/logger.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Renderer/Renderer.h"

#include <fstream>
#include <sstream>

namespace Oxide {
	Renderer2D Renderer2D::s_renderer;

	static glm::vec3 rotateZ(glm::vec3& pos, float angle) {
		glm::vec3 rotated;
		rotated.x = pos.x * glm::cos(angle) - pos.y * glm::sin(angle);
		rotated.y = pos.x * glm::sin(angle) + pos.y * glm::cos(angle);
		rotated.z = pos.z;
		return rotated;
	}

	static glm::vec3 quadPos[] = {
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3( 0.5f, -0.5f, 0.0f),
		glm::vec3( 0.5f,  0.5f, 0.0f),
		glm::vec3(-0.5f,  0.5f, 0.0f),
	};

	static std::string readFile(const char* path) {
		std::ifstream file(path);
		if (!file.is_open()) {
			OX_CLIENT_CRITICAL("Unable to open the file path %s", path);
			return "";
		}
		std::stringstream ss;
		std::string line = "";

		ss << file.rdbuf();

		return ss.str();
	}

	void Renderer2D::init()
	{
		std::string vsrc = readFile("res/vert2d.glsl");
		std::string fsrc = readFile("res/frag2d.glsl");

		s_renderer.m_data.m_shader = Shader::create();
		s_renderer.m_data.m_shader->addShader(ShaderType::VertexShader, vsrc);
		s_renderer.m_data.m_shader->addShader(ShaderType::FragmentShader, fsrc);
		s_renderer.m_data.m_shader->compile();

		s_renderer.m_data.m_ib = IndexBuffer::create();
		s_renderer.m_data.m_vb = VertexBuffer::create();
		s_renderer.m_data.m_vao = VertexArrayObject::create();

		Attributes attrs;
		attrs.addAttribute(VertexAttributeTypes::Float3);
		attrs.addAttribute(VertexAttributeTypes::Float3);
		s_renderer.m_data.m_vao->addVertexBuffer(s_renderer.m_data.m_vb, attrs);
		
	}
	void Renderer2D::setViewportHeight(glm::vec2& size)
	{
		s_renderer.m_data.m_proj = glm::ortho(-size.x / 2.0f, +size.x / 2.0f, -size.y / 2.0f, +size.y / 2.0f, -1.0f, 1.0f);
	}
	void Renderer2D::drawQuad(glm::vec3& pos, glm::vec2& scale, float angle, glm::vec3& colour, glm::vec3& origin) {
		VertexData2D vertex;
		float a = glm::radians(angle);
		{
			vertex.pos = rotateZ(quadPos[0] * glm::vec3(scale, 1.0f) + origin, a) + pos;
			vertex.color = colour;
			s_renderer.m_data.m_vertices.push_back(vertex);
		}

		{
			vertex.pos = rotateZ(quadPos[1] * glm::vec3(scale, 1.0f) + origin, a)  + pos;
			s_renderer.m_data.m_vertices.push_back(vertex);
		}

		{
			vertex.pos = rotateZ(quadPos[2] * glm::vec3(scale, 1.0f) + origin, a)  + pos;
			s_renderer.m_data.m_vertices.push_back(vertex);
		}

		{
			vertex.pos = rotateZ(quadPos[3] * glm::vec3(scale, 1.0f) + origin, a) + pos;
			s_renderer.m_data.m_vertices.push_back(vertex);
		}

		uint32_t size = s_renderer.m_data.m_renderedVertices;
		s_renderer.m_data.m_indices.push_back(size + 0);
		s_renderer.m_data.m_indices.push_back(size + 1);
		s_renderer.m_data.m_indices.push_back(size + 2);
		s_renderer.m_data.m_indices.push_back(size + 2);
		s_renderer.m_data.m_indices.push_back(size + 3);
		s_renderer.m_data.m_indices.push_back(size + 0);

		s_renderer.m_data.numIndices += 6;
		s_renderer.m_data.numVertices += 4;
		s_renderer.m_data.m_renderedVertices += 4;
		s_renderer.m_data.numQuads += 4;

		if (s_renderer.m_data.m_vertices.size() >= s_renderer.m_data.numMaxVertices && s_renderer.m_data.m_indices.size() >= s_renderer.m_data.numMaxIndices) {
			flush();
		}
	}
	void Renderer2D::flush() {
		s_renderer.m_data.m_vb->addData(s_renderer.m_data.m_vertices.data(), s_renderer.m_data.m_vertices.size() * sizeof(VertexData2D));
		s_renderer.m_data.m_ib->addData(s_renderer.m_data.m_indices.data(), s_renderer.m_data.m_indices.size() * sizeof(uint32_t));
		s_renderer.m_data.m_shader->use();
		s_renderer.m_data.m_shader->Mat4("u_proj", s_renderer.m_data.m_proj);
		Renderer::Draw(s_renderer.m_data.m_vao, s_renderer.m_data.m_ib, s_renderer.m_data.m_shader, s_renderer.m_data.m_indices.size());

		s_renderer.m_data.m_vertices.clear();
		s_renderer.m_data.m_vertices.resize(0);

		s_renderer.m_data.m_indices.clear();
		s_renderer.m_data.m_indices.resize(0);

		s_renderer.m_data.m_renderedVertices = 0;

		s_renderer.m_data.numDrawCalls++;
	}
	void Renderer2D::begin()
	{
		s_renderer.m_data.numIndices = 0;
		s_renderer.m_data.numVertices = 0;
		s_renderer.m_data.numQuads = 0;

		s_renderer.m_data.m_vertices.clear();
		s_renderer.m_data.m_vertices.resize(0);

		s_renderer.m_data.m_indices.clear();
		s_renderer.m_data.m_indices.resize(0);
	}
	void Renderer2D::draw(glm::vec3& pos, glm::vec2& scale, glm::vec3& colour)
	{
		s_renderer.drawQuad(pos, scale, 0.0f, colour, glm::vec3(0.0f, 0.0f, 0.0f));
	}
	void Renderer2D::draw(glm::vec3& pos, glm::vec2& scale, float angle, glm::vec3& colour)
	{
		s_renderer.drawQuad(pos, scale, angle, colour, glm::vec3(0.0f, 0.0f, 0.0f));
	}
	void Renderer2D::draw(glm::vec3& pos, glm::vec2& scale, float angle, glm::vec3& colour, glm::vec3& origin)
	{
		s_renderer.drawQuad(pos, scale, angle, colour, origin);
	}
	void Renderer2D::end()
	{
		s_renderer.flush();
	}
}