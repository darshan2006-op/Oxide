#include "GraphicalContext.h"
#include "Renderer/Renderer.h"
#include "Logging/logger.h"
#include "Platform/OpenGL/OpenGLGraphicalContext.h"

namespace Oxide {
	std::shared_ptr<GraphicalContext> GraphicalContext::create(const std::shared_ptr<Window>& window)
	{
		switch (Renderer::getCurrentRenderingApi())
		{
		case Oxide::RenderingApis::Vulkan: {
			OX_CORE_ERROR("Vulkan is Not Supported")
			return nullptr;
			break;
		}
		case Oxide::RenderingApis::Opengl: {
			return std::shared_ptr<GraphicalContext>(new OpenGLGraphicalContext(window));
			break;
		}
		default: {
			OX_CORE_ERROR("Unknown Api")
			return nullptr;
			break;
		}
		}
	}
}