#pragma once
#include <memory>


namespace Oxide {
	class Application {
	public:
		virtual void onInit() = 0;
		virtual void onUpdate() = 0;
		virtual void onDestroy() = 0;
		virtual bool shouldApplicationClose() = 0;
		virtual ~Application() = default;
	};
	// must be defined in client application
	extern std::shared_ptr<Application> getApplicationInterface();
}