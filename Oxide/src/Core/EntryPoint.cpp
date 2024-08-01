#include "Application.h"


int main() {
	auto app = Oxide::getApplicationInterface();

	app->onInit();

	while (!app->shouldApplicationClose())
	{
		app->onUpdate();
	}

	app->onDestroy();
}