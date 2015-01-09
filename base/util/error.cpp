#include "pch.h"

void _zerror(const char* const str, ...)
{
	va_list args;
	va_start(args, str);
	vzmsg(str, args);
	va_end(args);
}

void _zcriticalerror(const char* const str, ...)
{
	char buf[2048];

	va_list args;
	va_start(args, str);
	vsnprintf(buf, 2048-1, str, args);
	va_end(args);

	MessageBoxA(NULL, buf, NULL, NULL);
}

void _zfatalerror(const char* const str, ...)
{
	char buf[2048];

	va_list args;
	va_start(args, str);
	vsnprintf(buf, 2048-1, str, args);
	va_end(args);

	MessageBoxA(NULL, buf, NULL, NULL);

	ExitProcess(0xFFFFFFFF);
}