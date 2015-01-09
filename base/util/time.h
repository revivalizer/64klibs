#pragma once

class ZTime
{
public:
	ZTime();

	void Set(double currentTime);
	double Get(void);
	
private:
	double				ticksPerSecond;
	int64_t				zeroCount;
};

