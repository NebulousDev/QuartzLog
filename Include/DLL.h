#ifdef QUARTZLOG_DLL

#ifdef _WIN32

#define QUARTZLOG_API __declspec(dllexport)

#elif defined __GNUC__

#define QUARTZLOG_API __attribute__ ((visibility ("default")))

#else

#define QUARTZLOG_API

#endif

#elif defined QUARTZLOG_STATIC

#define QUARTZLOG_API

#else

#ifdef _WIN32

#define QUARTZLOG_API __declspec(dllimport)

#elif defined __GNUC__

#define QUARTZLOG_API

#else

#define QUARTZLOG_API

#endif

#endif