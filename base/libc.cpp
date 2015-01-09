#include "global.h"

void *__cdecl operator new(unsigned int size)
{
	return (char *) GlobalAlloc (GMEM_ZEROINIT, size+32)+16;
}

void __cdecl operator delete(void *p)
{
	GlobalFree((char *) p-16);
}

void *__cdecl operator new[](unsigned int size)
{
	return (char *) GlobalAlloc (GMEM_ZEROINIT, size+32)+16;
}

void __cdecl operator delete[](void *p)
{
	GlobalFree((char *) p-16);
}
