#pragma once

enum
{
	kGLDrawBufferColor0 = 0,
	kGLDrawBufferColor01,
	kGLDrawBufferColor012,
	kGLDrawBufferColor0123,
};

enum
{
	kBlendOverlay = 0,
	kBlendOff,
	kBlendAdd,
	kBlendSubtract,
};

enum
{
	kZBufferOn = 0,
	kZBufferOff,
	kZBufferReadOnly,
};

enum
{
	kCullingShowFront = 0,
	kCullingShowBack,
	kCullingShowFrontAndBack,
};

enum {
	kClearColorBuffer = GL_COLOR_BUFFER_BIT, 
	kClearDepthBuffer = GL_DEPTH_BUFFER_BIT
};

class ZRenderer : public align16
{ 
public:
	enum {kMaxTextureUnits = 8};

	ZRenderer(void);
	~ZRenderer(void);

	void Reset(void);

	void UseProgram(const ZProgram& program);

	void Clear(uint32_t buffer);

	void SetBlendMode(uint32_t blendMode);
	void SetZBufferMode(uint32_t zBufferMode);
	void SetCullingMode(uint32_t cullingMode);

	ZTextureUnit textureUnit[kMaxTextureUnits];
	ZTextureUnit& GetTextureUnit(uint32_t i) { return textureUnit[i]; }

	uint32_t numTextureUnits;

	void BindFBO(ZFBO* fbo);
	void UnbindFBO();

	void BindDrawBuffers(uint32_t buffers);

	ZFBO* currentFBO;
	ZFBO  nullFBO;

	ZMatrixStack pm;
	ZMatrixStack vm;
	ZMatrixStack mm;

	uint32_t currentBlendMode;
	uint32_t currentZBufferMode;
	uint32_t currentCullingMode;

	uint32_t GetGLError() { return uint32_t(glGetError()); }
};

extern ZRenderer* g_pRenderer;

