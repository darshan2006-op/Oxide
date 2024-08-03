#include "Core/Application.h"
#include "Renderer/GraphicalContext.h"
#include "Core/Window.h"
#include "Renderer/Renderer.h"
#include "Logging/logger.h"
#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/VertexArrayObject.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Shader.h"

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

		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		};

		unsigned int indices[] = { 0,1,2 };

		std::string vsrc = App::readFile("res/vert.glsl");
		std::string fsrc = App::readFile("res/frag.glsl");
		m_shader = Oxide::Shader::create();
		m_shader->addShader(Oxide::ShaderType::VertexShader, vsrc);
		m_shader->addShader(Oxide::ShaderType::FragmentShader, fsrc);
		m_shader->compile();

		m_vb = Oxide::VertexBuffer::create();
		m_ib = Oxide::IndexBuffer::create();
		m_vao = Oxide::VertexArrayObject::create();

		m_vb->addData(vertices, sizeof(vertices));
		m_ib->addData(indices, sizeof(indices));

		Oxide::Attributes attrs;
		attrs.addAttribute(Oxide::VertexAttributeTypes::Float3);
		attrs.addAttribute(Oxide::VertexAttributeTypes::Float3);

		m_vao->addVertexBuffer(m_vb, attrs);

		Oxide::Renderer::setClearColour(0x000000ff);
	}

	void onUpdate() override {
		Oxide::Renderer::clear();
		Oxide::Renderer::Draw(m_vao, m_ib, m_shader, 3);

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
	bool m_closeFlag;

	std::shared_ptr<Oxide::VertexArrayObject> m_vao;
	std::shared_ptr<Oxide::VertexBuffer> m_vb;
	std::shared_ptr<Oxide::IndexBuffer> m_ib;
	std::shared_ptr<Oxide::Shader> m_shader;

	std::shared_ptr<Oxide::Window> m_window;
	std::shared_ptr<Oxide::GraphicalContext> m_graphicalContext;
};

std::shared_ptr<Oxide::Application> Oxide::getApplicationInterface() {
	if (g_application == nullptr)
		g_application = std::shared_ptr<App>(new App());
	return g_application;
}