#pragma once

template<uint32_t oversamplingFactor>
class ZBlockBuffer : public align16
{
public:
	static const int numSamples = kBlockSize*oversamplingFactor;

	ZBlockBuffer()
	{
		// Verify that samples are aligned
		ZASSERT(((uintptr_t)(&samples) & 0xF) == 0)
	}

	void Reset()
	{
		zzeromem(samples, numSamples*sizeof(sample_t));
	}

	void Add(const ZBlockBuffer<oversamplingFactor>& other)
	{
		for (int i = 0; i < numSamples; i++)
		{
			samples[i].v = _mm_add_pd(samples[i].v, other.samples[i].v);
		}
	}

	sample_t samples[numSamples];
};

typedef ZBlockBuffer<kOversample1x> ZBlockBuffer1x;
typedef ZBlockBuffer<kOversample2x> ZBlockBuffer2x;
typedef ZBlockBuffer<kOversample4x> ZBlockBuffer4x;
typedef ZBlockBuffer<kOversample8x> ZBlockBuffer8x;
typedef ZBlockBuffer<kDefaultOversampling> ZBlockBufferInternal;


template<uint32_t numSamples> // numSamples MUST be power of 2
class ZCircularBuffer : public align16
{
public:
	sample_t samples[numSamples];

	ZCircularBuffer() : align16()
	, readPos(0)
	, writePos(0)
	{
		// Verify that samples are aligned
		ZASSERT(((uintptr_t)(&samples) & 0xF) == 0)
	}

	ZINLINE sample_t ReadOffsetSample(uint32_t offset)
	{
		sample_t sample = samples[(writePos - offset) & (numSamples-1)];
		return sample;
	}

	ZINLINE sample_t GetSample()
	{
		sample_t sample = samples[(readPos++) & (numSamples-1)];
		return sample;
	}

	ZINLINE void PutSample(const sample_t& sample)
	{
		samples[(writePos++) & (numSamples-1)]	= sample;
	}

	template<uint32_t oversamplingFactor>
	ZINLINE void PutBlock(const ZBlockBuffer<oversamplingFactor>& block)
	{
		for (uint32_t i=0; i<block.numSamples; i++)
		{
			PutSample(block.samples[i]);
		}
	}

	ZINLINE uint32_t SamplesAvailable(void)
	{
		return (writePos-readPos) & (numSamples-1);
	}

	void Reset(int n)
	{
		ZASSERT(n <= numSamples);

		readPos = 0;
		writePos = n;

		zzeromem(samples, n*sizeof(sample_t));
	}

	void Reset()
	{
		Reset(numSamples);
	}

	uint32_t readPos;
	uint32_t writePos;
};