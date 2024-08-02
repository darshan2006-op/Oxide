#pragma once
#include <inttypes.h>
#include "RenderingApi.h"
namespace Oxide {
	class Renderer {
	public:
		static void setClearColour(float r, float g, float b, float a);
		static void setClearColour(uint32_t color);
		static void clear();
		static void setReneringApi(RenderingApis api);
		static RenderingApis getCurrentRenderingApi();
	private:
		Renderer() = default;
	};
}