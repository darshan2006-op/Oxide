#include "Window.h"
#include "PlatformDetection.h"
#include "Platform/Windows/WindowsWindow.h"

#include <stdexcept>

namespace Oxide {
	std::shared_ptr<Window> Window::create(WindowData data)
	{
#ifdef OX_PLATFORM_WINDOWS
		return std::shared_ptr<Window>(new WindowsWindow(data));
#else
		throw std::runtime_error("Unsupported Platform");
		return nullptr;
#endif // OX_PLATFORM_WINDOWS

	}
}
