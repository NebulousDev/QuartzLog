#include "Log.h"

#include <cstdarg>
#include <time.h>
#include <memory>
#include <cstring>

namespace Quartz
{
	Log* spLog = nullptr;

	Log::Log(const Array<Sink*>& sinks) :
		mSinks(sinks) { }

	Log& Log::GetInstance()
	{
		return *spLog;
	}

	void Log::SetInstance(Log& logger)
	{
		spLog = &logger;
	}

	// TODO: PLEASE optimize.
	uSize Log::ParseFormat(const LogSeverity& severity, char* pBuffer, 
		uSize bufferSize, tm time, const char* format, const char* text)
	{
		char* pBuffItr = pBuffer;

		for (
			const char* chr = format;
			*chr != '\0' || (pBuffItr == pBuffer + bufferSize); // Stop at end of format or end of buffer
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

				if (*chr == 'F' && *(chr + 1) == 'G')
				{
					const char* fgColor = severity.GetForegroundColor();
					const uSize length = severity.GetForegroundColorSize() - 1;
					memcpy_s(pBuffItr, ((pBuffer + bufferSize) - pBuffItr - 1), fgColor, length);
					pBuffItr += length;
					chr++;
				}

				else if (*chr == 'B' && *(chr + 1) == 'G')
				{
					const char* bgColor = severity.GetBackgroundColor();
					const uSize length = severity.GetBackgroundColorSize() - 1;
					memcpy_s(pBuffItr, ((pBuffer + bufferSize) - pBuffItr - 1), bgColor, length);
					pBuffItr += length;
					chr++;
				}

				else if (*chr == 'H')
				{
					pBuffItr += strftime(pBuffItr, ((pBuffer + bufferSize) - pBuffItr - 1), "%H", &time);
				}

				else if (*chr == 'M')
				{
					pBuffItr += strftime(pBuffItr, ((pBuffer + bufferSize) - pBuffItr - 1), "%M", &time);
				}

				else if (*chr == 'S')
				{
					pBuffItr += strftime(pBuffItr, ((pBuffer + bufferSize) - pBuffItr - 1), "%S", &time);
				}

				else if (*chr == 'V')
				{
					const char* sevText = severity.GetText();
					const uSize length = severity.GetTextSize() - 1;
					int size = ((pBuffer + bufferSize) - pBuffItr - 1);
					int val = memcpy_s(pBuffItr, size, sevText, length);
					pBuffItr += length;
				}

				else if (*chr == 'T')
				{
					const uSize length = strlen(text);
					int size = ((pBuffer + bufferSize) - pBuffItr - 1);
					int val = memcpy_s(pBuffItr, size, text, length);
					pBuffItr += length;
				}
			}

			else
			{
				*pBuffItr = *chr;
				pBuffItr++;
			}
		}

		*(pBuffItr) = '\0';

		return pBuffItr - pBuffer;
	}

	uSize Log::ParseFormat(const LogSeverity& severity, wchar_t* pBuffer, 
		uSize bufferSize, tm time, const char* format, const wchar_t* wtext)
	{
		wchar_t* pBuffItr = pBuffer;
		wchar_t wformatBuffer[4096]{};

		for (
			const char* chr = format;
			*chr != '\0' || (pBuffItr == pBuffer + bufferSize); // Stop at end of format or end of buffer
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

				if (*chr == 'F' && *(chr + 1) == 'G')
				{
					const char* fgColor = severity.GetForegroundColor();
					const uSize length = severity.GetForegroundColorSize() - 1;
					mbstowcs(wformatBuffer, fgColor, length);
					memcpy_s(pBuffItr, ((pBuffer + bufferSize) - pBuffItr - 1), wformatBuffer, length * sizeof(wchar_t));
					pBuffItr += length;
					chr++;
				}

				else if (*chr == 'B' && *(chr + 1) == 'G')
				{
					const char* bgColor = severity.GetBackgroundColor();
					const uSize length = severity.GetBackgroundColorSize() - 1;
					mbstowcs(wformatBuffer, bgColor, length);
					memcpy_s(pBuffItr, ((pBuffer + bufferSize) - pBuffItr - 1), wformatBuffer, length * sizeof(wchar_t));
					pBuffItr += length;
					chr++;
				}

				else if (*chr == 'H')
				{
					pBuffItr += wcsftime(pBuffItr, ((pBuffer + bufferSize) - pBuffItr - 1), L"%H", &time);
				}

				else if (*chr == 'M')
				{
					pBuffItr += wcsftime(pBuffItr, ((pBuffer + bufferSize) - pBuffItr - 1), L"%M", &time);
				}

				else if (*chr == 'S')
				{
					pBuffItr += wcsftime(pBuffItr, ((pBuffer + bufferSize) - pBuffItr - 1), L"%S", &time);
				}

				else if (*chr == 'V')
				{
					const char* sevText = severity.GetText();
					const uSize length = severity.GetTextSize() - 1;
					mbstowcs(wformatBuffer, sevText, length);
					int size = ((pBuffer + bufferSize) - pBuffItr - 1);
					int val = memcpy_s(pBuffItr, size, wformatBuffer, length * sizeof(wchar_t));
					pBuffItr += length;
				}

				else if (*chr == 'T')
				{
					const uSize length = wcslen(wtext);
					int size = ((pBuffer + bufferSize) - pBuffItr - 1);
					int val = memcpy_s(pBuffItr, size, wtext, length * sizeof(wchar_t));
					pBuffItr += length;
				}
			}

			else
			{
				uInt16 wchar = *chr;
				*pBuffItr = (wchar_t)wchar;
				pBuffItr++;
			}
		}

		*(pBuffItr) = '\0';

		return pBuffItr - pBuffer;
	}
}
