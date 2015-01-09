#pragma once

enum
{
	kNearest = GL_NEAREST,
	kLinear = GL_LINEAR,
	kNearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
	kNearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR,
	kLinearMipmapNearest = GL_LINEAR_MIPMAP_NEAREST,
	kLinearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR,
};

enum
{
	kRepeat = GL_REPEAT,
	kMirroredRepeat = GL_MIRRORED_REPEAT,
	kClampToEgde = GL_CLAMP_TO_EDGE,
	kClampToBorder = GL_CLAMP_TO_BORDER,
};


class ZTextureSampler : public align16
{
public:
	ZTextureSampler(void);
	~ZTextureSampler(void);

	void SetFiltering(uint32_t maxFilter, uint32_t minFilter);
	void SetClamping(uint32_t sClamp, uint32_t	tClamp);

	GLuint id;
};