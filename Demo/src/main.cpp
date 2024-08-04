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
#include "Renderer/Image.h"
#include "Renderer/Texture2D.h"

#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class App;

static std::shared_ptr<App> g_application = nullptr;

struct VertexData {
	glm::vec3 pos;
	glm::vec2 textCoords;
};

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

		std::string vsrc = readFile("res/textVert.glsl");
		std::string fsrc = readFile("res/textFrag.glsl");
		// Shader Creation
		m_shader = Oxide::Shader::create();
		m_shader->addShader(Oxide::ShaderType::VertexShader, vsrc);
		m_shader->addShader(Oxide::ShaderType::FragmentShader, fsrc);
		m_shader->compile();

		m_cam = Oxide::Camera2D();
		m_camPos = m_cam.getCameraPosition();

		VertexData vertices[] = {
			VertexData({glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 1.0f)}),
			VertexData({glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 1.0f)}),
			VertexData({glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec2(1.0f, 0.0f)}),
			VertexData({glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec2(0.0f, 0.0f)}),
		};

		uint32_t indices[] = { 0,1,2,2,3,0 };

		// Vertex Buffer
		m_vb = Oxide::VertexBuffer::create();
		m_vb->addData(vertices, sizeof(vertices));

		// Index Buffer
		m_ib = Oxide::IndexBuffer::create();
		m_ib->addData(indices, sizeof(indices));

		// VAO
		m_vao = Oxide::VertexArrayObject::create();
		Oxide::Attributes attrs;
		attrs.addAttribute(Oxide::VertexAttributeTypes::Float3);
		attrs.addAttribute(Oxide::VertexAttributeTypes::Float2);
		m_vao->addVertexBuffer(m_vb, attrs);

		// Texture
		m_image = Oxide::Image::fromFile("res/demoTexture.png");
		m_text = Oxide::Texture2D::create();
		m_text->addData(m_image);

		Oxide::Renderer::setClearColour(0x000000ff);
	}

	void onUpdate() override {
		Oxide::Renderer::clear();

		m_shader->Int("u_texUnit", 1);
		Oxide::Renderer::Draw(m_vao, m_ib, m_shader, m_text, 6);

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
		dipatcher.Dispatch<Oxide::MouseButtonPressedEvent>(&App::onMouseClicked);
		dipatcher.Dispatch<Oxide::MouseButtonReleasedEvent>(&App::onMouseReleased);
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
		glm::vec2 opos = g_application->m_mpos;
		auto h = g_application->m_window->getHeight();
		auto w = g_application->m_window->getWidth();
		g_application->m_mpos = glm::vec2(e.GetX() - w/2, -(e.GetY() - h/2));

		if (g_application->m_clicked) {
			g_application->m_camPos += glm::vec3((g_application->m_mpos - opos), 0.0f);
		}

		return true;
	}

	static bool onMouseClicked(Oxide::MouseButtonPressedEvent& e) {
		g_application->m_clicked = true;
		return true;
	}

	static bool onMouseReleased(Oxide::MouseButtonReleasedEvent& e) {
		g_application->m_clicked = false;
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
	bool m_clicked = false;
	std::shared_ptr<Oxide::Image> m_image;
	glm::vec2 m_mpos = glm::vec2(0.0f);
	Oxide::Camera2D m_cam;
	glm::vec3 m_camPos;

	std::shared_ptr<Oxide::Shader> m_shader;
	std::shared_ptr<Oxide::VertexBuffer> m_vb;
	std::shared_ptr<Oxide::IndexBuffer> m_ib;
	std::shared_ptr<Oxide::VertexArrayObject> m_vao;
	std::shared_ptr<Oxide::Texture2D> m_text;
	std::shared_ptr<Oxide::Window> m_window;
	std::shared_ptr<Oxide::GraphicalContext> m_graphicalContext;
};

std::shared_ptr<Oxide::Application> Oxide::getApplicationInterface() {
	if (g_application == nullptr)
		g_application = std::shared_ptr<App>(new App());
	return g_application;
}