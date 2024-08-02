#pragma once
#include "Core/Window.h"
#include "Core/Application.h"

struct GLFWwindow;

namespace Oxide {
	class WindowsWindow: public Window {
	public:
		WindowsWindow(WindowData data);
		virtual void onInit() override;
		virtual void onUpdate() override;
		virtual void onDestroy() override;
		virtual void* getNativeWindow() override { return m_window; };
		virtual uint32_t getWidth() override { return m_windowData.m_windowWidth; }
		virtual uint32_t getHeight() override { return m_windowData.m_windowHeight; }
		virtual std::string getTitle() override { return m_windowData.m_windowTitle; }
		virtual bool isWindowClosed() override;
		~WindowsWindow();
	private:
		std::shared_ptr<Application> m_app;
		WindowData m_windowData;
		GLFWwindow* m_window;
	};
}