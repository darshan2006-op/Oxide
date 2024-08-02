#pragma once

#include "Renderer/GraphicalContext.h"

struct GLFWwindow;
namespace Oxide {
	class OpenGLGraphicalContext: public GraphicalContext {
	public:
		OpenGLGraphicalContext(const std::shared_ptr<Window>& window);
		virtual void init() override;
		virtual void swapBuffers() override;
	protected:
		GLFWwindow* m_nativeWindow;
	};
}