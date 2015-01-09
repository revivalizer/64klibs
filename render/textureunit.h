#pragma once

class ZTextureUnit : public align16
{
public:
	ZTextureUnit();
	~ZTextureUnit(void);

	void BindTexture(ZTexture* texture, ZTextureSampler* sampler = NULL);
	void UnbindTexture(void);

	void Reset();

private:
	uint32_t id;
	ZTexture* currentTexture;
	GLint currentTextureType;

	friend class ZRenderer;
};

