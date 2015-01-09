#pragma once

void _zerror(const char* const str, ...);
void _zcriticalerror(const char* const str, ...);
void _zfatalerror(const char* const str, ...);

#define ENABLE_ZERROR

#ifdef ENABLE_ZERROR
	#define zerror(...) _zerror(__VA_ARGS__)
	#define zcriticalerror(...) _zcriticalerror(__VA_ARGS__)
	#define zfatalerror(...) _zfatalerror(__VA_ARGS__)
#else
	#define zerror(...)
	#define zcriticalerror(...)
	#define zfatalerror(...)
#endif