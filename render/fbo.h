#pragma once

struct ZFBODescriptor
{
	ZFBODescriptor(uint32_t width, uint32_t height) : width(width), height(height)
	{
		UpdateHash();
	}

	uint32_t width;
	uint32_t height;

	hash_t hash;

	void UpdateHash()
	{
		hash = init_hash();
		update_hash(hash, width);
		update_hash(hash, height);
	}
};

class ZFBO : public align16
{
public:
	enum
	{
		kColor0 = 0,
		kColor1,
		kColor2,
		kColor3,
		kDepth,
	};

	ZFBO(ZFBODescriptor descriptor);
	ZFBO(ZFBODescriptor descriptor, GLuint id);
	~ZFBO(void);

	GLuint         id;
	ZFBODescriptor descriptor;

	void AttachTexture2D(     uint32_t attachment, ZTexture* texture, uint32_t mipmapLevel);
	void AttachTexture3D(     uint32_t attachment, ZTexture* texture, uint32_t mipmapLevel, uint32_t layer);
	void AttachTextureCubemap(uint32_t attachment, ZTexture* texture, uint32_t mipmapLevel, uint32_t face);
	
	void DetachTexture2D(     uint32_t attachment, uint32_t mipmapLevel);
	void DetachTexture3D(     uint32_t attachment, uint32_t mipmapLevel, uint32_t layer);
	void DetachTextureCubemap(uint32_t attachment, uint32_t mipmapLevel, uint32_t face);

	uint32_t GetStatus();

	static ZFBO NullFBO(uint32_t width, uint32_t height);

};
/*
class ZCubemapHelper
{
public:
	ZCubemapHelper() {};
	~ZCubemapHelper() {};

	void Begin(ZRenderer& renderer, ZFBO* fbo, ZTexture* texture);
	void SetupFace(ZRenderer& renderer, uint32_t face);
	void End(ZRenderer& renderer);
	
	ZFBO* fbo;
	ZTexture* texture;
	uint32_t lastAttachedFace = 
};
*/