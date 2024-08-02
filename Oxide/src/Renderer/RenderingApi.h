#pragma once

namespace Oxide {
	enum class RenderingApis {
		Vulkan, Opengl
	};

	inline RenderingApis g_currentApi = RenderingApis::Opengl;
}