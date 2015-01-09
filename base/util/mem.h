#pragma once

#include "inline.h"

ZFORCEINLINE void zzeromem(void* dest, uint32_t length)
{
	char* c = (char*)dest;

	for (uint32_t i=0; i<length; i++)
		*c++ = '\0';
}

ZFORCEINLINE void zmemcpy(void* dest, const void* src, uint32_t amount)
{
	_asm mov edi, dest
	_asm mov esi, src
	_asm mov ecx, amount
	_asm rep movsb
}

ZFORCEINLINE void* zmemdup(void* src, size_t numBytes)
{
	void* data = (void*)(new char[numBytes]);
	zmemcpy(data, src, numBytes);
	return data;
}