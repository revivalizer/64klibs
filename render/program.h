#pragma once

class ZRenderer;

class ZProgram : public align16
{
public:
	ZProgram(void);
	virtual ~ZProgram(void);

	void Link(const ZShader& vs, const ZShader& gs, const ZShader& fs);
	void Link(const ZShader& vs, const ZShader& fs);
	void Unload();

	void UpdateCommonLocations();
	void SetCommonLocations(ZRenderer& renderer);

	bool        DidLink();
	const char* GetLinkErrors();

	GLuint id;

	// Caching of common locations
	ZUniLoc locMM;
	ZUniLoc locVM;
	ZUniLoc locPM;
	ZUniLoc locMVM;
	ZUniLoc locMVPM;
	ZUniLoc locNMVM;
	ZUniLoc locNMM;

	ZUniLoc locPxSize;
	ZUniLoc locViewportSize;
};
