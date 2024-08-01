#include<iostream>

#include"Core/Application.h"

class App : public Oxide::Application {
public:
	void onInit() override {
		std::cout << "OnInit" << std::endl;
		m_closeFlag = false;
	}

	void onUpdate() override {
		std::cout << "OnUpdate" << std::endl;
		m_closeFlag = true;
	}

	void onDestroy() override {
		std::cout << "OnDestroy" << std::endl;
	}

	bool shouldApplicationClose() override {
		return m_closeFlag;
	}
private:
	bool m_closeFlag;

};

std::shared_ptr<Oxide::Application> Oxide::getApplicationInterface() {
	return std::shared_ptr<Oxide::Application>(new App());
}