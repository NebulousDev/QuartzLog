#pragma once

#include "Sink.h"
#include "Types/Types.h"
#include "Types/Array.h"
#include "Types/String.h"
#include "Utility/Move.h"
#include <time.h>

namespace Quartz
{
	class QUARTZLOG_API Log
	{
	private:
		Array<Sink*> mSinks;

	public:
		static uSize ParseFormat(const LogSeverity& severity, char* pBuffer, 
			uSize bufferSize, tm time, const char* format, const char* text);

		static uSize ParseFormat(const LogSeverity& severity, wchar_t* pBuffer,
			uSize bufferSize, tm time, const char* format, const wchar_t* wtext);

	public:
		Log(const Array<Sink*>& sinks);

		static Log& GetInstance();
		static void SetInstance(Log& logger);

		template<typename Severity, typename... Args>
		void Prefixed(const Severity& severity, const char* format, Args... args)
		{
			for (const Sink* pSink : mSinks)
			{
				pSink->WritePrefixed(severity, format, Forward<Args>(args)...);
			}
		}

		template<typename Severity, typename... Args>
		void Prefixed(const Severity& severity, const wchar_t* wformat, Args... args)
		{
			for (const Sink* pSink : mSinks)
			{
				pSink->WritePrefixed(severity, wformat, Forward<Args>(args)...);
			}
		}

		template<typename... Args>
		void Raw(const char* format, Args... args)
		{
			for (const Sink* pSink : mSinks)
			{
				pSink->WriteRaw(format, Forward<Args>(args)...);
			}
		}

		template<typename... Args>
		void Raw(const wchar_t* wformat, Args... args)
		{
			for (const Sink* pSink : mSinks)
			{
				pSink->WriteRaw(wformat, Forward<Args>(args)...);
			}
		}

		void RunLogTest();
	};
}

#ifndef QUARTZ_LOG_LEVEL
	#define QUARTZ_LOG_LEVEL 0
#endif

#define DefineLogSeverity(severity, text, fg, bg, level) \
	class LogSeverity##severity : public Quartz::LogSeverity \
	{ \
	public: \
		const char* GetText() const override { return text; } \
		const Quartz::LogLevel GetLevel() const override { return level; } \
		Quartz::LogColor GetForegroundColor() const override { return fg; } \
		Quartz::LogColor GetBackgroundColor() const override { return bg; } \
		Quartz::uSize GetTextSize() const override { return sizeof(text); } \
		Quartz::uSize GetForegroundColorSize() const override { return sizeof(fg); } \
		Quartz::uSize GetBackgroundColorSize() const override { return sizeof(bg); } \
	}; \
	namespace Quartz { namespace _Log { constexpr LogSeverity##severity csLogSeverity##severity; } }

#define GetLogSeverity(severity) Quartz::_Log::csLogSeverity##severity

#ifdef QUARTZLOG_COLORS

#ifdef QUARTZLOG_ANSI
	DefineLogSeverity(TEST,    "Test",    LOG_DARK_CYAN,	LOG_NONE,	Quartz::LOG_LEVEL_TRACE);
	DefineLogSeverity(TRACE,   "Trace",   LOG_CYAN,			LOG_NONE,	Quartz::LOG_LEVEL_TRACE);
	DefineLogSeverity(DEBUG,   "Debug",   LOG_GREEN,		LOG_NONE,	Quartz::LOG_LEVEL_DEBUG);
	DefineLogSeverity(INFO,    "Info",    LOG_WHITE,		LOG_NONE,	Quartz::LOG_LEVEL_INFO);
	DefineLogSeverity(WARNING, "Warning", LOG_YELLOW,		LOG_NONE,	Quartz::LOG_LEVEL_WARNING);
	DefineLogSeverity(ERROR,   "Error",   LOG_RED,			LOG_NONE,	Quartz::LOG_LEVEL_ERROR);
	DefineLogSeverity(FATAL,   "Fatal",   LOG_MAGENTA,		LOG_NONE,	Quartz::LOG_LEVEL_FATAL);
	DefineLogSeverity(SUCCESS, "Success", LOG_DARK_GREEN,   LOG_NONE,	Quartz::LOG_LEVEL_SUCCESS);
	DefineLogSeverity(FAIL,    "Fail",    LOG_DARK_RED,		LOG_NONE,	Quartz::LOG_LEVEL_FAIL);
#else
	DefineLogSeverity(TEST,    "Test",    Quartz::LOG_LEVEL_TRACE,   Quartz::LOG_COLOR_DARK_CYAN, Quartz::LOG_COLOR_DEFAULT);
	DefineLogSeverity(TRACE,   "Trace",   Quartz::LOG_LEVEL_TRACE,   Quartz::LOG_COLOR_CYAN,      Quartz::LOG_COLOR_DEFAULT);
	DefineLogSeverity(DEBUG,   "Debug",   Quartz::LOG_LEVEL_DEBUG,   Quartz::LOG_COLOR_GREEN,     Quartz::LOG_COLOR_DEFAULT);
	DefineLogSeverity(INFO,    "Info",    Quartz::LOG_LEVEL_INFO,    Quartz::LOG_COLOR_WHITE,     Quartz::LOG_COLOR_DEFAULT);
	DefineLogSeverity(WARNING, "Warning", Quartz::LOG_LEVEL_WARNING, Quartz::LOG_COLOR_YELLOW,    Quartz::LOG_COLOR_DEFAULT);
	DefineLogSeverity(ERROR,   "Error",   Quartz::LOG_LEVEL_ERROR,   Quartz::LOG_COLOR_RED,       Quartz::LOG_COLOR_DEFAULT);
	DefineLogSeverity(FATAL,   "Fatal",   Quartz::LOG_LEVEL_FATAL,   Quartz::LOG_COLOR_MAGENTA,   Quartz::LOG_COLOR_DEFAULT);
#endif

#else
	DefineLogSeverity(TEST,    "Test",    Quartz::LOG_LEVEL_TRACE,   Quartz::LOG_COLOR_DEFAULT, Quartz::LOG_COLOR_DEFAULT);
	DefineLogSeverity(TRACE,   "Trace",   Quartz::LOG_LEVEL_TRACE,   Quartz::LOG_COLOR_DEFAULT, Quartz::LOG_COLOR_DEFAULT);
	DefineLogSeverity(DEBUG,   "Debug",   Quartz::LOG_LEVEL_DEBUG,   Quartz::LOG_COLOR_DEFAULT, Quartz::LOG_COLOR_DEFAULT);
	DefineLogSeverity(INFO,    "Info",    Quartz::LOG_LEVEL_INFO,    Quartz::LOG_COLOR_DEFAULT, Quartz::LOG_COLOR_DEFAULT);
	DefineLogSeverity(WARNING, "Warning", Quartz::LOG_LEVEL_WARNING, Quartz::LOG_COLOR_DEFAULT, Quartz::LOG_COLOR_DEFAULT);
	DefineLogSeverity(ERROR,   "Error",   Quartz::LOG_LEVEL_ERROR,   Quartz::LOG_COLOR_DEFAULT, Quartz::LOG_COLOR_DEFAULT);
	DefineLogSeverity(FATAL,   "Fatal",   Quartz::LOG_LEVEL_FATAL,   Quartz::LOG_COLOR_DEFAULT, Quartz::LOG_COLOR_DEFAULT);
#endif

#define _LogRaw(format, ...) Quartz::Log::GetInstance().Raw(format, ##__VA_ARGS__)

#define _LogPrefixed(severity, format, ...) Quartz::Log::GetInstance().Prefixed(\
		Quartz::_Log::csLogSeverity##severity, format, ##__VA_ARGS__)

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
#define LogSuccess(format, ...) _LogPrefixed(SUCCESS, format, ##__VA_ARGS__)
#define LogFail(format, ...)    _LogPrefixed(FAIL, format, ##__VA_ARGS__)
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