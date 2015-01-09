#include "pch.h"

ZTexture::ZTexture(ZTextureDescriptor descriptor)
	: descriptor(descriptor)
{
	glGenTextures(1, &id);

	g_pRenderer->textureUnit[0].BindTexture(this);

	bool isDepthTexture = descriptor.IsDepthTexture();

	if (isDepthTexture)
	{
		glTexParameteri(descriptor.GetGLType(), GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
		glTexParameteri(descriptor.GetGLType(), GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
		glTexParameteri(descriptor.GetGLType(), GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	}

	glTexParameteri(descriptor.GetGLType(), GL_TEXTURE_BASE_LEVEL, descriptor.mipmapBase);
	glTexParameteri(descriptor.GetGLType(), GL_TEXTURE_MAX_LEVEL,  descriptor.mipmapMax);

	// Create texture
	GLenum dataFormat = isDepthTexture? GL_DEPTH_COMPONENT : GL_RGBA; // These three elements are unused, but OpenGL requires valid enumerants
	GLenum dataType = isDepthTexture? GL_UNSIGNED_INT : GL_FLOAT;
	GLvoid* data = NULL;

	if (descriptor.type == kTextureType2D)
	{
		glTexImage2D(descriptor.GetGLType(), 0, descriptor.GetGLInternalFormat(), descriptor.width, descriptor.height, 0, dataFormat, dataType, data);
	}
	else if (descriptor.type == kTextureType3D)
	{
		glTexImage3D(descriptor.GetGLType(), 0, descriptor.GetGLInternalFormat(), descriptor.width, descriptor.height, descriptor.depth, 0, dataFormat, dataType, data);
	}
	else if (descriptor.type == kTextureTypeCubemap)
	{
		for (int i=0; i<6; i++)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, descriptor.GetGLInternalFormat(), descriptor.width, descriptor.height, 0, dataFormat, dataType, data);
		}
	}

	g_pRenderer->textureUnit[0].UnbindTexture();
}

ZTexture::~ZTexture(void)
{
	glDeleteTextures(1, &id);
}

void ZTexture::UploadData2D(float* data)
{
	g_pRenderer->textureUnit[0].BindTexture(this);
	glTexImage2D(descriptor.GetGLType(), 0, descriptor.GetGLInternalFormat(), descriptor.width, descriptor.height, 0, GL_RGBA, GL_FLOAT, data);
	g_pRenderer->textureUnit[0].UnbindTexture();
}

void ZTexture::GenerateMipmaps(ZRenderer& renderer)
{
	ZTextureSampler sampler;
	renderer.GetTextureUnit(0).BindTexture(this, &sampler);
	glGenerateMipmap(descriptor.GetGLType());
}
