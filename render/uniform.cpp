#include "pch.h"
#include "uniform.h"

void ZUniform::SetMat2(ZUniLoc l, const ZMatrix& v)
{
	if (l<0)
		return;

	static float m[4];

	for (uint32_t i=0; i<2; i++)
		for (uint32_t j=0; j<2; j++)
			m[i*2+j] = v.m[i][j];

	glUniformMatrix2fv(l, 1, false, m);
}

void ZUniform::SetMat3(ZUniLoc l, const ZMatrix& v)
{
	if (l<0)
		return;

	static float m[9];

	for (uint32_t i=0; i<3; i++)
		for (uint32_t j=0; j<3; j++)
			m[i*3+j] = v.m[i][j];

	glUniformMatrix3fv(l, 1, false, m);
}

ZUniLoc ZUniform::GetLoc(const ZProgram& p, const char* name)
{
	return glGetUniformLocation(p.id, name);
}
