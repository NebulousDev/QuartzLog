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

		LogRaw(LOG_COLOR_CYAN, LOG_COLOR_DEFAULT, u8" \u00B7 English:  The Quick Brown Fox Jumps Over The Lazy Dog\n");
		LogRaw(LOG_COLOR_CYAN, LOG_COLOR_DEFAULT, u8" \u00B7 Spanish:  Benjam\u00EDn pidi\u00F3 una bebida de kiwi y fresa; No\u00E9, sin verg\u00FCenza, la m\u00E1s exquisita champa\u00F1a del men\u00FA\n");
		LogRaw(LOG_COLOR_CYAN, LOG_COLOR_DEFAULT, u8" \u00B7 Polish:   Pchn\u0105\u0107 w t\u0119 \u0142\u00F3d\u017A je\u017Ca lub o\u015Bm skrzy\u0144 fig\n");
		LogRaw(LOG_COLOR_CYAN, LOG_COLOR_DEFAULT, u8" \u00B7 Greek:    \u03A4\u03B1\u03C7\u03AF\u03C3\u03C4\u03B7 \u03B1\u03BB\u03CE\u03C0\u03B7\u03BE \u03B2\u03B1\u03C6\u03AE\u03C2 \u03C8\u03B7\u03BC\u03AD\u03BD\u03B7 \u03B3\u03B7, \u03B4\u03C1\u03B1\u03C3\u03BA\u03B5\u03BB\u03AF\u03B6\u03B5\u03B9 \u03C5\u03C0\u03AD\u03C1 \u03BD\u03C9\u03B8\u03C1\u03BF\u03CD \u03BA\u03C5\u03BD\u03CC\u03C2\n");
		LogRaw(LOG_COLOR_CYAN, LOG_COLOR_DEFAULT, u8" \u00B7 Russian:  \u0421\u044A\u0435\u0448\u044C \u0435\u0449\u0451 \u044D\u0442\u0438\u0445 \u043C\u044F\u0433\u043A\u0438\u0445 \u0444\u0440\u0430\u043D\u0446\u0443\u0437\u0441\u043A\u0438\u0445 \u0431\u0443\u043B\u043E\u043A, \u0434\u0430 \u0432\u044B\u043F\u0435\u0439 \u0436\u0435 \u0447\u0430\u044E\n");
		LogRaw(LOG_COLOR_CYAN, LOG_COLOR_DEFAULT, u8" \u00B7 Japanese: \u8272\u306F\u5302\u3078\u3069 \u6563\u308A\u306C\u308B\u3092 \u6211\u304C\u4E16\u8AB0\u305E \u5E38\u306A\u3089\u3080 \u6709\u70BA\u306E\u5965\u5C71 \u4ECA\u65E5\u8D8A\u3048\u3066 \u6D45\u304D\u5922\u898B\u3058 \u9154\u3072\u3082\u305B\u305A\n");

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
		LogRaw(LOG_COLOR_WHITE,        LOG_COLOR_DEFAULT,       "r");
		LogRaw(LOG_COLOR_DEFAULT,	   LOG_COLOR_DEFAULT,       "\n");

		LogRaw(LOG_COLOR_DEFAULT,      LOG_COLOR_DEFAULT,       " Background Color: ");
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
		LogRaw(LOG_COLOR_BLACK,        LOG_COLOR_WHITE,         "r");
		LogRaw(LOG_COLOR_DEFAULT,	   LOG_COLOR_DEFAULT,       "\n");

		LogRaw(LOG_COLOR_YELLOW, LOG_COLOR_DEFAULT, "\n > Log Tests Complete.\n\n");
	}
}
