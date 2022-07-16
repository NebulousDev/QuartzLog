#pragma once

#include "DLL.h"
#include "Level.h"
#include <cstdarg>

namespace Quartz
{
	class QUARTZLOG_API Sink
	{
	protected:
		LogLevel    mLogLevel;
		const char* mFormat;

	public:
		Sink();

		virtual void WritePrefixed(const LogSeverity& severity, const char* format, ...) const = 0;
		virtual void WritePrefixedV(const LogSeverity& severity, const char* format, va_list args) const = 0;

		virtual void WriteRaw(const char* format, ...) const = 0;
		virtual void WriteRawV(const char* format, va_list args) const = 0;

		// $BG - severity background color
		// $FG - severity foreground color
		// $H  - hours
		// $M  - minutes
		// $S  - seconds
		// $V  - severity
		// $C  - category
		// $T  - log text
		void SetFormat(const char* format);

		void SetLogLevel(LogLevel level);
		LogLevel GetLogLevel() const;

		virtual bool SupportsEscapeColors() const = 0;
	};
}