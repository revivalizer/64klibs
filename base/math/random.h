// This should probably switch to xorshifts ... ? http://www.jstatsoft.org/v08/i14/paper
// This class is based on TinyMT: http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/TINYMT/index.html

#pragma once

class ZRandom
{
public:
	ZRandom(uint32_t seed);

	uint32_t NextUniformInt(); // random number in 0 <= r < 2^32
	float NextUniformFloat(); // random number in 0 <= r < 1.0
	float NextFloat(); // random number in -1 <= r < 1.0
	float NextGaussianFloat(); // gaussian random number with mean = 0 and std dev = 1
	double NextUniformDouble(); // random number in 0 <= r < 1.0
	double NextDouble(); // random number in -1 <= r < 1.0
	double NextGaussianDouble(); // gaussian random number with mean = 0 and std dev = 1

private:
	void NextState();

	// TinyMT state
    uint32_t status[4];

	static const uint32_t mat1 = 0x8f7011ee; // These constants from the TinyMT check file
    static const uint32_t mat2 = 0xfc78ff1f;
    static const uint32_t tmat = 0x3793fdff;
};