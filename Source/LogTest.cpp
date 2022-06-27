#include "Log.h"

namespace Quartz
{
	void Log::RunLogTest()
	{
		LogTest("%s", "LogTest: This is a TEST message.");
		LogDebug("%s", "LogTest: This is a DEBUG message.");
		LogTrace("%s", "LogTest: This is a TRACE message.");
		LogInfo("%s", "LogTest: This is an INFO message.");
		LogWarning("%s", "LogTest: This is a WARNING message.");
		LogError("%s", "LogTest: This is an ERROR message.");
		LogFatal("%s", "LogTest: This is a FATAL message.");
		LogRaw(LOG_COLOR_CYAN, LOG_COLOR_DEFAULT, "%s", "LogTest: This is a RAW message.\n");

		LogTest(L"%ls", L"LogTest: This is a unicode message\n -- English Español Русский Ελληνικά 日本語 中文 -- ");

		LogRaw(LOG_COLOR_DEFAULT,      LOG_COLOR_DEFAULT,       "Log Test: Forground Color DEFAULT.\n");
		LogRaw(LOG_COLOR_BLACK,        LOG_COLOR_DEFAULT,       "Log Test: Forground Color BLACK.\n");
		LogRaw(LOG_COLOR_DARK_BLUE,    LOG_COLOR_DEFAULT,       "Log Test: Forground Color DARK_BLUE.\n");
		LogRaw(LOG_COLOR_DARK_GREEN,   LOG_COLOR_DEFAULT,       "Log Test: Forground Color DARK_GREEN.\n");
		LogRaw(LOG_COLOR_DARK_CYAN,    LOG_COLOR_DEFAULT,       "Log Test: Forground Color DARK_CYAN.\n");
		LogRaw(LOG_COLOR_DARK_RED,     LOG_COLOR_DEFAULT,       "Log Test: Forground Color DARK_RED.\n");
		LogRaw(LOG_COLOR_DARK_MAGENTA, LOG_COLOR_DEFAULT,       "Log Test: Forground Color DARK_MAGENTA.\n");
		LogRaw(LOG_COLOR_DARK_YELLOW,  LOG_COLOR_DEFAULT,       "Log Test: Forground Color DARK_YELLOW.\n");
		LogRaw(LOG_COLOR_DARK_GRAY,    LOG_COLOR_DEFAULT,       "Log Test: Forground Color DARK_GRAY.\n");
		LogRaw(LOG_COLOR_GRAY,         LOG_COLOR_DEFAULT,       "Log Test: Forground Color GRAY.\n");
		LogRaw(LOG_COLOR_BLUE,         LOG_COLOR_DEFAULT,       "Log Test: Forground Color BLUE.\n");
		LogRaw(LOG_COLOR_GREEN,        LOG_COLOR_DEFAULT,       "Log Test: Forground Color GREEN.\n");
		LogRaw(LOG_COLOR_CYAN,         LOG_COLOR_DEFAULT,       "Log Test: Forground Color CYAN.\n");
		LogRaw(LOG_COLOR_RED,          LOG_COLOR_DEFAULT,       "Log Test: Forground Color RED.\n");
		LogRaw(LOG_COLOR_MAGENTA,      LOG_COLOR_DEFAULT,       "Log Test: Forground Color MAGENTA.\n");
		LogRaw(LOG_COLOR_YELLOW,       LOG_COLOR_DEFAULT,       "Log Test: Forground Color YELLOW.\n");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_DEFAULT,       "Log Test: Forground Color WHITE.\n");

		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_DEFAULT,       "Log Test: Background Color DEFAULT.\n");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_BLACK,         "Log Test: Background Color BLACK.\n");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_DARK_BLUE,     "Log Test: Background Color DARK_BLUE.\n");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_DARK_GREEN,    "Log Test: Background Color DARK_GREEN.\n");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_DARK_CYAN,     "Log Test: Background Color DARK_CYAN.\n");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_DARK_RED,      "Log Test: Background Color DARK_RED.\n");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_DARK_MAGENTA,  "Log Test: Background Color DARK_MAGENTA.\n");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_DARK_YELLOW,   "Log Test: Background Color DARK_YELLOW.\n");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_DARK_GRAY,     "Log Test: Background Color DARK_GRAY.\n");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_GRAY,          "Log Test: Background Color GRAY.\n");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_BLUE,          "Log Test: Background Color BLUE.\n");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_GREEN,         "Log Test: Background Color GREEN.\n");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_CYAN,          "Log Test: Background Color CYAN.\n");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_RED,           "Log Test: Background Color RED.\n");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_MAGENTA,       "Log Test: Background Color MAGENTA.\n");
		LogRaw(LOG_COLOR_BLACK,        LOG_COLOR_YELLOW,        "Log Test: Background Color YELLOW.\n");
		LogRaw(LOG_COLOR_BLACK,        LOG_COLOR_WHITE,         "Log Test: Background Color WHITE.\n");
	}
}
