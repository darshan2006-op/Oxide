#include "VertexArrayObject.h"
#include "Logging/logger.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArrayObject.h"

namespace Oxide {
	std::shared_ptr<VertexArrayObject> VertexArrayObject::create()
	{
		switch (Renderer::getCurrentRenderingApi())
		{
		case RenderingApis::Vulkan: {
			OX_CORE_ERROR("Vulkan is not supported")
			return nullptr;
			break;
		}
		case RenderingApis::Opengl: {
			return std::make_shared<OpenGLVertexArrayObject>();
			break;
		}
		default: {
			return nullptr;
			OX_CORE_ERROR("Unknown rendering api")
				break;
		}
		}
	}
}