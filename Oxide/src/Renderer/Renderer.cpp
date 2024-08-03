#include "Renderer.h"
#include "RenderingApi.h"
#include "Logging/logger.h"
#include "Platform/OpenGL/OpenGLRenderer.h"

namespace Oxide {
	void Renderer::setClearColour(float r, float g, float b, float a)
	{
		switch (getCurrentRenderingApi())
		{
		case Oxide::RenderingApis::Vulkan: {
			OX_CORE_ERROR("Vulkan Not Supported")
				break;
		}
		case Oxide::RenderingApis::Opengl: {
			OpenGLRenderer::setClearColour(r, g, b, a);
			break;
		}
		default: {
			OX_CORE_ERROR("Unknown Api")
			break;
		}
		}
	}
	void Renderer::setClearColour(uint32_t color)
	{
		switch (getCurrentRenderingApi())
		{
		case Oxide::RenderingApis::Vulkan: {
			OX_CORE_ERROR("Vulkan Not Supported")
				break;
		}
		case Oxide::RenderingApis::Opengl: {
			OpenGLRenderer::setClearColour(color);
			break;
		}
		default: {
			OX_CORE_ERROR("Unknown Api")
			break;
		}
		}
	}
	void Renderer::clear()
	{
		switch (getCurrentRenderingApi())
		{
		case Oxide::RenderingApis::Vulkan: {
			OX_CORE_ERROR("Vulkan Not Supported")
			break;
		}
		case Oxide::RenderingApis::Opengl: {
			OpenGLRenderer::clear();
			break;
		}
		default: {
			OX_CORE_ERROR("Unknown Api")
			break;
		}
		}
	}
	void Renderer::setRenderingApi(RenderingApis api)
	{
		g_currentApi = api;
	}
	RenderingApis Renderer::getCurrentRenderingApi()
	{
		return g_currentApi;
	}
	void Renderer::Draw(const std::shared_ptr<VertexArrayObject>& vao, const std::shared_ptr<IndexBuffer>& ib, const std::shared_ptr<Shader>& shader, uint32_t count)
	{
		switch (getCurrentRenderingApi())
		{
		case Oxide::RenderingApis::Vulkan: {
			OX_CORE_ERROR("Vulkan Not Supported")
			break;
		}
		case Oxide::RenderingApis::Opengl: {
			OpenGLRenderer::Draw(vao, ib, shader, count);
			break;
		}
		default: {
			OX_CORE_ERROR("Unknown Api")
			break;
		}
		}
	}
}