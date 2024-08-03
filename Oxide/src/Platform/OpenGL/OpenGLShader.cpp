#include "OpenGLShader.h"
#include "Logging/logger.h"
#include "glad/glad.h"

namespace Oxide {
	static uint32_t getShaderType(ShaderType type) {
		switch (type)
		{
		case Oxide::ShaderType::VertexShader: {
			return GL_VERTEX_SHADER;
			break;
		}
		case Oxide::ShaderType::FragmentShader: {
			return GL_FRAGMENT_SHADER;
			break;
		}
		default: {
			return 0;
			break;
		}
		}
	}

	OpenGLShader::OpenGLShader(): m_id(0), m_shaders()
	{
		m_id = glCreateProgram();
	}
	void OpenGLShader::addShader(ShaderType type, std::string_view src)
	{
		uint32_t id = glCreateShader(getShaderType(type));
		const char* data = src.data();
		glShaderSource(id, 1, &data, nullptr);
		glCompileShader(id);

		int success = 0;
		char infoLog[512];
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(id, 512, NULL, infoLog);
			OX_CORE_ERROR("Failed To Compile Shader, Error: {}", infoLog)
		};

		m_shaders.push_back(id);
	}
	void OpenGLShader::compile()
	{
		for (auto& shader : m_shaders) {
			glAttachShader(m_id, shader);
		}
		glLinkProgram(m_id);

		char infoLog[512];
		int success = 0;
		glGetProgramiv(m_id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_id, 512, NULL, infoLog);
			OX_CORE_ERROR("Failed to Link Program, Error: {}", infoLog)
		}

		for (auto& shader : m_shaders) {
			glDeleteShader(shader);
		}
	}
	void OpenGLShader::use()
	{
		glUseProgram(m_id);
	}
	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_id);
	}
}