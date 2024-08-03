#pragma once
#include <memory>
#include <string>

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
		virtual ~Shader() = default;
	protected:
		Shader() = default;
	};
}