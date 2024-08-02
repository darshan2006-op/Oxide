#include "Renderer.h"
#include "RenderingApi.h"
#include "Logging/logger.h"
#include "Platform/OpenGL/OpenGLRenderer.h"

namespace Oxide {
	void Renderer::setClearColour(float r, float g, float b, float a)
	{
		switch (g_currentApi)
		{
		case Oxide::RenderingApis::Vulkan:
			OX_CORE_ERROR("Vulkan Not Supported")
			break;
		case Oxide::RenderingApis::Opengl:
			OpenGLRenderer::setClearColour(r, g, b, a);
			break;
		default:
			OX_CORE_ERROR("Unknown Api")
			break;
		}
	}
	void Renderer::setClearColour(uint32_t color)
	{
		switch (g_currentApi)
		{
		case Oxide::RenderingApis::Vulkan:
			OX_CORE_ERROR("Vulkan Not Supported")
				break;
		case Oxide::RenderingApis::Opengl:
			OpenGLRenderer::setClearColour(color);
			break;
		default:
			OX_CORE_ERROR("Unknown Api")
				break;
		}
	}
	void Renderer::clear()
	{
		switch (g_currentApi)
		{
		case Oxide::RenderingApis::Vulkan:
			OX_CORE_ERROR("Vulkan Not Supported")
				break;
		case Oxide::RenderingApis::Opengl:
			OpenGLRenderer::clear();
			break;
		default:
			OX_CORE_ERROR("Unknown Api")
				break;
		}
	}
	void Renderer::setReneringApi(RenderingApis api)
	{
		g_currentApi = api;
	}
	RenderingApis Renderer::getCurrentRenderingApi()
	{
		return g_currentApi;
	}
}