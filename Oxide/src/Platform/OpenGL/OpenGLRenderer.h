#pragma once
#include "Renderer/Renderer.h"

namespace Oxide {
	class OpenGLRenderer {
	public:
		static void setClearColour(float r, float g, float b, float a);
		static void setClearColour(uint32_t color);
		static void clear();
	};
}