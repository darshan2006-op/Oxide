#include "Texture2D.h"
#include "Logging/logger.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"
#include "Renderer.h"

namespace Oxide {
	uint8_t Texture2D::s_texCount = 0;
	std::shared_ptr<Texture2D> Texture2D::create()
	{
		s_texCount++;
		switch (Renderer::getCurrentRenderingApi())
		{
		case RenderingApis::Vulkan:{
			OX_CORE_ERROR("Vulkan is not supported")
			return nullptr;
			break;
		}
		case RenderingApis::Opengl: {
			return std::make_shared<OpenGLTexture2D>();
			break;
		}
		default: {
			OX_CORE_ERROR("Unsupported Rendering Api")
			return nullptr;
			break;
		}
		}
	}
}