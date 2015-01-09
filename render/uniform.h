#pragma once

class ZProgram;

typedef GLint ZUniLoc;

class ZUniform : public align16
{
public:
	static ZUniLoc GetLoc  (const ZProgram& p, const char* name);

	static void    SetInt         (ZUniLoc l, int32_t v)                        { if (l<0) return; glUniform1i(l, v); }
	static void    SetInt         (ZUniLoc l, uint32_t v)                       { if (l<0) return; glUniform1i(l, v); }
	static void    SetFloat       (ZUniLoc l, float v)                          { if (l<0) return; glUniform1f(l, v); }
	static void    SetFloat       (ZUniLoc l, double v)                         { if (l<0) return; glUniform1f(l, GLfloat(v)); }
	static void    SetFloatArray  (ZUniLoc l, uint32_t numFloats, float* v)     { if (l<0) return; glUniform1fv(l, numFloats, v); }
	static void    SetVec2        (ZUniLoc l, const ZVector& v)                 { if (l<0) return; glUniform2fv(l, 1, v.v.f); }
	static void    SetVec3        (ZUniLoc l, const ZVector& v)                 { if (l<0) return; glUniform3fv(l, 1, v.v.f); }
	static void    SetVec4        (ZUniLoc l, const ZVector& v)                 { if (l<0) return; glUniform4fv(l, 1, v.v.f); }
	static void    SetMat2        (ZUniLoc l, const ZMatrix& v);
	static void    SetMat3        (ZUniLoc l, const ZMatrix& v);
	static void    SetMat4        (ZUniLoc l, const ZMatrix& v)                 { if (l<0) return; glUniformMatrix4fv(l, 1, false, v.m[0].v.f); }
};

