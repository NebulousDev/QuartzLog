#include "Log.h"

namespace Quartz
{
	void Log::RunLogTest()
	{
		LogRaw(LOG_COLOR_YELLOW, LOG_COLOR_DEFAULT, "\n > Starting Log Tests...\n");

		LogRaw(LOG_COLOR_CYAN, LOG_COLOR_DEFAULT, "\n   -- Severity Tests: --   \n");
		LogTest("   This is a TEST message.");
		LogDebug("  This is a DEBUG message.");
		LogTrace("  This is a TRACE message.");
		LogInfo("   This is an INFO message.");
		LogWarning("This is a WARNING message.");
		LogError("  This is an ERROR message.");
		LogFatal("  This is a FATAL message.");
		LogRaw(LOG_COLOR_DARK_YELLOW, LOG_COLOR_DEFAULT, "%s", "                    This is a RAW message.\n");

		LogRaw(LOG_COLOR_CYAN, LOG_COLOR_DEFAULT, "\n   -- Unicode Tests: --   \n");
		LogRaw(LOG_COLOR_CYAN, LOG_COLOR_DEFAULT, L" · English:  The Quick Brown Fox Jumps Over The Lazy Dog.\n");
		LogRaw(LOG_COLOR_CYAN, LOG_COLOR_DEFAULT, L" · Spanish:  Benjamín pidió una bebida de kiwi y fresa; Noé, sin vergüenza, la más exquisita champaña del menú.\n");
		LogRaw(LOG_COLOR_CYAN, LOG_COLOR_DEFAULT, L" · Polish:   Pchnąć w tę łódź jeża lub ośm skrzyń fig.\n");
		LogRaw(LOG_COLOR_CYAN, LOG_COLOR_DEFAULT, L" · Greek:    Ταχίστη αλώπηξ βαφής ψημένη γη, δρασκελίζει υπέρ νωθρού κυνός Takhístè alôpèx vaphês psèménè gè, draskelízei ypér nòthroý kynós\n");
		LogRaw(LOG_COLOR_CYAN, LOG_COLOR_DEFAULT, L" · Russian:  Съешь ещё этих мягких французских булок, да выпей же чаю.\n");
		LogRaw(LOG_COLOR_CYAN, LOG_COLOR_DEFAULT, L" · Japanese: 色は匂へど 散りぬるを 我が世誰ぞ 常ならむ 有為の奥山 今日越えて 浅き夢見じ 酔ひもせず\n");

		LogRaw(LOG_COLOR_CYAN, LOG_COLOR_DEFAULT, "\n   -- Color Tests: --   \n");
		LogRaw(LOG_COLOR_DEFAULT,      LOG_COLOR_DEFAULT,       " Foreground Color: ");
		LogRaw(LOG_COLOR_BLACK,        LOG_COLOR_DEFAULT,       "F");
		LogRaw(LOG_COLOR_DARK_BLUE,    LOG_COLOR_DEFAULT,       "o");
		LogRaw(LOG_COLOR_DARK_GREEN,   LOG_COLOR_DEFAULT,       "r");
		LogRaw(LOG_COLOR_DARK_CYAN,    LOG_COLOR_DEFAULT,       "e");
		LogRaw(LOG_COLOR_DARK_RED,     LOG_COLOR_DEFAULT,       "g");
		LogRaw(LOG_COLOR_DARK_MAGENTA, LOG_COLOR_DEFAULT,       "r");
		LogRaw(LOG_COLOR_DARK_YELLOW,  LOG_COLOR_DEFAULT,       "o");
		LogRaw(LOG_COLOR_DARK_GRAY,    LOG_COLOR_DEFAULT,       "u");
		LogRaw(LOG_COLOR_GRAY,         LOG_COLOR_DEFAULT,       "n");
		LogRaw(LOG_COLOR_BLUE,         LOG_COLOR_DEFAULT,       "d");
		LogRaw(LOG_COLOR_GREEN,        LOG_COLOR_DEFAULT,       " ");
		LogRaw(LOG_COLOR_CYAN,         LOG_COLOR_DEFAULT,       "C");
		LogRaw(LOG_COLOR_RED,          LOG_COLOR_DEFAULT,       "o");
		LogRaw(LOG_COLOR_MAGENTA,      LOG_COLOR_DEFAULT,       "l");
		LogRaw(LOG_COLOR_YELLOW,       LOG_COLOR_DEFAULT,       "o");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_DEFAULT,       "r\n");

		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_DEFAULT,       " Background Color: ");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_BLACK,         "B");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_DARK_BLUE,     "a");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_DARK_GREEN,    "c");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_DARK_CYAN,     "k");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_DARK_RED,      "g");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_DARK_MAGENTA,  "r");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_DARK_YELLOW,   "o");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_DARK_GRAY,     "u");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_GRAY,          "n");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_BLUE,          "d");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_GREEN,         " ");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_CYAN,          "C");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_RED,           "o");
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_MAGENTA,       "l");
		LogRaw(LOG_COLOR_BLACK,        LOG_COLOR_YELLOW,        "o");
		LogRaw(LOG_COLOR_BLACK,        LOG_COLOR_WHITE,         "r\n");

		LogRaw(LOG_COLOR_YELLOW, LOG_COLOR_DEFAULT, "\n > Log Tests Complete.\n\n");
	}
}
