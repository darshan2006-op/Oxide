#include "WindowsWindow.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Logging/logger.h"

#include <stdexcept>


namespace Oxide {
	WindowsWindow::WindowsWindow(WindowData data): m_windowData(data), m_window(nullptr)
	{
		if (!glfwInit()) {
			OX_CORE_ERROR("Unable to initialize windowing framework(GLFW)")
		}
	}

	void WindowsWindow::onInit()
	{
		if (!m_windowData.m_canResize) {
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		}

		m_window = glfwCreateWindow(m_windowData.m_windowWidth, m_windowData.m_windowHeight, m_windowData.m_windowTitle.c_str(), nullptr, nullptr);

		if (!m_window) {
			glfwTerminate();
			OX_CORE_ERROR("Unable to create a window using windowing framework(GLFW)")
		}

	}

	void WindowsWindow::onUpdate()
	{
		glClearColor(0.8, 0.4, 0.8, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
	}

	void WindowsWindow::onDestroy()
	{
		glfwSetWindowShouldClose(m_window, 1);
	}

	bool WindowsWindow::isWindowClosed()
	{
		return glfwWindowShouldClose(m_window);
	}

	WindowsWindow::~WindowsWindow()
	{
		glfwTerminate();
	}
}