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
		LOG_LEVEL_FATAL,
		LOG_LEVEL_SUCCESS,
		LOG_LEVEL_FAIL
	};

#define QUARTZ_LOG_LEVEL_ENUM

#endif

	struct QUARTZLOG_API LogSeverity
	{
	public:
		virtual const char* GetText() const = 0;
		virtual const LogLevel GetLevel() const = 0;
		virtual LogColor GetForegroundColor() const = 0;
		virtual LogColor GetBackgroundColor() const = 0;

		virtual uSize GetTextSize() const = 0;
		virtual uSize GetForegroundColorSize() const = 0;
		virtual uSize GetBackgroundColorSize() const = 0;
	};
}