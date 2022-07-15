#pragma once

#include "Color.h"
#include "Types/Types.h"

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

	//template<const char* _text, LogLevel _level, LogColor _fg, LogColor _bg>
	struct QUARTZLOG_API LogSeverity
	{
		/*
		constexpr const char*    text    = _text;
		constexpr const LogLevel level   = _level;
		constexpr const LogColor fgColor = _fg;
		constexpr const LogColor gbColor = _bg;
		*/

	public:
		virtual const char* GetText() const = 0;
		virtual const LogLevel GetLevel() const = 0;
		virtual LogColor GetForegroundColor() const = 0;
		virtual LogColor GetBackgroundColor() const = 0;
	};
}