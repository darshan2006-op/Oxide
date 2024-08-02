#include "logger.h"

namespace Oxide {
	std::shared_ptr<spdlog::logger> Logger::s_coreLogger;
	std::shared_ptr<spdlog::logger> Logger::s_clientLogger;
	void Logger::init()
	{
		// Core Logger Setup
		std::string core_pattern = "[Oxide Core] [%d %b %Y %R] [%^%l%$] %v";
		auto core_cons_sink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();
		core_cons_sink->set_level(spdlog::level::trace);
		core_cons_sink->set_pattern(core_pattern);

		auto core_file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("log/core_engine_log.txt", true);
		core_file_sink->set_level(spdlog::level::trace);
		core_file_sink->set_pattern(core_pattern);

		std::vector<spdlog::sink_ptr> core_sinks;
		core_sinks.push_back(core_cons_sink);
		core_sinks.push_back(core_file_sink);

		s_coreLogger = std::make_shared<spdlog::logger>("Oxide Core Logger", begin(core_sinks), end(core_sinks));

		// Client Logger Setup
		std::string client_pattern = "[Client] [%d %b %Y %R] [%^%l%$] %v";
		auto client_cons_sink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();
		client_cons_sink->set_level(spdlog::level::trace);
		client_cons_sink->set_pattern(client_pattern);

		auto client_file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("log/client_engine_log.txt", true);
		client_file_sink->set_level(spdlog::level::trace);
		client_file_sink->set_pattern(client_pattern);

		std::vector<spdlog::sink_ptr> client_sinks;
		client_sinks.push_back(client_cons_sink);
		client_sinks.push_back(client_file_sink);

		s_clientLogger = std::make_shared<spdlog::logger>("Oxide Client Logger", begin(client_sinks), end(client_sinks));
	}
}