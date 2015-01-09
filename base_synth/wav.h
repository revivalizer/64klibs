#pragma once

#define	REPLAY_RATE				44100
#define	REPLAY_DEPTH			16
#define	REPLAY_CHANNELS			2
#define	REPLAY_SAMPLESIZE		(REPLAY_DEPTH/8)

void WriteWav(const char* path, int16_t* data, uint32_t numSamples);
void LoadWav(const char* path, int16_t*& data, uint32_t& numSamples);
