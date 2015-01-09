#include "pch.h"

ZTime::ZTime(void)
{
	LARGE_INTEGER iTimerCountsPerSecond;
	QueryPerformanceFrequency( &iTimerCountsPerSecond );
	ticksPerSecond = (double) iTimerCountsPerSecond.QuadPart;

	zeroCount = 0;

	Set(0.);
}

void ZTime::Set(double currentTime)
{
	int64_t diff = zltruncd(currentTime*ticksPerSecond);

	LARGE_INTEGER currentCount;
	QueryPerformanceCounter(&currentCount);

	zeroCount = currentCount.QuadPart - diff;
}

double ZTime::Get(void)
{
	LARGE_INTEGER currentCount;
	QueryPerformanceCounter(&currentCount);

	int64_t diff = currentCount.QuadPart - zeroCount;
	return ((double)diff / ticksPerSecond);
}