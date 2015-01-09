#include "pch.h"

void *__cdecl operator new(size_t size)
{
	return zalignedalloc(size, 16);
}

void __cdecl operator delete(void *p)
{
	zalignedfree(p);
}

void *__cdecl operator new[](size_t size)
{
	return zalignedalloc(size, 16);
}

void __cdecl operator delete[](void *p)
{
	zalignedfree(p);
}