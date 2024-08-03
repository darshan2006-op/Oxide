#pragma once
#include "Renderer/Shader.h"

#include <vector>

namespace Oxide {
	class OpenGLShader: public Shader {
	public:
		OpenGLShader();
		virtual void addShader(ShaderType type, std::string_view src) override;
		virtual void compile() override;
		virtual void use() override;
		virtual ~OpenGLShader();
	protected:
		uint32_t m_id;
		std::vector<uint32_t> m_shaders;
	};
}