#include "pch.h"
#include "program.h"


ZProgram::ZProgram(void)
	: id(0)
	, locMM(-1)
	, locVM(-1)
	, locPM(-1)
	, locMVM(-1)
	, locMVPM(-1)
	, locNMM(-1)
	, locNMVM(-1)
	, locPxSize(-1)
	, locViewportSize(-1)
{
}


ZProgram::~ZProgram(void)
{
}

void ZProgram::Link(const ZShader& vs, const ZShader& gs, const ZShader& fs)
{
	if (id==0)
		id = glCreateProgram();

	glAttachShader(id, vs.id);
	glAttachShader(id, gs.id);
	glAttachShader(id, fs.id);

	glLinkProgram(id);

	glDetachShader(id, vs.id); // It's a good idea to do this, to ensure that glDeleteShader actually deletes
	glDetachShader(id, gs.id);
	glDetachShader(id, fs.id);

	if (DidLink())
		UpdateCommonLocations();
}

void ZProgram::Link(const ZShader& vs, const ZShader& fs)
{
	if (id==0)
		id = glCreateProgram();

	glAttachShader(id, vs.id);
	glAttachShader(id, fs.id);

	glLinkProgram(id);

	glDetachShader(id, vs.id); // It's a good idea to do this, to ensure that glDeleteShader actually deletes
	glDetachShader(id, fs.id);

	if (DidLink())
		UpdateCommonLocations();
}

void ZProgram::Unload()
{
	if (id > 0)
	{
		glDeleteProgram(id);
		id = 0;
	}
}

bool ZProgram::DidLink()
{
	GLint res;
	glGetProgramiv(id, GL_LINK_STATUS, &res);
	return res==GL_TRUE;
}

const char* ZProgram::GetLinkErrors()
{
	GLint size;
	glGetProgramiv(id, GL_INFO_LOG_LENGTH, &size);
	char* str = new char[size+1];
	glGetProgramInfoLog(id, size+1, nullptr, str);
	str[size] = '\0'; // This handles case with 0 log length (needs size+1)
	return str;
}

void ZProgram::UpdateCommonLocations()
{
	locMM = ZUniform::GetLoc(*this, "mm");
	locVM = ZUniform::GetLoc(*this, "vm");
	locPM = ZUniform::GetLoc(*this, "pm");
	locMVM = ZUniform::GetLoc(*this, "mvm");
	locMVPM = ZUniform::GetLoc(*this, "mvpm");
	locNMM = ZUniform::GetLoc(*this, "nmm");
	locNMVM = ZUniform::GetLoc(*this, "nmvm");

	locPxSize = ZUniform::GetLoc(*this, "pxSize");
	locViewportSize = ZUniform::GetLoc(*this, "viewportSize");

}

void ZProgram::SetCommonLocations(ZRenderer& renderer)
{
	// This can be optimized since we don't always need it
	ZMatrix mvm = renderer.vm() * renderer.mm();

	if (locMM >= 0)
		ZUniform::SetMat4(locMM, renderer.mm());

	if (locVM >= 0)
		ZUniform::SetMat4(locVM, renderer.vm());

	if (locPM >= 0)
		ZUniform::SetMat4(locPM, renderer.pm());

	if (locMVM >= 0)
		ZUniform::SetMat4(locMVM, mvm);

	if (locMVPM >= 0)
		ZUniform::SetMat4(locMVPM, renderer.pm() * mvm);

	if (locNMM >= 0)
		ZUniform::SetMat3(locNMM, MakeNormalMatrix(renderer.mm()));

	if (locNMVM >= 0)
		ZUniform::SetMat3(locNMVM, MakeNormalMatrix(mvm));

	if (locPxSize >= 0)
		ZUniform::SetVec2(locPxSize, ZVector(1.f/float(renderer.currentFBO->descriptor.width), 1.f/float(renderer.currentFBO->descriptor.height)));

	if (locViewportSize >= 0)
		ZUniform::SetVec2(locViewportSize, ZVector(float(renderer.currentFBO->descriptor.width), float(renderer.currentFBO->descriptor.height)));
}
