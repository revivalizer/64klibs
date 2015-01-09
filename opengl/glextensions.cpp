#include "pch.h"

#if 0
// Based Off Of Code Supplied At OpenGL.org
bool IsExtensionSupported( char* szTargetExtension )
{
	const unsigned char *pszExtensions = NULL;
	const unsigned char *pszStart;
	unsigned char *pszWhere, *pszTerminator;

	// Extension names should not have spaces
	pszWhere = (unsigned char *) strchr( szTargetExtension, ' ' );
	if( pszWhere || *szTargetExtension == '\0' )
		return false;

	// Get Extensions String
	pszExtensions = glGetString( GL_EXTENSIONS );

	// Search The Extensions String For An Exact Copy
	pszStart = pszExtensions;
	for(;;)
	{
		pszWhere = (unsigned char *) strstr( (const char *) pszStart, szTargetExtension );
		if( !pszWhere )
			break;
		pszTerminator = pszWhere + strlen( szTargetExtension );
		if( pszWhere == pszStart || *( pszWhere - 1 ) == ' ' )
			if( *pszTerminator == ' ' || *pszTerminator == '\0' )
				return true;
		pszStart = pszTerminator;
	}
	return false;
}
#endif

static bool isInited = false;

#pragma warning(disable: 4191) // unsafe conversions below
void InitOpenGLExtensions()
{
	if (isInited)
		return;

/*	if (IsExtensionSupported("GL_ARB_framebuffer_object"))
		umsg("SUPPORTED");
	else
		umsg("NOT SUPPORTED");*/

	// Program
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
	glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
	glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
	glDetachShader = (PFNGLDETACHSHADERPROC)wglGetProcAddress("glDetachShader");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
	glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
	glUniform2i = (PFNGLUNIFORM2IPROC)wglGetProcAddress("glUniform2i");
	glUniform3i = (PFNGLUNIFORM3IPROC)wglGetProcAddress("glUniform3i");
	glUniform4i = (PFNGLUNIFORM4IPROC)wglGetProcAddress("glUniform4i");
	glUniform1iv = (PFNGLUNIFORM1IVPROC)wglGetProcAddress("glUniform1iv");
	glUniform2iv = (PFNGLUNIFORM2IVPROC)wglGetProcAddress("glUniform2iv");
	glUniform3iv = (PFNGLUNIFORM3IVPROC)wglGetProcAddress("glUniform3iv");
	glUniform4iv = (PFNGLUNIFORM4IVPROC)wglGetProcAddress("glUniform4iv");
	glUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
	glUniform2f = (PFNGLUNIFORM2FPROC)wglGetProcAddress("glUniform2f");
	glUniform3f = (PFNGLUNIFORM3FPROC)wglGetProcAddress("glUniform3f");
	glUniform4f = (PFNGLUNIFORM4FPROC)wglGetProcAddress("glUniform4f");
	glUniform1fv = (PFNGLUNIFORM1FVPROC)wglGetProcAddress("glUniform1fv");
	glUniform2fv = (PFNGLUNIFORM2FVPROC)wglGetProcAddress("glUniform2fv");
	glUniform3fv = (PFNGLUNIFORM3FVPROC)wglGetProcAddress("glUniform3fv");
	glUniform4fv = (PFNGLUNIFORM4FVPROC)wglGetProcAddress("glUniform4fv");
	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
	glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)wglGetProcAddress("glUniformMatrix3fv");
	glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)wglGetProcAddress("glUniformMatrix2fv");
	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)wglGetProcAddress("glGetAttribLocation");
	glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)wglGetProcAddress("glVertexAttrib1f");
	glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)wglGetProcAddress("glVertexAttrib1fv");
	glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)wglGetProcAddress("glVertexAttrib2fv");
	glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)wglGetProcAddress("glVertexAttrib3fv");
	glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)wglGetProcAddress("glVertexAttrib4fv");
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
	glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)wglGetProcAddress("glBindAttribLocation");
	glMultiTexCoord2f = (PFNGLMULTITEXCOORD2FPROC)wglGetProcAddress("glMultiTexCoord2f");
	glMultiTexCoord2d = (PFNGLMULTITEXCOORD2DPROC)wglGetProcAddress("glMultiTexCoord2d");

	// Buffer
	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");

	// Shader
	glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
	glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
	glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
	glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
	glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC)wglGetProcAddress("glGetActiveUniform");

	// VBO
	glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
	glBufferSubData = (PFNGLBUFFERSUBDATAPROC)wglGetProcAddress("glBufferSubData");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");

	// FBO
	glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)wglGetProcAddress("glGenFramebuffers"); 
	glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)wglGetProcAddress("glDeleteFramebuffers"); 
	glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)wglGetProcAddress("glBindFramebuffer"); 
	glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)wglGetProcAddress("glCheckFramebufferStatus"); 
	glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)wglGetProcAddress("glFramebufferTexture2D"); 
	glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC)wglGetProcAddress("glFramebufferTexture3D"); 
	glDrawBuffers = (PFNGLDRAWBUFFERSPROC)wglGetProcAddress("glDrawBuffers"); 
	glActiveTexture = (PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture"); 
	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog"); 

	// MISC
	glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
	glClampColorARB = (PFNGLCLAMPCOLORARBPROC)wglGetProcAddress("glClampColorARB");
	glWindowPos2i = (PFNGLWINDOWPOS2IPROC)wglGetProcAddress("glWindowPos2i");
	glBlendEquation = (PFNGLBLENDEQUATIONPROC)wglGetProcAddress("glBlendEquation");
	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");

	// MORE
	#define ADD_EXTENSION(type, name) name = (type)wglGetProcAddress(#name);
	#include "extensionlist.h"
	#undef ADD_EXTENSION

//	glGenSamplers = (PFNGLGENSAMPLERSPROC)wglGetProcAddress("glGenSamplers");

	// TEXTURE
	extern PFNGLTEXIMAGE3DPROC glTexImage3D;
	extern PFNGLFRAMEBUFFERTEXTURELAYERPROC glFramebufferTextureLayer;

	isInited = true;
}
#pragma warning(default: 4191)

// Program
PFNGLCREATEPROGRAMPROC glCreateProgram = NULL;
PFNGLDELETEPROGRAMPROC glDeleteProgram = NULL; 
PFNGLUSEPROGRAMPROC glUseProgram = NULL; 
PFNGLATTACHSHADERPROC glAttachShader = NULL; 
PFNGLDETACHSHADERPROC glDetachShader = NULL; 
PFNGLLINKPROGRAMPROC glLinkProgram = NULL; 
PFNGLGETPROGRAMIVPROC glGetProgramiv = NULL; 
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = NULL; 
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = NULL; 
PFNGLUNIFORM1IPROC glUniform1i = NULL; 
PFNGLUNIFORM2IPROC glUniform2i = NULL; 
PFNGLUNIFORM3IPROC glUniform3i = NULL; 
PFNGLUNIFORM4IPROC glUniform4i = NULL; 
PFNGLUNIFORM1IVPROC glUniform1iv = NULL; 
PFNGLUNIFORM2IVPROC glUniform2iv = NULL; 
PFNGLUNIFORM3IVPROC glUniform3iv = NULL; 
PFNGLUNIFORM4IVPROC glUniform4iv = NULL; 
PFNGLUNIFORM1FPROC glUniform1f = NULL; 
PFNGLUNIFORM2FPROC glUniform2f = NULL; 
PFNGLUNIFORM3FPROC glUniform3f = NULL; 
PFNGLUNIFORM4FPROC glUniform4f = NULL; 
PFNGLUNIFORM1FVPROC glUniform1fv = NULL; 
PFNGLUNIFORM2FVPROC glUniform2fv = NULL; 
PFNGLUNIFORM3FVPROC glUniform3fv = NULL; 
PFNGLUNIFORM4FVPROC glUniform4fv = NULL; 
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = NULL; 
PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv = NULL; 
PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv = NULL; 
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation = NULL; 
PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f = NULL; 
PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv = NULL; 
PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv = NULL; 
PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv = NULL; 
PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv = NULL; 
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = NULL; 
PFNGLENABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = NULL; 
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation = NULL; 
PFNGLMULTITEXCOORD2FPROC glMultiTexCoord2f = NULL; 
PFNGLMULTITEXCOORD2DPROC glMultiTexCoord2d = NULL; 

// Buffer
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = NULL;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = NULL;


// Shader
PFNGLCREATESHADERPROC glCreateShader = NULL; 
PFNGLDELETESHADERPROC glDeleteShader = NULL; 
PFNGLSHADERSOURCEPROC glShaderSource = NULL; 
PFNGLCOMPILESHADERPROC glCompileShader = NULL; 
PFNGLGETSHADERIVPROC glGetShaderiv = NULL; 
PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform = NULL; 

// VBO
PFNGLGENBUFFERSPROC glGenBuffers = NULL; 
PFNGLDELETEBUFFERSPROC glDeleteBuffers = NULL; 
PFNGLBINDBUFFERPROC glBindBuffer = NULL; 
PFNGLBUFFERDATAPROC glBufferData = NULL; 
PFNGLBUFFERSUBDATAPROC glBufferSubData = NULL; 
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = NULL; 

// FBO
PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers = NULL; 
PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers = NULL; 
PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer = NULL; 
PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus = NULL; 
PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D = NULL; 
PFNGLFRAMEBUFFERTEXTURE3DPROC glFramebufferTexture3D = NULL; 
PFNGLDRAWBUFFERSPROC glDrawBuffers = NULL; 
PFNGLACTIVETEXTUREPROC glActiveTexture = NULL; 
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = NULL; 

// MISC
PFNGLGENERATEMIPMAPPROC glGenerateMipmap = NULL;
PFNGLCLAMPCOLORARBPROC glClampColorARB = NULL;
PFNGLWINDOWPOS2IPROC glWindowPos2i = NULL;
PFNGLBLENDEQUATIONPROC glBlendEquation = NULL;
PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;

// 3D TEXTURES
PFNGLTEXIMAGE3DPROC glTexImage3D = NULL;
PFNGLFRAMEBUFFERTEXTURELAYERPROC glFramebufferTextureLayer = NULL;

// MORE
#define ADD_EXTENSION(type, name) type name = NULL;
#include "extensionlist.h"
#undef ADD_EXTENSION
