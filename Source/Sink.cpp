#include "Sink.h"

namespace Quartz
{
	Sink::Sink()
	{
		mLogLevel = LOG_LEVEL_TRACE;
		mFormat = LOG_GRAY "[$H:$M:$S]" LOG_WHITE "[" "$FG$BG$V" LOG_RESET LOG_WHITE "] $FG$BG$T\n" LOG_RESET;
	}

	void Sink::SetFormat(const char* format)
	{
		mFormat = format;
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