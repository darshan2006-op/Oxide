#include "IndexBuffer.h"
#include "Logging/logger.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"

namespace Oxide {
	std::shared_ptr<IndexBuffer> IndexBuffer::create()
	{
		switch (Renderer::getCurrentRenderingApi())
		{
		case RenderingApis::Vulkan: {
			OX_CORE_ERROR("Vulkan is not supported")
			return nullptr;
			break;
		}
		case RenderingApis::Opengl: {
			return std::make_shared<OpenGLIndexBuffer>();
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