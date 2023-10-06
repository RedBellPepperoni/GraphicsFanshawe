#pragma once
#include "spdlog/spdlog.h"



#define LOG_TRACE(caller, ...) ::FanshaweGameEngine::Debug::Log::GetCoreLogger()->trace(caller, __VA_ARGS__)
#define LOG_INFO(caller, ...) ::FanshaweGameEngine::Debug::Log::GetCoreLogger()->info(caller, __VA_ARGS__)
#define LOG_WARN(...) ::FanshaweGameEngine::Debug::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::FanshaweGameEngine::Debug::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::FanshaweGameEngine::Debug::Log::GetCoreLogger()->critical(__VA_ARGS__)


namespace FanshaweGameEngine
{

	namespace Debug
	{
		class Log
		{
		public:

			static void OnInit();
			static void OnRelease();

			static std::shared_ptr <spdlog::logger>& GetCoreLogger();

			static void AddSink(spdlog::sink_ptr& sink);
		private:

			static std::shared_ptr <spdlog::logger> m_coreLogger;
		};
	}
}

