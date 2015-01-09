#include "pch.h"
#include "wav.h"

struct ZWavHeader {
	DWORD ChunkID;
	DWORD ChunkSize;
	DWORD Format;
	DWORD Subchunk1ID;
	DWORD Subchunk1Size;
	PCMWAVEFORMAT bufferFormat;
	DWORD Subchunk2ID;
	DWORD Subchunk2Size;
} wav_header_prototype = {
	'FFIR',
	0,
	'EVAW',
	' tmf',
	16,
	{
		WAVE_FORMAT_PCM,    // format
		REPLAY_CHANNELS,  // channels
		REPLAY_RATE,     // sample rate
		REPLAY_RATE * REPLAY_CHANNELS * REPLAY_SAMPLESIZE,    // bytes per second
		REPLAY_CHANNELS * REPLAY_SAMPLESIZE, // block align
		REPLAY_DEPTH, // sample depth
	},
	'atad', // ID
	0,      // Chunk size
};

ZWavHeader CreateHeader(uint32_t numSamples)
{
	ZWavHeader header = wav_header_prototype;

	uint32_t dataSize = numSamples*REPLAY_SAMPLESIZE*REPLAY_CHANNELS;

	header.ChunkSize = dataSize + sizeof(ZWavHeader) - 8; // subtract 8 for ID and size
	header.Subchunk2Size = dataSize;

	return header;
}

int16_t* SetupWavHeader(uint8_t* data, uint32_t numSamples)
{
	ZWavHeader* header = (ZWavHeader*)(data);

	uint32_t dataSize = numSamples*REPLAY_SAMPLESIZE*REPLAY_CHANNELS;

	*header = wav_header_prototype;
	header->ChunkSize = dataSize + sizeof(ZWavHeader) - 8; // subtract 8 for ID and size
	header->Subchunk2Size = dataSize;

	return (int16_t*)(uintptr_t(data) + sizeof(ZWavHeader));
}

void WriteWav(const char* path, int16_t* data, uint32_t numSamples)
{
	ZWavHeader header = CreateHeader(numSamples);
		
	DWORD wmWritten; 
	HANDLE hFile = CreateFileA(path, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); 
	WriteFile(hFile, &header, (DWORD)sizeof(header), &wmWritten, NULL); 
	WriteFile(hFile, data, (DWORD)header.Subchunk2Size, &wmWritten, NULL); 
	CloseHandle(hFile); 
}

void LoadWav(const char* path, int16_t*& data, uint32_t& numSamples)
{
	// This might not load arbitrary WAVs, but it'll process the onces we output.
	HANDLE hFile = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile==INVALID_HANDLE_VALUE)
	{
		data = NULL;
		numSamples = 0;
		return;
	}

	// Get size and alloc
	LARGE_INTEGER size;
	GetFileSizeEx(hFile, &size);

	data = (int16_t*)zalignedalloc(size.LowPart, 4); // ensure 4 byte align

	// Read file
	DWORD  dwBytesRead = 0;
	ReadFile(hFile, data, size.LowPart, &dwBytesRead, NULL);

	CloseHandle(hFile);

	ZWavHeader* header = (ZWavHeader*)(data);
	numSamples = header->Subchunk2Size / REPLAY_CHANNELS / REPLAY_SAMPLESIZE;
	data = (int16_t*)(uintptr_t(data) + sizeof(ZWavHeader));
}