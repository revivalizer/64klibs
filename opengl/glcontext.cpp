#include "pch.h"

const PIXELFORMATDESCRIPTOR pfd =
{
    sizeof(PIXELFORMATDESCRIPTOR),
    1,
    PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,
    PFD_TYPE_RGBA,
    32,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    32,             // zbuffer
    0,              // stencil!
    0,
    PFD_MAIN_PLANE,
    0, 0, 0, 0
};

HGLRC InitGLContext(HDC dc)
{
	int32_t pxFormat;
	HGLRC rc = 0;

    if ( (pxFormat = ChoosePixelFormat(dc, &pfd)) == NULL )
		return 0;

    if ( !SetPixelFormat(dc, pxFormat, &pfd) )
		return 0;

    if ( (rc = wglCreateContext(dc)) == NULL )
		return 0;

    if ( !wglMakeCurrent(dc, rc) )
		return 0;

	return rc;
}