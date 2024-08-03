#include "Shader.h"
#include "Logging/logger.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Oxide {
	std::shared_ptr<Shader> Shader::create()
	{
		switch (Renderer::getCurrentRenderingApi())
		{
		case RenderingApis::Vulkan: {
			OX_CORE_ERROR("Vulkan is not supported")
			return nullptr;
			break;
		}
		case RenderingApis::Opengl: {
			return std::make_shared<OpenGLShader>();
			break;
		}
		default: {
			OX_CORE_ERROR("Unknown rendering api")
			return nullptr;
			break;
		}
		}
	}
}