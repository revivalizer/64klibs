#include "pch.h"
#include "renderer.h"

ZRenderer* g_pRenderer = nullptr;

ZRenderer::ZRenderer(void)
	: numTextureUnits(8)
	, currentFBO(nullptr)
	, nullFBO(ZFBODescriptor(0, 0), 0)
{
	for (uint32_t i=0; i<numTextureUnits; i++)
		textureUnit[i].id = i;

	g_pRenderer = this;
}


ZRenderer::~ZRenderer(void)
{
}

void ZRenderer::Reset(void)
{
	/*
	currentMaterial = NULL;
	currentProgramID = 0;
	currentProgram = NULL;
	*/
	currentBlendMode = kBlendOverlay;
	currentZBufferMode = kZBufferOff;
	currentCullingMode = kCullingShowFront;

	glUseProgram(0);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBlendEquation(GL_FUNC_ADD);

	//glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDisable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // allow us to use glColor for stuff other than just being 1 :)

	// Other state assumptions
	glFrontFace(GL_CCW); // Front face is defined counter clock wise
	glDisable(GL_LIGHTING);

	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	/*
	// Reset render targets
	renderTargetStackPos = 0;
	renderTargetStack[0] = NULL;
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	*/

	for (uint32_t i=0; i<numTextureUnits; i++)
	{
		textureUnit[i].Reset();
	}

	/*
	// Reset matrix state
	for (int mode=0; mode<kNumMatrixModes; mode++)
	{
		SetMatrixMode(mode);
		matrixStackPos[mode] = 0;
		LoadIdentityMatrix();
	} // leave in model matrix mode

	overrideMaterial = false;
	*/

	pm.Reset();
	vm.Reset();
	mm.Reset();

	SetBlendMode(kBlendOverlay);
	SetZBufferMode(kZBufferOn);
}

void ZRenderer::UseProgram(const ZProgram& program)
{
	glUseProgram(program.id);
}

void ZRenderer::BindFBO(ZFBO* fbo)
{
	currentFBO = fbo;
	glBindFramebuffer(GL_FRAMEBUFFER_EXT, fbo->id);

	glViewport(0, 0, fbo->descriptor.width, fbo->descriptor.height);
	glScissor(0, 0, fbo->descriptor.width, fbo->descriptor.height);
}

void ZRenderer::UnbindFBO()
{
	BindFBO(&nullFBO);
}

void ZRenderer::BindDrawBuffers(uint32_t buffers)
{
	const GLuint kColorBuffers[] = {
		GL_COLOR_ATTACHMENT0_EXT, 
		GL_COLOR_ATTACHMENT1_EXT, 
		GL_COLOR_ATTACHMENT2_EXT, 
		GL_COLOR_ATTACHMENT3_EXT,
	};

	// Buffers is not a count here, it's an enum. But because of the way this is set up, we can use the enum+1 as the buffer count
	glDrawBuffers(buffers+1, kColorBuffers);
}

void ZRenderer::Clear(uint32_t buffer)
{
	glClear(GLbitfield(buffer));
}

static const int blendSourceFactor[] = {GL_SRC_ALPHA,           0, GL_ONE, GL_ONE };
static const int blendDestFactor[]   = {GL_ONE_MINUS_SRC_ALPHA, 0, GL_ONE, GL_ONE };

void ZRenderer::SetBlendMode(uint32_t blendMode)
{
	if (blendMode!=currentBlendMode)
	{
		if (blendMode==kBlendOff && currentBlendMode!=kBlendOff)
			glDisable(GL_BLEND);	
		else if (blendMode!=kBlendOff && currentBlendMode==kBlendOff)
			glEnable(GL_BLEND);	

		if (blendMode!=kBlendOff)
		{
			glBlendFunc(blendSourceFactor[blendMode], blendDestFactor[blendMode]);

			if (blendMode!=kBlendSubtract)
				glBlendEquation(GL_FUNC_ADD);
			else
				glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);

		}

		currentBlendMode = blendMode;	
	}
}

void ZRenderer::SetZBufferMode(uint32_t zBufferMode)
{
	if (zBufferMode != currentZBufferMode)
	{
		if (zBufferMode==kZBufferOn)
		{
			glEnable(GL_DEPTH_TEST);
			glDepthMask(GL_TRUE);
		}
		else if (zBufferMode==kZBufferOff)
		{
			glDisable(GL_DEPTH_TEST);
		}
		else if (zBufferMode==kZBufferReadOnly)
		{
			glEnable(GL_DEPTH_TEST);
			glDepthMask(GL_FALSE);
		}

		currentZBufferMode = zBufferMode;	
	}
}

void ZRenderer::SetCullingMode(uint32_t cullingMode)
{	
	if (cullingMode != currentCullingMode)
	{
		// This could be optimized to do GL calls separately (if needed)
		if (cullingMode==kCullingShowFront)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
		}
		else if (cullingMode==kCullingShowBack)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);
		}
		else if (cullingMode==kCullingShowFrontAndBack)
		{
			glDisable(GL_CULL_FACE);
		}

		currentCullingMode = cullingMode;	
	}
}
