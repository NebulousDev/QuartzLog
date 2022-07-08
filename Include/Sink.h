#pragma once

#include "DLL.h"
#include "LogLevel.h"
#include <cstdarg>

namespace Quartz
{
	class QUARTZLOG_API Sink
	{
	protected:
		LogLevel    mLogLevel;
		const char* mPrefix;

	public:
		Sink();

		virtual void WritePrefixed(LogLevel level, LogColor foreground, LogColor background,
			const char* severityName, const char* format, ...) const = 0;
		virtual void WritePrefixedV(LogLevel level, LogColor foreground, LogColor background,
			const char* severityName, const char* format, va_list args) const = 0;

		virtual void WriteRaw(LogColor foreground, LogColor background, const char* format, ...) const = 0;
		virtual void WriteRawV(LogColor foreground, LogColor background, const char* format, va_list args) const = 0;

		void SetPrefixFormat(const char* format);

		void SetLogLevel(LogLevel level);
		LogLevel GetLogLevel() const;

		virtual bool SupportsEscapeColors() const = 0;
	};
}