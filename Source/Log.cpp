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

	void Log::Prefixed(const LogSeverity& severity, const char* format, ...)
	{
		for (const Sink* pSink : mSinks)
		{
			va_list args;
			va_start(args, format);
			pSink->WritePrefixedV(severity, format, args);
			va_end(args);
		}
	}

	void Log::Raw(const char* format, ...)
	{
		for (const Sink* pSink : mSinks)
		{
			va_list args;
			va_start(args, format);
			pSink->WriteRawV(format, args);
			va_end(args);
		}
	}

	/*
	uSize Resolve(const char* format, const LogSeverity& severity,
		const char* text, tm time, bool useColor, char* pBuffer, uSize buffSize)
	{
		char* pBuffItr = pBuffer;

		for (
			const char* chr = format; 
			chr != '\0' || (pBuffItr == pBuffer + buffSize); // Stop at end of format or end of buffer
			chr++)
		{
			if (*chr == '\\')
			{
				if (*(chr + 1) == '$')
				{
					chr++;
					continue;
				}
			}

			if (*chr == '$')
			{
				chr++;

				// TODO: PLEASE optimize.
				if (useColor && *chr == 'F' && *(chr + 1) == 'G')
				{
					const char* fgColor = severity.GetForegroundColor();
					uSize length = strlen(fgColor);
					memcpy(pBuffItr, fgColor, );
					pBuffItr += 2;
				}

				// TODO: PLEASE optimize.
				if (useColor && *chr == 'F' && *(chr + 1) == 'G')
				{
					const char* fgColor = severity.GetForegroundColor();
					memcpy(pBuffItr, fgColor, strlen(fgColor));
					pBuffItr += 2;
				}
			}
		}
	}
	*/
}
