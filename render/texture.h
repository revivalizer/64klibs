#pragma once

enum
{
	kTextureType2D = 0,
	kTextureType3D,
	kTextureTypeCubemap,
};

enum
{
	kTextureFormatDepth16 = 0,
	kTextureFormatDepth24,
	kTextureFormatDepth32,
	kTextureFormatRGBA,
	kTextureFormatRGBA32,
	kTextureFormatRGBA16,
};


struct ZTextureDescriptor
{
	ZTextureDescriptor(uint32_t width, uint32_t height, uint32_t depth, uint32_t format, uint32_t type, uint32_t mipmapBase, uint32_t mipmapMax) : width(width), height(height), depth(depth), format(format), type(type), mipmapBase(mipmapBase), mipmapMax(mipmapMax)
	{
		UpdateHash();
	}

	uint32_t width;
	uint32_t height;
	uint32_t depth;
	uint32_t format;
	uint32_t type;
	uint32_t mipmapBase;
	uint32_t mipmapMax;

	uint32_t hash;

	static ZTextureDescriptor Texture2D(uint32_t width, uint32_t height, uint32_t format)
	{
		return ZTextureDescriptor(width, height, 0, format, kTextureType2D, 0, 0);
	}

	static ZTextureDescriptor TextureCubemap(uint32_t width, uint32_t height, uint32_t format)
	{
		return ZTextureDescriptor(width, height, 0, format, kTextureTypeCubemap, 0, 0);
	}

	ZTextureDescriptor WithMipmapLevels(uint32_t mipmapLevels)
	{
		ZTextureDescriptor clone = *this;
		clone.mipmapMax = mipmapLevels;
		clone.UpdateHash();

		return clone;
	}

	void UpdateHash()
	{
		// From http://www.cse.yorku.ca/~oz/hash.html
		uint32_t hash = 0x569921df;
		hash = 65599 * hash + (width << 10) + width;
		hash = 65599 * hash + (height << 8) + height;
		hash = 65599 * hash + (depth << 13) + depth;
		hash = 65599 * hash + ((format+59) << 20) + (format + 59);
		hash = 65599 * hash + ((type+23) << 7) + (type + 23);
		hash = 65599 * hash + (mipmapBase << 9) + mipmapBase;
		hash = 65599 * hash + (mipmapMax << 11) + mipmapMax;
	}

	bool IsDepthTexture()
	{
		return format==kTextureFormatDepth16 ||
			   format==kTextureFormatDepth24 ||
			   format==kTextureFormatDepth32;
	}

	GLenum GetGLType()
	{
		const GLenum TextureTypes[] =
		{
			GL_TEXTURE_2D,
			GL_TEXTURE_3D,
			GL_TEXTURE_CUBE_MAP,
		};

		return TextureTypes[type];
	}

	GLenum GetGLInternalFormat()
	{
		const GLenum InternalFormat[] =
		{
			GL_DEPTH_COMPONENT16,
			GL_DEPTH_COMPONENT24,
			GL_DEPTH_COMPONENT32,
			GL_RGBA8,
			GL_RGBA32F_ARB,
			GL_RGBA16F_ARB,
		};

		return InternalFormat[format];
	}
};

class ZTexture : public align16
{
public:
	ZTexture(ZTextureDescriptor descriptor);
	~ZTexture(void);

	GLuint id;

	ZTextureDescriptor descriptor;

	void UploadData2D(float* data);

	void GenerateMipmaps(ZRenderer& renderer);
};