#pragma once
#include "Core/Window.h"

namespace Oxide {
	class GraphicalContext {
	public:
		static std::shared_ptr<GraphicalContext> create(const std::shared_ptr<Window>& window);
		virtual void init() = 0;
		virtual void swapBuffers() = 0;
	protected:
		GraphicalContext() = default;
	};
}