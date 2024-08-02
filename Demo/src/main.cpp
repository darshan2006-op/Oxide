#include <iostream>
#include "Core/Application.h"
#include "Renderer/GraphicalContext.h"
#include "Core/Window.h"
#include "Logging/logger.h"

class App : public Oxide::Application {
public:
	void onInit() override {
		OX_CLIENT_INFO("initializing")
		Oxide::WindowData data;
		m_window = Oxide::Window::create(data);
		m_window->onInit();
		m_graphicalContext = Oxide::GraphicalContext::create(m_window);
		m_graphicalContext->init();
		m_closeFlag = false;
	}

	void onUpdate() override {
		m_window->onUpdate();
		m_graphicalContext->swapBuffers();
		if (m_window->isWindowClosed())
			m_closeFlag = true;
	}

	void onDestroy() override {
		OX_CLIENT_INFO("Destroyed")
		m_window->onDestroy();
	}

	bool shouldApplicationClose() override {
		return m_closeFlag;
	}
private:
	bool m_closeFlag;
	std::shared_ptr<Oxide::Window> m_window;
	std::shared_ptr<Oxide::GraphicalContext> m_graphicalContext;
};

std::shared_ptr<Oxide::Application> Oxide::getApplicationInterface() {
	return std::shared_ptr<Oxide::Application>(new App());
}