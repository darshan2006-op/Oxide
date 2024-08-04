#include "Core/Application.h"
#include "Renderer/GraphicalContext.h"
#include "Core/Window.h"
#include "Renderer/Renderer.h"
#include "Logging/logger.h"
#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvents.h"
#include "Renderer/Renderer2D.h"
#include "Renderer/Camera2D.h"

#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>

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
		
		Oxide::Renderer2D::init();
		Oxide::Renderer2D::setViewportHeight(glm::vec2(data.m_windowWidth, data.m_windowHeight));

		m_cam = Oxide::Camera2D();

		m_camPos = m_cam.getCameraPosition();

		Oxide::Renderer::setClearColour(0x000000ff);
	}

	void onUpdate() override {
		Oxide::Renderer::clear();

		a += 0.05f;

		m_cam.setCameraPosition(m_camPos);

		Oxide::Renderer2D::begin(m_cam);
		Oxide::Renderer2D::draw(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(100.0f, 100.0f), -a, glm::vec3(1.0f, 0.5f, 1.0f));
		Oxide::Renderer2D::end();

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
		dipatcher.Dispatch<Oxide::MouseMovedEvent>(&App::onMouseMoved);
	}

	static bool onKeyPessed(Oxide::KeyPressedEvent& e) {
		OX_CLIENT_INFO("KeyPressed");
		if(e.GetKeyCode() == Oxide::Key::Escape){
			g_application->m_closeFlag = true;
		}

		if (e.GetKeyCode() == Oxide::Key::A) {
			g_application->m_camPos.x -= 10.0f;
		}

		if (e.GetKeyCode() == Oxide::Key::D) {
			g_application->m_camPos.x += 10.0f;
		}

		if (e.GetKeyCode() == Oxide::Key::S) {
			g_application->m_camPos.y -= 10.0f;
		}

		if (e.GetKeyCode() == Oxide::Key::W) {
			g_application->m_camPos.y += 10.0f;
		}

		return true;
	}

	static bool onMouseMoved(Oxide::MouseMovedEvent& e) {
		auto h = g_application->m_window->getHeight();
		auto w = g_application->m_window->getWidth();
		g_application->m_mpos = glm::vec2(e.GetX() - w/2, -(e.GetY() - h/2));
		return true;
	}

	static std::string readFile(const char* path) {
		std::ifstream file(path);
		if (!file.is_open()) {
			OX_CLIENT_CRITICAL("Unable to open the file path %s", path);
			return "";
		}
		std::stringstream ss;
		std::string line = "";
		
		ss << file.rdbuf();

		return ss.str();
	}

private:
	float a = 0;
	bool m_closeFlag;
	glm::vec2 m_mpos;
	Oxide::Camera2D m_cam;
	glm::vec3 m_camPos;
	std::shared_ptr<Oxide::Window> m_window;
	std::shared_ptr<Oxide::GraphicalContext> m_graphicalContext;
};

std::shared_ptr<Oxide::Application> Oxide::getApplicationInterface() {
	if (g_application == nullptr)
		g_application = std::shared_ptr<App>(new App());
	return g_application;
}