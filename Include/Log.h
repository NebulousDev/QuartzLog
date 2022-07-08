#pragma once

#include "Sink.h"
#include "LogLevel.h"
#include "Types/Array.h"

namespace Quartz
{
	class QUARTZLOG_API Log
	{
	private:
		Array<Sink*> mSinks;

	public:
		Log(const Array<Sink*>& sinks);

		static Log& GetGlobalLog();
		static void SetGlobalLog(Log& logger);

		void Prefixed(LogLevel level, LogColor foreground, LogColor background,
			const char* severityName, const char* format, ...);

		void Raw(LogColor foreground, LogColor background, const char* format, ...);

		void RunLogTest();
	};
}

#ifndef QUARTZ_LOG_LEVEL
#define QUARTZ_LOG_LEVEL 0
#endif

#define DefineLogSeverity(severity, text, level, foreground, background) \
	struct LogSeverity##severity \
	{ \
		constexpr static const char* sText = text; \
		constexpr static const Quartz::LogLevel sLevel = level; \
		constexpr static const Quartz::LogColor sForegroundColor = foreground; \
		constexpr static const Quartz::LogColor sBackgroundColor = background; \
	}; \
	namespace Quartz { namespace _Log { constexpr LogSeverity##severity csLogSeverity##severity; } }

DefineLogSeverity(TEST,    "Test",    Quartz::LOG_LEVEL_TRACE,   Quartz::LOG_COLOR_DARK_CYAN, Quartz::LOG_COLOR_DEFAULT);
DefineLogSeverity(TRACE,   "Trace",   Quartz::LOG_LEVEL_TRACE,   Quartz::LOG_COLOR_CYAN,      Quartz::LOG_COLOR_DEFAULT);
DefineLogSeverity(DEBUG,   "Debug",   Quartz::LOG_LEVEL_DEBUG,   Quartz::LOG_COLOR_GREEN,     Quartz::LOG_COLOR_DEFAULT);
DefineLogSeverity(INFO,    "Info",    Quartz::LOG_LEVEL_INFO,    Quartz::LOG_COLOR_WHITE,     Quartz::LOG_COLOR_DEFAULT);
DefineLogSeverity(WARNING, "Warning", Quartz::LOG_LEVEL_WARNING, Quartz::LOG_COLOR_YELLOW,    Quartz::LOG_COLOR_DEFAULT);
DefineLogSeverity(ERROR,   "Error",   Quartz::LOG_LEVEL_ERROR,   Quartz::LOG_COLOR_RED,       Quartz::LOG_COLOR_DEFAULT);
DefineLogSeverity(FATAL,   "Fatal",   Quartz::LOG_LEVEL_FATAL,   Quartz::LOG_COLOR_MAGENTA,   Quartz::LOG_COLOR_DEFAULT);

#define _LogRaw(forground, background, format, ...) Quartz::Log::GetGlobalLog().Raw( \
		forground, background, format, ##__VA_ARGS__)

#define _LogPrefixed(severity, format, ...) Quartz::Log::GetGlobalLog().Prefixed( \
		Quartz::_Log::csLogSeverity##severity.sLevel, \
		Quartz::_Log::csLogSeverity##severity.sForegroundColor, Quartz::_Log::csLogSeverity##severity.sBackgroundColor, \
		Quartz::_Log::csLogSeverity##severity.sText, format, ##__VA_ARGS__)

#if QUARTZ_LOG_LEVEL == 0
#define LogTest(format, ...)    _LogPrefixed(TEST, format, ##__VA_ARGS__)
#else
#define LogTest(format, ...)
#endif

#if QUARTZ_LOG_LEVEL == 0
#define LogTrace(format, ...)   _LogPrefixed(TRACE, format, ##__VA_ARGS__)
#else
#define LogTrace(format, ...)
#endif

#if QUARTZ_LOG_LEVEL <= 1
#define LogDebug(format, ...)   _LogPrefixed(DEBUG, format, ##__VA_ARGS__)
#else
#define LogDebug(format, ...)
#endif

#if QUARTZ_LOG_LEVEL <= 2
#define LogInfo(format, ...)    _LogPrefixed(INFO, format, ##__VA_ARGS__)
#else
#define LogInfo(format, ...)
#endif

#if QUARTZ_LOG_LEVEL <= 3
#define LogWarning(format, ...) _LogPrefixed(WARNING, format, ##__VA_ARGS__)
#else
#define LogWarning(format, ...)
#endif

#if QUARTZ_LOG_LEVEL <= 4
#define LogError(format, ...)   _LogPrefixed(ERROR, format, ##__VA_ARGS__)
#else
#define LogError(format, ...)
#endif

#if QUARTZ_LOG_LEVEL <= 5
#define LogFatal(format, ...)   _LogPrefixed(FATAL, format, ##__VA_ARGS__)
#else
#define LogFatal(format, ...)
#endif

#define LogRaw _LogRaw