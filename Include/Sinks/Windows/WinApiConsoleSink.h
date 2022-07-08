#pragma once

#include "Sink.h"
#include <cstdio>

namespace Quartz
{
	class QUARTZLOG_API WinApiConsoleSink : public Sink
	{
	private:
		unsigned short mDefaultLogColors;
		FILE*          mpOutputStream;
		void*		   mhConsole;

	public:
		WinApiConsoleSink();

		void WritePrefixed(LogLevel level, LogColor foreground, LogColor background,
			const char* severityName, const char* format, ...) const override;
		void WritePrefixedV(LogLevel level, LogColor foreground, LogColor background,
			const char* severityName, const char* format, va_list args) const override;

		void WriteRaw(LogColor foreground, LogColor background, const char* format, ...) const override;
		void WriteRawV(LogColor foreground, LogColor background, const char* format, va_list args) const override;

		bool SupportsEscapeColors() const override;
	};
}