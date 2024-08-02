#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Oxide {
	class Logger {
	public:
		static void init();
		static std::shared_ptr<spdlog::logger> getCoreLogger() { return s_coreLogger; }
		static std::shared_ptr<spdlog::logger> getClientLogger() { return s_clientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
	};
}

#define OX_CORE_TRACE(...) ::Oxide::Logger::getCoreLogger()->trace(__VA_ARGS__);
#define OX_CORE_INFO(...) ::Oxide::Logger::getCoreLogger()->info(__VA_ARGS__);
#define OX_CORE_WARN(...) ::Oxide::Logger::getCoreLogger()->warn(__VA_ARGS__);
#define OX_CORE_ERROR(...) ::Oxide::Logger::getCoreLogger()->error(__VA_ARGS__);
#define OX_CORE_CRITICAL(...) ::Oxide::Logger::getCoreLogger()->critical(__VA_ARGS__);

#define OX_CLIENT_TRACE(...) ::Oxide::Logger::getClientLogger()->trace(__VA_ARGS__);
#define OX_CLIENT_INFO(...) ::Oxide::Logger::getClientLogger()->info(__VA_ARGS__);
#define OX_CLIENT_WARN(...) ::Oxide::Logger::getClientLogger()->warn(__VA_ARGS__);
#define OX_CLIENT_ERROR(...) ::Oxide::Logger::getClientLogger()->error(__VA_ARGS__);
#define OX_CLIENT_CRITICAL(...) ::Oxide::Logger::getClientLogger()->critical(__VA_ARGS__);