#include "Sinks/Windows/WinApiConsoleSink.h"

#include "Log.h"
#include "WinApi.h"
#include <cstdio>
#include <fcntl.h>
#include <time.h>
#include <io.h>

namespace Quartz
{
	WinApiConsoleSink::WinApiConsoleSink() : Sink()
	{
		AllocConsole();
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

#if defined(QUARTZLOG_COLORS) && defined(QUARTZLOG_ANSI)

		/* Enable VT100 ANSI color codes: */
		DWORD dwConsoleMode;
		GetConsoleMode(hConsole, &dwConsoleMode);
		SetConsoleMode(hConsole, dwConsoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

#endif

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
		mhConsole = (void*)hConsole;
	}

	void WinApiConsoleSink::WritePrefixed(const LogSeverity& severity, const char* format, ...) const
	{
		va_list args;
		va_start(args, format);
		WritePrefixedV(severity, format, args);
		va_end(args);
	}

	void WinApiConsoleSink::WritePrefixed(const LogSeverity& severity, const wchar_t* wformat, ...) const
	{
		va_list args;
		va_start(args, wformat);
		WritePrefixedV(severity, wformat, args);
		va_end(args);
	}

	void WinApiConsoleSink::WritePrefixedV(const LogSeverity& severity, const char* format, va_list args) const
	{
		if (severity.GetLevel() < mLogLevel) return;

		static char prefixBuffer[1024]{};

		time_t timer;
		tm timeInfo;
		time(&timer);
		localtime_s(&timeInfo, &timer);

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		uSize bytes = Log::ParseFormat(severity, prefixBuffer, 1024, timeInfo, mFormat, format);

		uSize bufferSize = vsnprintf(NULL, 0, prefixBuffer, args);
		if (bufferSize < 0) return; // TODO: Throw error?

		char* pBuffer = new char[(LONG)bufferSize + 1]{};

		vsprintf(pBuffer, prefixBuffer, args);

		uSize wideBufferSize = MultiByteToWideChar(CP_UTF8, 0, pBuffer, -1, 0, 0);

		wchar_t* pWideBuffer = new wchar_t[(LONG)wideBufferSize + 1]{};

		MultiByteToWideChar(CP_UTF8, 0, pBuffer, bufferSize, pWideBuffer, wideBufferSize);

		WriteConsoleW(hConsole, pWideBuffer, wideBufferSize + 1, NULL, NULL);

		delete[] pBuffer;
		delete[] pWideBuffer;
	}

	void WinApiConsoleSink::WritePrefixedV(const LogSeverity& severity, const wchar_t* wformat, va_list args) const
	{
		if (severity.GetLevel() < mLogLevel) return;

		static wchar_t prefixBuffer[1024]{};

		time_t timer;
		tm timeInfo;
		time(&timer);
		localtime_s(&timeInfo, &timer);

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		uSize bytes = Log::ParseFormat(severity, prefixBuffer, 1024, timeInfo, mFormat, wformat);

		uSize bufferSize = _vsnwprintf(NULL, 0, prefixBuffer, args);
		if (bufferSize < 0) return; // TODO: Throw error?

		wchar_t* pBuffer = new wchar_t[(LONG)bufferSize + 1]{};

		wvsprintfW(pBuffer, prefixBuffer, args);

		WriteConsoleW(hConsole, pBuffer, bufferSize + 1, NULL, NULL);

		delete[] pBuffer;
	}

	void WinApiConsoleSink::WriteRaw(const char* format, ...) const
	{
		va_list args;
		va_start(args, format);
		WriteRawV(format, args);
		va_end(args);
	}

	void WinApiConsoleSink::WriteRaw(const wchar_t* wformat, ...) const
	{
		va_list args;
		va_start(args, wformat);
		WriteRawV(wformat, args);
		va_end(args);
	}

	void WinApiConsoleSink::WriteRawV(const char* format, va_list args) const
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		uSize bufferSize = vsnprintf(NULL, 0, format, args);
		if (bufferSize < 0) return; // TODO: Throw error?

		char* pBuffer = new char[(LONG)bufferSize + 1]{};

		vsprintf(pBuffer, format, args);

		uSize wideBufferSize = MultiByteToWideChar(CP_UTF8, 0, pBuffer, -1, 0, 0);

		wchar_t* pWideBuffer = new wchar_t[(LONG)wideBufferSize + 1]{};

		MultiByteToWideChar(CP_UTF8, 0, pBuffer, bufferSize, pWideBuffer, wideBufferSize);

		WriteConsoleW(hConsole, pWideBuffer, wideBufferSize + 1, NULL, NULL);

		delete[] pBuffer;
		delete[] pWideBuffer;
	}

	void WinApiConsoleSink::WriteRawV(const wchar_t* wformat, va_list args) const
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		uSize bufferSize = _vsnwprintf(NULL, 0, wformat, args);
		if (bufferSize < 0) return; // TODO: Throw error?

		wchar_t* pBuffer = new wchar_t[(LONG)bufferSize + 1] {};

		wvsprintfW(pBuffer, wformat, args);

		WriteConsoleW(hConsole, pBuffer, bufferSize + 1, NULL, NULL);

		delete[] pBuffer;
	}

	bool WinApiConsoleSink::SupportsEscapeColors() const
	{
		// TODO: windows feature/version check?
		return true;
	}
}