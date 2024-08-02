#include "Application.h"
#include "Logging/logger.h"

#include "Events/ApplicationEvents.h"
#include "Events/Event.h"

int main() {
	auto app = Oxide::getApplicationInterface();

	Oxide::Logger::init();
	app->onInit();

	while (!app->shouldApplicationClose())
	{
		Oxide::AppTickEvent e = Oxide::AppTickEvent();
		app->onEvent((Oxide::Event&)e);
		app->onUpdate();
	}

	app->onDestroy();
}