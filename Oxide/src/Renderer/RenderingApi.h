#pragma once

namespace Oxide {
	enum class RenderingApis {
		Vulkan, Opengl
	};

	RenderingApis g_currentApi = RenderingApis::Opengl;
}