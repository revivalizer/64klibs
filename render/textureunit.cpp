#include "pch.h"
#include "textureunit.h"

ZTextureUnit::ZTextureUnit()
	: id(0xFFFFFFFF)
	, currentTexture(nullptr)
{

}


ZTextureUnit::~ZTextureUnit(void)
{
}

void ZTextureUnit::Reset()
{
	glActiveTexture(GL_TEXTURE0 + id);

	if (currentTexture)
	{
		glBindTexture(currentTextureType, 0);
		glDisable(currentTextureType);
	}
}

void ZTextureUnit::BindTexture(ZTexture* texture, ZTextureSampler* sampler)
{
	glActiveTexture(GL_TEXTURE0 + id);

	UnbindTexture();

	currentTexture = texture;
	currentTextureType = texture->descriptor.GetGLType();

	// Should depend on texture type
	glEnable(currentTextureType);
	glBindTexture(currentTextureType, texture->id);

	if (sampler)
		glBindSampler(id, sampler->id);
	else
		glBindSampler(id, 0);

}

void ZTextureUnit::UnbindTexture(void)
{
	glActiveTexture(GL_TEXTURE0 + id);

	// Should depend on texture type
	if (currentTexture)
	{
		glBindTexture(currentTextureType, 0);
		glDisable(currentTextureType);
	}

	currentTexture = nullptr;
	currentTextureType = -1;
}