#pragma once

void *__cdecl operator new(size_t size);
void __cdecl operator delete(void *p);
void *__cdecl operator new[](size_t size);
void __cdecl operator delete[](void *p);
