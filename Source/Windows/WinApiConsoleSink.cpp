#include "Sinks/Windows/WinApiConsoleSink.h"

#include "WinApi.h"
#include <cstdio>
#include <fcntl.h>
#include <time.h>
#include <io.h>

namespace Quartz
{
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

	WinApiConsoleSink::WinApiConsoleSink() : Sink()
	{
		AllocConsole();
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		/* Enable VT100 ANSII color codes: */
		//SetConsoleMode(hConsole, ENABLE_VIRTUAL_TERMINAL_INPUT);
		//SetConsoleMode(hConsole, ENABLE_VIRTUAL_TERMINAL_PROCESSING);

		HANDLE	std     = GetStdHandle(STD_OUTPUT_HANDLE);
		int		crt     = _open_osfhandle((intptr_t)std, _O_TEXT);
		FILE*   pStream = _fdopen(crt, "w");

		/* Enable UTF16 output: */
		setvbuf(pStream, NULL, _IONBF, 1);
		_setmode(_fileno(pStream), _O_U16TEXT);

		CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
		GetConsoleScreenBufferInfo(hConsole, &consoleInfo);

		mDefaultLogColors = consoleInfo.wAttributes;
		mpOutputStream = pStream;
	}

	void WinApiConsoleSink::WritePrefixed(LogLevel level, LogColor foreground, LogColor background,
		const char* severityName, const char* format, ...) const
	{
		va_list args;
		va_start(args, format);
		WritePrefixedV(level, foreground, background, severityName, format, args);
		va_end(args);
	}

	void WinApiConsoleSink::WritePrefixedV(LogLevel level, LogColor foreground, LogColor background,
		const char* severityName, const char* format, va_list args) const
	{
		if (level < mLogLevel) return;

		static char prefixedFormat[1024]{};
		static char currentTime[26]{};

		time_t timer;
		tm timeInfo;
		time(&timer);
		localtime_s(&timeInfo, &timer);
		strftime(currentTime, 26, mPrefix, &timeInfo);

		sprintf(prefixedFormat, "[%s][%s] %s\n", currentTime, severityName, format);

		WORD forgroundColor = (foreground == LOG_COLOR_DEFAULT) ? mDefaultLogColors & 0x0F : sWin32LogColors[foreground];
		WORD backgroundColor = (background == LOG_COLOR_DEFAULT) ? mDefaultLogColors & 0xF0 : (sWin32LogColors[background] << 4) & 0xF0;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, forgroundColor | backgroundColor);

		int bufferSize = vsnprintf(NULL, 0, prefixedFormat, args);
		if (bufferSize < 0) return; // TODO: Throw error?

		char* pBuffer = new char[(LONG)bufferSize + 1]{};

		vsprintf(pBuffer, prefixedFormat, args);

		int wideBufferSize = MultiByteToWideChar(CP_UTF8, 0, pBuffer, -1, 0, 0);

		wchar_t* pWideBuffer = new wchar_t[(LONG)wideBufferSize + 1]{};

		MultiByteToWideChar(CP_UTF8, 0, pBuffer, bufferSize, pWideBuffer, wideBufferSize);

		fwprintf(mpOutputStream, pWideBuffer);

		SetConsoleTextAttribute(hConsole, mDefaultLogColors);

		delete[] pBuffer;
		delete[] pWideBuffer;
	}

	void WinApiConsoleSink::WritePrefixedW(LogLevel level, LogColor foreground, LogColor background,
		const char* severityName, const wchar_t* format, ...) const
	{
		va_list args;
		va_start(args, format);
		WritePrefixedWV(level, foreground, background, severityName, format, args);
		va_end(args);
	}

	void WinApiConsoleSink::WritePrefixedWV(LogLevel level, LogColor foreground, LogColor background,
		const char* severityName, const wchar_t* format, va_list args) const
	{
		if (level < mLogLevel) return;

		static wchar_t prefixedFormat[1024]{};
		static char currentTime[26]{};

		time_t timer;
		tm timeInfo;
		time(&timer);
		localtime_s(&timeInfo, &timer);
		strftime(currentTime, 26, mPrefix, &timeInfo);

		swprintf(prefixedFormat, L"[%S][%s] %ls\n", currentTime, severityName, format);

		WORD forgroundColor = (foreground == LOG_COLOR_DEFAULT) ? mDefaultLogColors & 0x0F : sWin32LogColors[foreground];
		WORD backgroundColor = (background == LOG_COLOR_DEFAULT) ? mDefaultLogColors & 0xF0 : (sWin32LogColors[background] << 4) & 0xF0;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, forgroundColor | backgroundColor);

		vfwprintf(mpOutputStream, prefixedFormat, args);

		SetConsoleTextAttribute(hConsole, mDefaultLogColors);
	}

	void WinApiConsoleSink::WriteRaw(LogColor foreground, LogColor background, const char* format, ...) const
	{
		va_list args;
		va_start(args, format);
		WriteRawV(foreground, background, format, args);
		va_end(args);
	}

	void WinApiConsoleSink::WriteRawV(LogColor foreground, LogColor background, const char* format, va_list args) const
	{
		WORD forgroundColor = (foreground == LOG_COLOR_DEFAULT) ? mDefaultLogColors & 0x0F : sWin32LogColors[foreground];
		WORD backgroundColor = (background == LOG_COLOR_DEFAULT) ? mDefaultLogColors & 0xF0 : (sWin32LogColors[background] << 4) & 0xF0;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, forgroundColor | backgroundColor);

		int bufferSize = vsnprintf(NULL, 0, format, args);
		if (bufferSize < 0) return; // TODO: Throw error?

		char* pBuffer = new char[(LONG)bufferSize + 1]{};

		vsprintf(pBuffer, format, args);

		int wideBufferSize = MultiByteToWideChar(CP_UTF8, 0, pBuffer, -1, 0, 0);

		wchar_t* pWideBuffer = new wchar_t[(LONG)wideBufferSize + 1]{};

		MultiByteToWideChar(CP_UTF8, 0, pBuffer, bufferSize, pWideBuffer, wideBufferSize);

		fwprintf(mpOutputStream, pWideBuffer);

		SetConsoleTextAttribute(hConsole, mDefaultLogColors);

		delete[] pBuffer;
		delete[] pWideBuffer;
	}

	void WinApiConsoleSink::WriteRawW(LogColor foreground, LogColor background, const wchar_t* format, ...) const
	{
		va_list args;
		va_start(args, format);
		WriteRawWV(foreground, background, format, args);
		va_end(args);
	}

	void WinApiConsoleSink::WriteRawWV(LogColor foreground, LogColor background, const wchar_t* format, va_list args) const
	{
		WORD forgroundColor = (foreground == LOG_COLOR_DEFAULT) ? mDefaultLogColors & 0x0F : sWin32LogColors[foreground];
		WORD backgroundColor = (background == LOG_COLOR_DEFAULT) ? mDefaultLogColors & 0xF0 : (sWin32LogColors[background] << 4) & 0xF0;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, forgroundColor | backgroundColor);

		vfwprintf(mpOutputStream, format, args);

		SetConsoleTextAttribute(hConsole, mDefaultLogColors);
	}

	bool WinApiConsoleSink::SupportsEscapeColors() const
	{
		// TODO: windows feature/version check?
		return true;
	}
}