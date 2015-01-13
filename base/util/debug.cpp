#include "pch.h"

static const int kBufLen = 65536;
char buf[kBufLen];
ZMutex bufMutex;


void _zmsg(const char* const str, ...)
{
	va_list args;
	va_start(args, str);
	vzmsg(str, args);
	va_end(args);
}

void vzmsg(const char* const str, va_list argp)
{
	ZScopedLock l(bufMutex);

	ZASSERT(str!=NULL);

	argp;
	str;
	wvsprintf(buf, str, argp);

	OutputDebugStringA(buf);
	OutputDebugStringA("\n");
}