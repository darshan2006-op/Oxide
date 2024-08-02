#include "OpenGLGraphicalContext.h"
#include "glad/glad.h"
#include "Logging/logger.h"
#include "GLFW/glfw3.h"

namespace Oxide {
	OpenGLGraphicalContext::OpenGLGraphicalContext(const std::shared_ptr<Window>& window): m_nativeWindow(nullptr)
	{
		m_nativeWindow = (GLFWwindow*)window->getNativeWindow();
	}

	void OpenGLGraphicalContext::init()
	{
		glfwMakeContextCurrent(m_nativeWindow);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			OX_CORE_ERROR("Unable to initialize OpenGL")
		}
	}
	void OpenGLGraphicalContext::swapBuffers()
	{
		glfwSwapBuffers(m_nativeWindow);
	}
}