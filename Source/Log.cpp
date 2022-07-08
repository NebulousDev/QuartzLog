#include "Log.h"

namespace Quartz
{
	Log sDefaultLog;
	Log* spLog = &sDefaultLog;

	Log::Log()
	{
		InitLogging(); //temp
	}

	Log Log::CreateLog()
	{
		return Log();
	}

	Log& Log::GetGlobalLog()
	{
		return *spLog;
	}

	void Log::SetGlobalLog(Log& logger)
	{
		spLog = &logger;
	}

	void Log::SetLogLevel(LogLevel level)
	{
		static const char* slogLevelNames[] =
		{ "TRACE", "DEBUG", "INFO" , "WARNING" , "ERROR" , "FATAL" };

		Raw(Quartz::LOG_COLOR_BLUE, Quartz::LOG_COLOR_DEFAULT,
			"LogLevel set to %d (%s).\n", level, slogLevelNames[level]);

		mLogLevel = level;
	}

	LogLevel Log::GetLogLevel()
	{
		return mLogLevel;
	}
}
