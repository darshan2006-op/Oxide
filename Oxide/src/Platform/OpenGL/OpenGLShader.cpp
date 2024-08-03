#include "OpenGLShader.h"
#include "Logging/logger.h"
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

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

	OpenGLShader::OpenGLShader(): m_id(0), m_shaders(), m_cached()
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
	void OpenGLShader::Mat4(const char* name, glm::mat4& mat)
	{
		auto id = getUniformId(name);
		glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(mat));
	}
	void OpenGLShader::Int(const char* name, int value)
	{
		auto id = getUniformId(name);
		glUniform1i(id, value);
	}
	void OpenGLShader::Float(const char* name, float value)
	{
		auto id = getUniformId(name);
		glUniform1f(id, value);
	}
	void OpenGLShader::Float2(const char* name, glm::vec2 v2)
	{
		auto id = getUniformId(name);
		glUniform2fv(id, 1, glm::value_ptr(v2));
	}
	void OpenGLShader::Float3(const char* name, glm::vec3 v3)
	{
		auto id = getUniformId(name);
		glUniform3fv(id, 1, glm::value_ptr(v3));
	}
	void OpenGLShader::Float4(const char* name, glm::vec4 v4)
	{
		auto id = getUniformId(name);
		glUniform4fv(id, 1, glm::value_ptr(v4));
	}
	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_id);
	}
	uint32_t OpenGLShader::getUniformId(const char* name)
	{
		if (m_cached.count(name) == 0) m_cached[name] = glGetUniformLocation(m_id, name);
		return m_cached.at(name);
	}
}