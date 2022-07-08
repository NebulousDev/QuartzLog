#include "Log.h"

#include <cstdio>
#include <cstdarg>
#include <time.h>
#include <fcntl.h>
#include <locale.h>
#include <wchar.h>

#include <ios>

namespace Quartz
{
	const wchar_t* sLinuxForegroundLogColors[] =
	{
		/* LOG_COLOR_DEFAULT */         L"\033[39m",
		/* LOG_COLOR_BLACK */           L"\033[30m",
		/* LOG_COLOR_DARK_BLUE */       L"\033[34m",
		/* LOG_COLOR_DARK_GREEN */      L"\033[32m",
		/* LOG_COLOR_DARK_CYAN */       L"\033[36m",
		/* LOG_COLOR_DARK_RED */        L"\033[31m",
		/* LOG_COLOR_DARK_MAGENTA */    L"\033[35m",
		/* LOG_COLOR_DARK_YELLOW */     L"\033[33m",
		/* LOG_COLOR_DARK_GRAY */       L"\033[37m",
		/* LOG_COLOR_GRAY */            L"\033[30;1m",
		/* LOG_COLOR_BLUE */            L"\033[34;1m",
		/* LOG_COLOR_GREEN */           L"\033[32;1m",
		/* LOG_COLOR_CYAN */            L"\033[36;1m",
		/* LOG_COLOR_RED */             L"\033[31;1m",
		/* LOG_COLOR_MAGENTA */         L"\033[35;1m",
		/* LOG_COLOR_YELLOW */          L"\033[33;1m",
		/* LOG_COLOR_WHITE */           L"\033[37;1m"
	};

	const wchar_t* sLinuxBackgroundLogColors[] =
	{
		/* LOG_COLOR_DEFAULT */         L"\033[49m",
		/* LOG_COLOR_BLACK */           L"\033[40m",
		/* LOG_COLOR_DARK_BLUE */       L"\033[44m",
		/* LOG_COLOR_DARK_GREEN */      L"\033[42m",
		/* LOG_COLOR_DARK_CYAN */       L"\033[46m",
		/* LOG_COLOR_DARK_RED */        L"\033[41m",
		/* LOG_COLOR_DARK_MAGENTA */    L"\033[45m",
		/* LOG_COLOR_DARK_YELLOW */     L"\033[43m",
		/* LOG_COLOR_DARK_GRAY */       L"\033[47m",
		/* LOG_COLOR_GRAY */            L"\033[40;1m",
		/* LOG_COLOR_BLUE */            L"\033[44;1m",
		/* LOG_COLOR_GREEN */           L"\033[42;1m",
		/* LOG_COLOR_CYAN */            L"\033[46;1m",
		/* LOG_COLOR_RED */             L"\033[41;1m",
		/* LOG_COLOR_MAGENTA */         L"\033[45;1m",
		/* LOG_COLOR_YELLOW */          L"\033[43;1m",
		/* LOG_COLOR_WHITE */           L"\033[47;1m"
	};

	const wchar_t* sLinuxResetLogColor = L"\033[0;0m";

	void Log::InitLogging()
	{
		//setlocale(LC_ALL, ".utf-8");
		setlocale(LC_ALL, "en_US.UTF-8");
		wprintf(L""); // Enforce wide printing
		GetGlobalLog().SetLogLevel((LogLevel)QUARTZ_LOG_LEVEL);
	}

	void Log::Prefixed(LogLevel level, LogColor foreground, LogColor background,
		const char* severityName, const char* format, ...)
	{
		if (level < mLogLevel) return;

		static wchar_t prefixedFormat[1024]{};
		static wchar_t currentTime[26]{};

		time_t timer;
		tm* pTimeInfo;
		time(&timer);
		pTimeInfo = localtime(&timer);
		wcsftime(currentTime, 26, L"%H:%M:%S", pTimeInfo);

		const wchar_t* forgroundColor = sLinuxForegroundLogColors[(int)foreground];
		const wchar_t* backgroundColor = sLinuxBackgroundLogColors[(int)background];

		swprintf(prefixedFormat, 1024, L"%ls%ls[%ls][%s] %s\n", forgroundColor, backgroundColor, currentTime, severityName, format);

		va_list args{};
		va_start(args, format);

		vwprintf(prefixedFormat, args);
		printf("%ls", sLinuxResetLogColor);
	}

	void Log::Prefixed(LogLevel level, LogColor foreground, LogColor background,
		const char* severityName, const wchar_t* format, ...)
	{
		if (level < mLogLevel) return;

		static wchar_t prefixedFormat[1024]{};
		static wchar_t currentTime[26]{};

		time_t timer;
		tm* pTimeInfo;
		time(&timer);
		pTimeInfo = localtime(&timer);
		wcsftime(currentTime, 26, L"%H:%M:%S", pTimeInfo);

		const wchar_t* forgroundColor = sLinuxForegroundLogColors[(int)foreground];
		const wchar_t* backgroundColor = sLinuxBackgroundLogColors[(int)background];

		swprintf(prefixedFormat, 1024, L"%s%s[%s][%s] %ls\n", forgroundColor, backgroundColor, currentTime, severityName, format);

		va_list args{};
		va_start(args, format);

		vwprintf(prefixedFormat, args);
		wprintf(L"%ls", sLinuxResetLogColor);

		va_end(args);
	}

	void Log::Raw(LogColor foreground, LogColor background, const char* format, ...)
	{
		static wchar_t prefixedFormat[1024]{};

		const wchar_t* forgroundColor = sLinuxForegroundLogColors[(int)foreground];
		const wchar_t* backgroundColor = sLinuxBackgroundLogColors[(int)background];

		swprintf(prefixedFormat, 1024, L"%ls%ls%s", forgroundColor, backgroundColor, format);

		va_list args{};
		va_start(args, format);

		vwprintf(prefixedFormat, args);
		printf("%ls", sLinuxResetLogColor);

		va_end(args);
	}

	void Log::Raw(LogColor foreground, LogColor background, const wchar_t* format, ...)
	{
		const wchar_t* forgroundColor = sLinuxForegroundLogColors[(int)foreground];
		const wchar_t* backgroundColor = sLinuxBackgroundLogColors[(int)background];

		va_list args{};
		va_start(args, format);

		wprintf(L"%ls", forgroundColor);
		wprintf(L"%ls", backgroundColor);
		wprintf(format, args);
		wprintf(L"%ls", sLinuxResetLogColor);

		va_end(args);
	}
}
