#include "Sink.h"

namespace Quartz
{
	Sink::Sink()
	{
		mLogLevel = LOG_LEVEL_TRACE;
		mTimeFormat = "%H:%M:%S";
		mLevelFormat = "%s";
		mTextFormat = "%s";
	}

	void Sink::SetTimeFormat(const char* format)
	{
		mTimeFormat = format;
	}

	void Sink::SetLevelFormat(const char* format)
	{
		mLevelFormat = format;
	}

	void Sink::SetTextFormat(const char* format)
	{
		mTextFormat = format;
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