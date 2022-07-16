#pragma once

#include "Types/String.h"

namespace Quartz
{
#if defined(QUARTZLOG_COLORS) && defined(QUARTZLOG_ANSI)

	#define LOG_NONE             u8""

	#define LOG_RGB(r, g, b)     u8"\033[38;2;" #r ";" #g ";" #b "m"
	#define LOG_BG_RGB(r, g, b)  u8"\033[48;2;" #r ";" #g ";" #b "m"

	#define LOG_DEFAULT          u8"\033[39m"
	#define LOG_BLACK            u8"\033[30m"
	#define LOG_DARK_BLUE        u8"\033[34m"
	#define LOG_DARK_GREEN       u8"\033[32m"
	#define LOG_DARK_CYAN        u8"\033[36m"
	#define LOG_DARK_RED         u8"\033[31m"
	#define LOG_DARK_MAGENTA     u8"\033[35m"
	#define LOG_DARK_YELLOW      u8"\033[33m"
	#define LOG_DARK_GRAY        u8"\033[37m"
	#define LOG_GRAY             u8"\033[30;1m"
	#define LOG_BLUE             u8"\033[34;1m"
	#define LOG_GREEN            u8"\033[32;1m"
	#define LOG_CYAN             u8"\033[36;1m"
	#define LOG_RED              u8"\033[31;1m"
	#define LOG_MAGENTA          u8"\033[35;1m"
	#define LOG_YELLOW           u8"\033[33;1m"
	#define LOG_WHITE            u8"\033[37;1m"

	#define LOG_BG_DEFAULT       u8"\033[49m"
	#define LOG_BG_BLACK         u8"\033[40m"
	#define LOG_BG_DARK_BLUE     u8"\033[44m"
	#define LOG_BG_DARK_GREEN    u8"\033[42m"
	#define LOG_BG_DARK_CYAN     u8"\033[46m"
	#define LOG_BG_DARK_RED      u8"\033[41m"
	#define LOG_BG_DARK_MAGENTA  u8"\033[45m"
	#define LOG_BG_DARK_YELLOW   u8"\033[43m"
	#define LOG_BG_DARK_GRAY     u8"\033[47m"
	#define LOG_BG_GRAY          u8"\033[40;1m"
	#define LOG_BG_BLUE          u8"\033[44;1m"
	#define LOG_BG_GREEN         u8"\033[42;1m"
	#define LOG_BG_CYAN          u8"\033[46;1m"
	#define LOG_BG_RED           u8"\033[41;1m"
	#define LOG_BG_MAGENTA       u8"\033[45;1m"
	#define LOG_BG_YELLOW        u8"\033[43;1m"
	#define LOG_BG_WHITE         u8"\033[47;1m"
							     
	#define LOG_BOLD             u8"\033[1m"
	#define LOG_ITALIC           u8"\033[3m"
	#define LOG_UNDERLINE        u8"\033[4m"
	#define LOG_STRIKE           u8"\033[9m"

	#define LOG_RESET            u8"\033[0m"

#else

	#define LOG_RGB(r, g, b)     u8""
	#define LOG_BG_RGB(r, g, b)  u8""

	#define LOG_DEFAULT          u8""
	#define LOG_BLACK            u8""
	#define LOG_DARK_BLUE        u8""
	#define LOG_DARK_GREEN       u8""
	#define LOG_DARK_CYAN        u8""
	#define LOG_DARK_RED         u8""
	#define LOG_DARK_MAGENTA     u8""
	#define LOG_DARK_YELLOW      u8""
	#define LOG_DARK_GRAY        u8""
	#define LOG_GRAY             u8""
	#define LOG_BLUE             u8""
	#define LOG_GREEN            u8""
	#define LOG_CYAN             u8""
	#define LOG_RED              u8""
	#define LOG_MAGENTA          u8""
	#define LOG_YELLOW           u8""
	#define LOG_WHITE            u8""

	#define LOG_BG_DEFAULT       u8""
	#define LOG_BG_BLACK         u8""
	#define LOG_BG_DARK_BLUE     u8""
	#define LOG_BG_DARK_GREEN    u8""
	#define LOG_BG_DARK_CYAN     u8""
	#define LOG_BG_DARK_RED      u8""
	#define LOG_BG_DARK_MAGENTA  u8""
	#define LOG_BG_DARK_YELLOW   u8""
	#define LOG_BG_DARK_GRAY     u8""
	#define LOG_BG_GRAY          u8""
	#define LOG_BG_BLUE          u8""
	#define LOG_BG_GREEN         u8""
	#define LOG_BG_CYAN          u8""
	#define LOG_BG_RED           u8""
	#define LOG_BG_MAGENTA       u8""
	#define LOG_BG_YELLOW        u8""
	#define LOG_BG_WHITE         u8""
							     
	#define LOG_BOLD             u8""
	#define LOG_ITALIC           u8""
	#define LOG_UNDERLINE        u8""
	#define LOG_STRIKE           u8""

	#define LOG_RESET            u8""

#endif

	using LogColor = const char*;
}