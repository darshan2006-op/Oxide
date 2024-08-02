#pragma once
#include "Core/Window.h"

extern struct GLFWwindow;

namespace Oxide {
	class WindowsWindow: public Window {
	public:
		WindowsWindow(WindowData data);
		virtual void onInit() override;
		virtual void onUpdate() override;
		virtual void onDestroy() override;
		virtual uint32_t getWidth() override { return m_windowData.m_windowWidth; }
		virtual uint32_t getHeight() override { return m_windowData.m_windowHeight; }
		virtual std::string getTitle() override { return m_windowData.m_windowTitle; }
		virtual bool isWindowClosed() override;
		~WindowsWindow();
	private:
		WindowData m_windowData;
		GLFWwindow* m_window;
	};
}