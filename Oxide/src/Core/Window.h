#pragma once
#include <memory>
#include <string>

namespace Oxide {
	struct WindowData {
		std::string m_windowTitle = "Oxide Window";
		uint32_t m_windowWidth = 1200;
		uint32_t m_windowHeight = (9.0/16.0) * m_windowWidth;
		bool m_canResize = false;
	};

	class Window {
	public:
		static std::shared_ptr<Window> create(WindowData data);
		virtual void onInit() = 0;
		virtual void onUpdate() = 0;
		virtual void onDestroy() = 0;
		virtual uint32_t getWidth() = 0;
		virtual uint32_t getHeight() = 0;
		virtual std::string getTitle() = 0;
		virtual bool isWindowClosed() = 0;
		virtual ~Window() = default;
	protected:
		Window() = default;
	};
}