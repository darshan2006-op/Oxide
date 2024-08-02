#include "WindowsWindow.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Logging/logger.h"
#include "Core/Application.h"
#include "Events/Event.h"
#include "Events/ApplicationEvents.h"
#include "Events/MouseEvents.h"
#include "Events/KeyEvent.h"

#include <string>
#include <sstream>
#include <stdexcept>

namespace Oxide {
	WindowsWindow::WindowsWindow(WindowData data): m_windowData(data), m_window(nullptr)
	{
		m_app = getApplicationInterface();
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
		glfwSetWindowUserPointer(m_window, &m_windowData);

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
			auto app = getApplicationInterface();
			WindowCloseEvent e = WindowCloseEvent();
			app->onEvent((Event&)e);
		});

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
			auto app = getApplicationInterface();
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.m_windowWidth = width;
			data.m_windowHeight = height;
			WindowResizeEvent e(width, height);
			app->onEvent((Event&)e);
		});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			auto app = getApplicationInterface();
			switch (action)
			{
			case GLFW_PRESS: {
				KeyPressedEvent pressed = KeyPressedEvent(key, false);
				app->onEvent((Event&)pressed);
				break;
			}
			case GLFW_RELEASE: {
				KeyReleasedEvent released = KeyReleasedEvent(key);
				app->onEvent((Event&)released);
				break;
			}
			case GLFW_REPEAT: {
				KeyPressedEvent repeat = KeyPressedEvent(key, true);
				app->onEvent((Event&)repeat);
				break;
			}
			default:
				break;
			}
			
		});

		glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int keycode)
			{
				auto app = getApplicationInterface();
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				KeyTypedEvent e(keycode);
				app->onEvent((Event&)e);
		});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
			{
				auto app = getApplicationInterface();
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent e(button);
					app->onEvent((Event&)e);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent e(button);
					app->onEvent((Event&)e);
					break;
				}
				}
		});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				auto app = getApplicationInterface();
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent e((float)xOffset, (float)yOffset);
				app->onEvent((Event&)e);
		});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos)
			{
				auto app = getApplicationInterface();
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent e((float)xPos, (float)yPos);
				app->onEvent((Event&)e);
		});
	}

	void WindowsWindow::onUpdate()
	{
		glfwPollEvents();
		AppUpdateEvent e = AppUpdateEvent();
		m_app->onEvent((Event&) e);
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