#pragma once
#include "Renderer/Shader.h"

#include <vector>
#include <map>

namespace Oxide {
	class OpenGLShader: public Shader {
	public:
		OpenGLShader();
		virtual void addShader(ShaderType type, std::string_view src) override;
		virtual void compile() override;
		virtual void use() override;
		virtual void Mat4(const char* name, glm::mat4& mat) override;
		virtual void Int(const char* name, int value) override;
		virtual void Float(const char* name, float value) override;
		virtual void Float2(const char* name, glm::vec2 v2) override;
		virtual void Float3(const char* name, glm::vec3 v3) override;
		virtual void Float4(const char* name, glm::vec4 v4) override;
		virtual ~OpenGLShader();
	protected:
		uint32_t getUniformId(const char* name);
		uint32_t m_id;
		std::vector<uint32_t> m_shaders;
		std::map<const char*, uint32_t> m_cached;
	};
}