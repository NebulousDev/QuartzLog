#include "Log.h"

#include <cstdarg>

namespace Quartz
{
	Log* spLog = nullptr;

	Log::Log(const Array<Sink*>& sinks) :
		mSinks(sinks) { }

	Log& Log::GetGlobalLog()
	{
		return *spLog;
	}

	void Log::SetGlobalLog(Log& logger)
	{
		spLog = &logger;
	}

	void Log::Prefixed(LogLevel level, LogColor foreground, LogColor background,
		const char* severityName, const char* format, ...)
	{
		for (const Sink* pSink : mSinks)
		{
			va_list args;
			va_list argsCpy;
			va_start(args, format);
			va_copy(argsCpy, args);
			pSink->WritePrefixedV(level, foreground, background, severityName, format, argsCpy);
			va_end(args);
		}
	}

	void Log::Raw(LogColor foreground, LogColor background, const char* format, ...)
	{
		for (const Sink* pSink : mSinks)
		{
			va_list args;
			va_list argsCpy;
			va_start(args, format);
			va_copy(argsCpy, args);
			pSink->WriteRawV(foreground, background, format, argsCpy);
			va_end(args);
		}
	}
}
