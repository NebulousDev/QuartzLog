#include "Log.h"

#include <cstdio>
#include <cstdarg>
#include <time.h>
#include <fcntl.h>
#include <io.h>
#include <locale.h>

#include <Windows.h>

namespace Quartz
{
	WORD sDefaultLogColors = 0;
	FILE* spOutputStream = 0;

	WORD sWin32LogColors[] =
	{
		/* LOG_COLOR_DEFAULT */         0,
		/* LOG_COLOR_BLACK */           0x0,
		/* LOG_COLOR_DARK_BLUE */       FOREGROUND_BLUE,
		/* LOG_COLOR_DARK_GREEN */      FOREGROUND_GREEN,
		/* LOG_COLOR_DARK_CYAN */       FOREGROUND_GREEN | FOREGROUND_BLUE,
		/* LOG_COLOR_DARK_RED */        FOREGROUND_RED,
		/* LOG_COLOR_DARK_MAGENTA */    FOREGROUND_RED | FOREGROUND_BLUE,
		/* LOG_COLOR_DARK_YELLOW */     FOREGROUND_RED | FOREGROUND_GREEN,
		/* LOG_COLOR_DARK_GRAY */       0x8,
		/* LOG_COLOR_GRAY */            0x7,
		/* LOG_COLOR_BLUE */            FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		/* LOG_COLOR_GREEN */           FOREGROUND_GREEN | FOREGROUND_INTENSITY,
		/* LOG_COLOR_CYAN */            FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		/* LOG_COLOR_RED */             FOREGROUND_RED | FOREGROUND_INTENSITY,
		/* LOG_COLOR_MAGENTA */         FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		/* LOG_COLOR_YELLOW */          FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
		/* LOG_COLOR_WHITE */           FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	};

	void Log::InitLogging()
	{
		AllocConsole();

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
		GetConsoleScreenBufferInfo(hConsole, &consoleInfo);

		HANDLE	std		= GetStdHandle(STD_OUTPUT_HANDLE);
		int		crt		= _open_osfhandle((intptr_t)std, _O_TEXT);
		FILE*	pStream = _fdopen(crt, "w");

		setvbuf(pStream, NULL, _IONBF, 1);
		_setmode(_fileno(pStream), _O_U16TEXT);

		sDefaultLogColors = consoleInfo.wAttributes;
		spOutputStream = pStream;

		GetGlobalLog().SetLogLevel((LogLevel)QUARTZ_LOG_LEVEL);
	}

	void Log::Prefixed(LogLevel level, LogColor foreground, LogColor background, 
		const char* severityName, const char* format, ...)
	{
		if (level < mLogLevel) return;

		static char prefixedFormat[1024] {};
		static char currentTime[26] {};

		time_t timer;
		tm timeInfo;
		time(&timer);
		localtime_s(&timeInfo, &timer);
		strftime(currentTime, 26, "%H:%M:%S", &timeInfo);

		sprintf(prefixedFormat, "[%s][%s] %s\n", currentTime, severityName, format);

		WORD forgroundColor = (foreground == LOG_COLOR_DEFAULT) ? sDefaultLogColors & 0x0F : sWin32LogColors[foreground];
		WORD backgroundColor = (background == LOG_COLOR_DEFAULT) ? sDefaultLogColors & 0xF0 : (sWin32LogColors[background] << 4) & 0xF0;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, forgroundColor | backgroundColor);

		va_list args;

		va_start(args, format);
		int bufferSize = vsnprintf(NULL, 0, prefixedFormat, args);
		if (bufferSize < 0) return; // TODO: Throw error?

		char* pBuffer = new char[(LONG)bufferSize + 1]{};

		va_start(args, format);
		vsprintf(pBuffer, prefixedFormat, args);

		int wideBufferSize = MultiByteToWideChar(CP_UTF8, 0, pBuffer, -1, 0, 0);

		wchar_t* pWideBuffer = new wchar_t[(LONG)wideBufferSize + 1]{};

		MultiByteToWideChar(CP_UTF8, 0, pBuffer, bufferSize, pWideBuffer, wideBufferSize);

		fwprintf(spOutputStream, pWideBuffer);

		va_end(args);

		SetConsoleTextAttribute(hConsole, sDefaultLogColors);

		delete[] pBuffer;
		delete[] pWideBuffer;
	}

	void Log::Prefixed(LogLevel level, LogColor foreground, LogColor background, const char* severityName, const wchar_t* format, ...)
	{
		if (level < mLogLevel) return;

		static wchar_t prefixedFormat[1024]{};
		static wchar_t currentTime[26]{};

		time_t timer;
		tm timeInfo;
		time(&timer);
		localtime_s(&timeInfo, &timer);
		wcsftime(currentTime, 26, L"%H:%M:%S", &timeInfo);

		swprintf(prefixedFormat, L"[%s][%s] %ls\n", currentTime, severityName, format);

		WORD forgroundColor = (foreground == LOG_COLOR_DEFAULT) ? sDefaultLogColors & 0x0F : sWin32LogColors[foreground];
		WORD backgroundColor = (background == LOG_COLOR_DEFAULT) ? sDefaultLogColors & 0xF0 : (sWin32LogColors[background] << 4) & 0xF0;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, forgroundColor | backgroundColor);

		va_list args;
		va_start(args, format);

		vfwprintf(spOutputStream, prefixedFormat, args);

		va_end(args);

		SetConsoleTextAttribute(hConsole, sDefaultLogColors);
	}

	void Log::Raw(LogColor foreground, LogColor background, const char* format, ...)
	{
		WORD forgroundColor = (foreground == LOG_COLOR_DEFAULT) ? sDefaultLogColors & 0x0F : sWin32LogColors[foreground];
		WORD backgroundColor = (background == LOG_COLOR_DEFAULT) ? sDefaultLogColors & 0xF0 : (sWin32LogColors[background] << 4) & 0xF0;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, forgroundColor | backgroundColor);

		va_list args;

		va_start(args, format);
		int bufferSize = vsnprintf(NULL, 0, format, args);
		if (bufferSize < 0) return; // TODO: Throw error?

		char* pBuffer = new char[(LONG)bufferSize + 1]{};

		va_start(args, format);
		vsprintf(pBuffer, format, args);

		int wideBufferSize = MultiByteToWideChar(CP_UTF8, 0, pBuffer, -1, 0, 0);

		wchar_t* pWideBuffer = new wchar_t[(LONG)wideBufferSize + 1]{};

		MultiByteToWideChar(CP_UTF8, 0, pBuffer, bufferSize, pWideBuffer, wideBufferSize);

		fwprintf(spOutputStream, pWideBuffer);

		va_end(args);

		SetConsoleTextAttribute(hConsole, sDefaultLogColors);

		delete[] pBuffer;
		delete[] pWideBuffer;
	}

	void Log::Raw(LogColor foreground, LogColor background, const wchar_t* format, ...)
	{
		WORD forgroundColor = (foreground == LOG_COLOR_DEFAULT) ? sDefaultLogColors & 0x0F : sWin32LogColors[foreground];
		WORD backgroundColor = (background == LOG_COLOR_DEFAULT) ? sDefaultLogColors & 0xF0 : (sWin32LogColors[background] << 4) & 0xF0;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, forgroundColor | backgroundColor);

		va_list args;
		va_start(args, format);

		vfwprintf(spOutputStream, format, args);

		va_end(args);

		SetConsoleTextAttribute(hConsole, sDefaultLogColors);
	}
}
