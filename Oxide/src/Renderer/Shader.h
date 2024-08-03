#pragma once
#include <memory>
#include <string>

#include "glm/glm.hpp"

namespace Oxide {
	enum class ShaderType {
		VertexShader, FragmentShader
	};

	class Shader {
	public:
		static std::shared_ptr<Shader> create();
		virtual void addShader(ShaderType type, std::string_view src) = 0;
		virtual void compile() = 0;
		virtual void use() = 0;
		virtual void Mat4(const char* name, glm::mat4& mat) = 0;
		virtual void Int(const char* name, int value) = 0;
		virtual void Float(const char* name, float value) = 0;
		virtual void Float2(const char* name, glm::vec2 v2) = 0;
		virtual void Float3(const char* name, glm::vec3 v3) = 0;
		virtual void Float4(const char* name, glm::vec4 v4) = 0;
		virtual ~Shader() = default;
	protected:
		Shader() = default;
	};
}