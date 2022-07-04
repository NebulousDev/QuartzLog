#pragma once

#include "DLL.h"

namespace Quartz
{

#ifndef QUARTZ_LOG_LEVEL_ENUM

	enum LogLevel
	{
		LOG_LEVEL_TRACE,
		LOG_LEVEL_DEBUG,
		LOG_LEVEL_INFO,
		LOG_LEVEL_WARNING,
		LOG_LEVEL_ERROR,
		LOG_LEVEL_FATAL
	};

#define QUARTZ_LOG_LEVEL_ENUM

#endif

	enum LogColor
	{
		LOG_COLOR_DEFAULT,
		LOG_COLOR_BLACK,
		LOG_COLOR_DARK_BLUE,
		LOG_COLOR_DARK_GREEN,
		LOG_COLOR_DARK_CYAN,
		LOG_COLOR_DARK_RED,
		LOG_COLOR_DARK_MAGENTA,
		LOG_COLOR_DARK_YELLOW,
		LOG_COLOR_DARK_GRAY,
		LOG_COLOR_GRAY,
		LOG_COLOR_BLUE,
		LOG_COLOR_GREEN,
		LOG_COLOR_CYAN,
		LOG_COLOR_RED,
		LOG_COLOR_MAGENTA,
		LOG_COLOR_YELLOW,
		LOG_COLOR_WHITE
	};

	class QUARTZLOG_API Log
	{
	private:
		static LogLevel smLogLevel;

	public:
		static void InitLogging();
		static void SetLogLevel(LogLevel level);

		static void RunLogTest();

		static void _Log(LogLevel level, LogColor foreground, LogColor background,
			const char* severityName, const char* format, ...);
		static void _Log(LogLevel level, LogColor foreground, LogColor background,
			const char* severityName, const wchar_t* format, ...);

		static void _LogRaw(LogColor foreground, LogColor background, const char* format, ...);
		static void _LogRaw(LogColor foreground, LogColor background, const wchar_t* format, ...);

		static LogLevel GetLogLevel();
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

#define LogRaw(forground, background, format, ...) Quartz::Log::_LogRaw( \
		forground, background, format, ##__VA_ARGS__)

#define Log(severity, format, ...) Quartz::Log::_Log( \
		Quartz::_Log::csLogSeverity##severity.sLevel, \
		Quartz::_Log::csLogSeverity##severity.sForegroundColor, Quartz::_Log::csLogSeverity##severity.sBackgroundColor, \
		Quartz::_Log::csLogSeverity##severity.sText, format, ##__VA_ARGS__)

#if QUARTZ_LOG_LEVEL == 0
#define LogTest(format, ...)    Log(TEST, format, ##__VA_ARGS__)
#else
#define LogTest(format, ...)
#endif

#if QUARTZ_LOG_LEVEL == 0
#define LogTrace(format, ...)   Log(TRACE, format, ##__VA_ARGS__)
#else
#define LogTrace(format, ...)
#endif

#if QUARTZ_LOG_LEVEL <= 1
#define LogDebug(format, ...)   Log(DEBUG, format, ##__VA_ARGS__)
#else
#define LogDebug(format, ...)
#endif

#if QUARTZ_LOG_LEVEL <= 2
#define LogInfo(format, ...)    Log(INFO, format, ##__VA_ARGS__)
#else
#define LogInfo(format, ...)
#endif

#if QUARTZ_LOG_LEVEL <= 3
#define LogWarning(format, ...) Log(WARNING, format, ##__VA_ARGS__)
#else
#define LogWarning(format, ...)
#endif

#if QUARTZ_LOG_LEVEL <= 4
#define LogError(format, ...)   Log(ERROR, format, ##__VA_ARGS__)
#else
#define LogError(format, ...)
#endif

#if QUARTZ_LOG_LEVEL <= 5
#define LogFatal(format, ...)   Log(FATAL, format, ##__VA_ARGS__)
#else
#define LogFatal(format, ...)
#endif