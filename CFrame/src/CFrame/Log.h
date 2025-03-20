#pragma once

#include "Core.h"
#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace CFrame 
{
	class CFRAME_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return clientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> coreLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;

	};
}// namespace CFrame


#define CF_CORE_TRACE(...)    ::CFrame::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CF_CORE_INFO(...)     ::CFrame::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CF_CORE_WARN(...)     ::CFrame::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CF_CORE_ERROR(...)    ::CFrame::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CF_CORE_FATAL(...)    ::CFrame::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define CF_TRACE(...)         ::CFrame::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CF_INFO(...)          ::CFrame::Log::GetClientLogger()->info(__VA_ARGS__)
#define CF_WARN(...)          ::CFrame::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CF_ERROR(...)         ::CFrame::Log::GetClientLogger()->error(__VA_ARGS__)
#define CF_FATAL(...)         ::CFrame::Log::GetClientLogger()->fatal(__VA_ARGS__)





