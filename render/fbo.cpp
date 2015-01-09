#include "pch.h"


ZFBO::ZFBO(ZFBODescriptor descriptor)
	: descriptor(descriptor)
{
	glGenFramebuffers(1, &id);
}

ZFBO::ZFBO( ZFBODescriptor descriptor, GLuint id )
	: descriptor(descriptor)
	, id(id)
{

}


ZFBO::~ZFBO(void)
{
	if (id)
		glDeleteFramebuffers(1, &id);
}

GLuint AttachmentTypes[] = {
	GL_COLOR_ATTACHMENT0_EXT,
	GL_COLOR_ATTACHMENT1_EXT,
	GL_COLOR_ATTACHMENT2_EXT,
	GL_COLOR_ATTACHMENT3_EXT,
	GL_DEPTH_ATTACHMENT_EXT,
};

void ZFBO::AttachTexture2D(uint32_t attachment, ZTexture* texture, uint32_t mipmapLevel)
{
	glFramebufferTexture2D(GL_FRAMEBUFFER_EXT, AttachmentTypes[attachment], GL_TEXTURE_2D, texture->id, mipmapLevel);
}

void ZFBO::DetachTexture2D(uint32_t attachment, uint32_t mipmapLevel)
{
	glFramebufferTexture2D(GL_FRAMEBUFFER_EXT, AttachmentTypes[attachment], GL_TEXTURE_2D, 0, mipmapLevel);
}

void ZFBO::AttachTexture3D(uint32_t attachment, ZTexture* texture, uint32_t mipmapLevel, uint32_t layer)
{
	glFramebufferTexture3D(GL_FRAMEBUFFER_EXT, AttachmentTypes[attachment], GL_TEXTURE_3D, texture->id, mipmapLevel, layer);
}

void ZFBO::DetachTexture3D(uint32_t attachment, uint32_t mipmapLevel, uint32_t layer)
{
	glFramebufferTexture3D(GL_FRAMEBUFFER_EXT, AttachmentTypes[attachment], GL_TEXTURE_3D, 0, mipmapLevel, layer);
}

void ZFBO::AttachTextureCubemap(uint32_t attachment, ZTexture* texture, uint32_t mipmapLevel, uint32_t face)
{
	glFramebufferTexture2D(GL_FRAMEBUFFER_EXT, AttachmentTypes[attachment], GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, texture->id, mipmapLevel);
}

void ZFBO::DetachTextureCubemap(uint32_t attachment, uint32_t mipmapLevel, uint32_t face)
{
	glFramebufferTexture2D(GL_FRAMEBUFFER_EXT, AttachmentTypes[attachment], GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, 0, mipmapLevel);
}

ZFBO ZFBO::NullFBO(uint32_t width, uint32_t height)
{
	return ZFBO(ZFBODescriptor(width, height), 0);
}

uint32_t ZFBO::GetStatus()
{
	return (uint32_t)glCheckFramebufferStatus(GL_FRAMEBUFFER_EXT);
}
/*
void ZCubemapHelper::Begin(ZRenderer& renderer, ZFBO* fbo, ZTexture* texture)
{
	this->fbo = fbo;
	this->texture = texture;
}

void ZCubemapHelper::SetupFace(ZRenderer& renderer, uint32_t face)
{

}

void ZCubemapHelper::End(ZRenderer& renderer)
{
	fbo->DetachTextureCubemap(GL_COLOR_ATTACHMENT0_EXT, 0);

	fbo = nullptr;
	texture = nullptr;
}

*/