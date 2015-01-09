#include "pch.h"
#include "texturesampler.h"


ZTextureSampler::ZTextureSampler(void)
	: id(0)
{
	glGenSamplers(1, &id);

	SetFiltering(kLinear, kLinear);
	SetClamping(kClampToEgde, kClampToEgde);
}


ZTextureSampler::~ZTextureSampler(void)
{
	glDeleteSamplers(1, &id);
}

void ZTextureSampler::SetFiltering(uint32_t magFilter, uint32_t minFilter)
{
	glSamplerParameteri(id, GL_TEXTURE_MAG_FILTER, magFilter); 
	glSamplerParameteri(id, GL_TEXTURE_MIN_FILTER, minFilter); 
}

void ZTextureSampler::SetClamping(uint32_t sClamp, uint32_t tClamp)
{
	glSamplerParameteri(id, GL_TEXTURE_WRAP_S, sClamp);  	
	glSamplerParameteri(id, GL_TEXTURE_WRAP_T, tClamp);  	
}
