#include "pch.h"

// THANKS: All these from iq's 64k framework
double zlog2d(const double x)
{
    double res;

    _asm fld    qword ptr [x]
    _asm fld1
    _asm fxch   st(1)
    _asm fyl2x
    _asm fstp   qword ptr [res]

    return res;
}

double zlogd(const double x)
{
	return zlog2d(x)/zlog2d(kM_E); // log2(x)/log2(e) - NOTE: opcodes exists for pushing log2(e) and log2(10)   :)
}

double zlog10d(const double x)
{
	return zlog2d(x)/zlog2d(10.); // log2(x)/log2(10)
}

double zexpd(const double x)
{
    double res;

    _asm fld     qword ptr [x]
    _asm fldl2e
    _asm fmulp   st(1), st(0)
    _asm fld1
    _asm fld     st(1)
    _asm fprem
    _asm f2xm1
    _asm faddp   st(1), st(0)
    _asm fscale
    _asm fxch    st(1)
    _asm fstp    st(0)
    _asm fstp    qword ptr [res]

    return res;
}

double zfmodd(const double x, const double y)
{
    double res;

    _asm fld     qword ptr [y]
    _asm fld     qword ptr [x]
    _asm fprem
    _asm fxch    st(1)
    _asm fstp    st(0)
    _asm fstp    qword ptr [res]

    return res;
}

double zpowd(const double x, const double y)
{
    double res;

    _asm fld     qword ptr [y]
    _asm fld     qword ptr [x]
    _asm fyl2x
    _asm fld1
    _asm fld     st(1)
    _asm fprem
    _asm f2xm1
    _asm faddp   st(1), st(0)
    _asm fscale
    _asm fxch
    _asm fstp    st(0)
    _asm fstp    qword ptr [res];

    return res;
}






// THANKS: All these from iq's 64k framework
float zlog2f(const float x)
{
    float res;

    _asm fld    dword ptr [x]
    _asm fld1
    _asm fxch   st(1)
    _asm fyl2x
    _asm fstp   dword ptr [res]

    return res;
}

float zlogf(const float x)
{
	return zlog2f(x)/zlog2f(kFE); // log2(x)/log2(e)
}

float zlog10f(const float x)
{
	return zlog2f(x)/zlog2f(10.f); // log2(x)/log2(10)
}

float zexpf(const float x)
{
    float res;

    _asm fld     dword ptr [x]
    _asm fldl2e
    _asm fmulp   st(1), st(0)
    _asm fld1
    _asm fld     st(1)
    _asm fprem
    _asm f2xm1
    _asm faddp   st(1), st(0)
    _asm fscale
    _asm fxch    st(1)
    _asm fstp    st(0)
    _asm fstp    dword ptr [res]

    return res;
}

float zfmodf(const float x, const float y)
{
    float res;

    _asm fld     dword ptr [y]
    _asm fld     dword ptr [x]
    _asm fprem
    _asm fxch    st(1)
    _asm fstp    st(0)
    _asm fstp    dword ptr [res]

    return res;
}

float zpowf(const float x, const float y)
{
    float res;

    _asm fld     dword ptr [y]
    _asm fld     dword ptr [x]
    _asm fyl2x
    _asm fld1
    _asm fld     st(1)
    _asm fprem
    _asm f2xm1
    _asm faddp   st(1), st(0)
    _asm fscale
    _asm fxch
    _asm fstp    st(0)
    _asm fstp    dword ptr [res];

    return res;
}
