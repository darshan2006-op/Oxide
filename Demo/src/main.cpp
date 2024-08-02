#include <iostream>
#include "Core/Application.h"
#include "Renderer/GraphicalContext.h"
#include "Core/Window.h"
#include "Renderer/Renderer.h"
#include "Logging/logger.h"
#include "Events/Event.h"
#include "Events/KeyEvent.h"

class App;

static std::shared_ptr<App> g_application = nullptr;

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

		Oxide::Renderer::setClearColour(0xff88ffff);
	}

	void onUpdate() override {
		Oxide::Renderer::clear();

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

	virtual void onEvent(Oxide::Event& e) {
		Oxide::EventDispatcher dipatcher (e);
		dipatcher.Dispatch<Oxide::KeyPressedEvent>(&App::onKeyPessed);
	}

	static bool onKeyPessed(Oxide::KeyPressedEvent& e) {
		OX_CLIENT_INFO("KeyPressed");
		if(e.GetKeyCode() == Oxide::Key::Escape){
			g_application->m_closeFlag = true;
		}
		return true;
	}

private:
	bool m_closeFlag;
	std::shared_ptr<Oxide::Window> m_window;
	std::shared_ptr<Oxide::GraphicalContext> m_graphicalContext;
};

std::shared_ptr<Oxide::Application> Oxide::getApplicationInterface() {
	if (g_application == nullptr)
		g_application = std::shared_ptr<App>(new App());
	return g_application;
}