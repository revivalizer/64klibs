#include "pch.h"

#define TINYMT32_MEXP 127
#define TINYMT32_SH0 1
#define TINYMT32_SH1 10
#define TINYMT32_SH8 8
#define TINYMT32_MASK ((uint32_t)0x7fffffff)
#define TINYMT32_MUL (1.0f / 4294967296.0f)

#define MIN_LOOP 8
#define PRE_LOOP 8

ZRandom::ZRandom(uint32_t seed)
{
    status[0] = seed;
    status[1] = mat1;
    status[2] = mat2;
    status[3] = tmat;

    for (int i=1; i<MIN_LOOP; i++)
		status[i & 3] ^= i + ((uint32_t)1812433253) * (status[(i - 1) & 3] ^ (status[(i - 1) & 3] >> 30));

	if ((status[0] & TINYMT32_MASK)==0 && status[1]==0 && status[2]==0 && status[3]==0)
	{
		status[0] = 'T';
		status[1] = 'I';
		status[2] = 'N';
		status[3] = 'Y';
	}

    for (int i=0; i<PRE_LOOP; i++)
		NextState();
}

uint32_t ZRandom::NextUniformInt()
{
	NextState();

    uint32_t t0, t1;
    t0 = status[3];
    t1 = status[0] + (status[2] >> TINYMT32_SH8);
    t0 ^= t1;
    t0 ^= -((int32_t)(t1 & 1)) & tmat;
    return t0;
}

float ZRandom::NextUniformFloat()
{
	NextState();
	return (float)NextUniformInt()*TINYMT32_MUL;
}

float ZRandom::NextFloat()
{
	NextState();
	return (float)NextUniformInt()*TINYMT32_MUL*2.0f-1.0f;
}

float ZRandom::NextGaussianFloat()
{
	return zsqrtf(-2.0f * zlogf(NextUniformFloat())) * zcosf(NextUniformFloat() * 2.0f * kFPI);
}

double ZRandom::NextUniformDouble()
{
	NextState();
	return (double)NextUniformInt()*TINYMT32_MUL;
}

double ZRandom::NextDouble()
{
	NextState();
	return (double)NextUniformInt()*TINYMT32_MUL*2.0f-1.0f;
}

double ZRandom::NextGaussianDouble()
{
	return zsqrtd(-2.0 * zlogd(NextUniformDouble())) * zcosd(NextUniformDouble() * 2.0 * kM_PI);
}


void ZRandom::NextState()
{
    uint32_t x;
    uint32_t y;

    y = status[3];
    x = (status[0] & TINYMT32_MASK) ^ status[1] ^ status[2];
    x ^= (x << TINYMT32_SH0);
    y ^= (y >> TINYMT32_SH0) ^ x;
    status[0] = status[1];
    status[1] = status[2];
    status[2] = x ^ (y << TINYMT32_SH1);
    status[3] = y;
    status[1] ^= -((int32_t)(y & 1)) & mat1;
    status[2] ^= -((int32_t)(y & 1)) & mat2;
}
