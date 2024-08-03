#include "VertexBuffer.h"
#include "Renderer.h"
#include "Logging/logger.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"

namespace Oxide {
	std::shared_ptr<VertexBuffer> VertexBuffer::create()
	{
		switch (Renderer::getCurrentRenderingApi())
		{
		case RenderingApis::Vulkan: {
			OX_CORE_ERROR("Vulkan is not Supported")
			return nullptr;
			break;
		}
		case RenderingApis::Opengl: {
			return std::make_shared<OpenGLVertexBuffer>();
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