#include "precompiled.h"

void NORETURN UTIL_SysError(const char *fmt, ...)
{
	va_list argptr;
	char string[8192];

	va_start(argptr, fmt);
	vsnprintf(string, sizeof(string), fmt, argptr);
	va_end(argptr);

	printf("%s\n", string);

	//TerminateProcess(GetCurrentProcess(), 1);

	volatile int *null = 0;
	*null = 0;
	exit(-1);
}

char *UTIL_VarArgs(char *format, ...)
{
	va_list argptr;
	static char string[1024];

	va_start(argptr, format);
	vsprintf(string, format, argptr);
	va_end(argptr);

	return string;
}

void UTIL_LogPrintf(const char *fmt, ...)
{
	va_list argptr;
	char string[1024];

	va_start(argptr, fmt);
	vsprintf(string, fmt, argptr);
	va_end(argptr);

	ALERT(at_logged, "%s", string);
}

void UTIL_ServerPrint(const char *fmt, ...)
{
	va_list argptr;
	char string[1024];

	va_start(argptr, fmt);
	vsprintf(string, fmt, argptr);
	va_end(argptr);

	SERVER_PRINT(string);
}
