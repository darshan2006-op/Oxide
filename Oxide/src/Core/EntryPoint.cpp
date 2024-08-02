#include "Application.h"
#include "Logging/logger.h"

int main() {
	auto app = Oxide::getApplicationInterface();

	Oxide::Logger::init();
	app->onInit();

	while (!app->shouldApplicationClose())
	{
		app->onUpdate();
	}

	app->onDestroy();
}