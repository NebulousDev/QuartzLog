#include "Sink.h"

namespace Quartz
{
	Sink::Sink()
	{
		mLogLevel = LOG_LEVEL_TRACE;
		mPrefix = "%H:%M:%S";
	}

	void Sink::SetPrefixFormat(const char* format)
	{
		mPrefix = format;
	}

	void Sink::SetLogLevel(LogLevel level)
	{
		mLogLevel = level;
	}

	LogLevel Sink::GetLogLevel() const
	{
		return mLogLevel;
	}
}