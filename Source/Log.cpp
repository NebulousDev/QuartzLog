#include "Log.h"

namespace Quartz
{
	LogLevel Log::smLogLevel = LOG_LEVEL_TRACE;

	void Log::SetLogLevel(LogLevel level)
	{
		static const char* slogLevelNames[] =
		{ "TRACE", "DEBUG", "INFO" , "WARNING" , "ERROR" , "FATAL" };

		LogRaw(Quartz::LOG_COLOR_BLUE, Quartz::LOG_COLOR_DEFAULT,
			"LogLevel set to %d (%s).\n", level, slogLevelNames[level]);

		smLogLevel = level;
	}

	LogLevel Log::GetLogLevel()
	{
		return smLogLevel;
	}
}
