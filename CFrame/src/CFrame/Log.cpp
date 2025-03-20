#include "Log.h"

namespace CFrame {

	std::shared_ptr<spdlog::logger> Log::coreLogger;
	std::shared_ptr<spdlog::logger> Log::clientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		coreLogger = spdlog::stdout_color_mt("CORE");
		clientLogger = spdlog::stdout_color_mt("APP");
		coreLogger->set_level(spdlog::level::trace);
		clientLogger->set_level(spdlog::level::trace);

	}
}