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

		void WritePrefixed(const LogSeverity& severity, const char* format, ...) const override;
		void WritePrefixedV(const LogSeverity& severity, const char* format, va_list args) const override;

		void WriteRaw(const char* format, ...) const override;
		void WriteRawV(const char* format, va_list args) const override;

		bool SupportsEscapeColors() const override;
	};
}