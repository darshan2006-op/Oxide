#pragma once
#include <memory>
#include "Events/Event.h"

namespace Oxide {
	class Application {
	public:
		virtual void onInit() = 0;
		virtual void onUpdate() = 0;
		virtual void onDestroy() = 0;
		virtual bool shouldApplicationClose() = 0;
		virtual ~Application() = default;
		virtual void onEvent(Event& e) {}
	protected:
		Application() = default;
	};
	// must be defined in client application
	extern std::shared_ptr<Application> getApplicationInterface();
}