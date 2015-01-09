#pragma once

void InitOpenGLExtensions();

// Program
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLDELETEPROGRAMPROC glDeleteProgram; 
extern PFNGLUSEPROGRAMPROC glUseProgram; 
extern PFNGLATTACHSHADERPROC glAttachShader; 
extern PFNGLDETACHSHADERPROC glDetachShader; 
extern PFNGLLINKPROGRAMPROC glLinkProgram; 
extern PFNGLGETPROGRAMIVPROC glGetProgramiv; 
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog; 
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation; 
extern PFNGLUNIFORM1IPROC glUniform1i; 
extern PFNGLUNIFORM2IPROC glUniform2i; 
extern PFNGLUNIFORM3IPROC glUniform3i; 
extern PFNGLUNIFORM4IPROC glUniform4i; 
extern PFNGLUNIFORM1IVPROC glUniform1iv; 
extern PFNGLUNIFORM2IVPROC glUniform2iv; 
extern PFNGLUNIFORM3IVPROC glUniform3iv; 
extern PFNGLUNIFORM4IVPROC glUniform4iv; 
extern PFNGLUNIFORM1FPROC glUniform1f; 
extern PFNGLUNIFORM2FPROC glUniform2f; 
extern PFNGLUNIFORM3FPROC glUniform3f; 
extern PFNGLUNIFORM4FPROC glUniform4f; 
extern PFNGLUNIFORM1FVPROC glUniform1fv; 
extern PFNGLUNIFORM2FVPROC glUniform2fv; 
extern PFNGLUNIFORM3FVPROC glUniform3fv; 
extern PFNGLUNIFORM4FVPROC glUniform4fv; 
extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv; 
extern PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv; 
extern PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv; 
extern PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation; 
extern PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f; 
extern PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv; 
extern PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv; 
extern PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv; 
extern PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv; 
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray; 
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray; 
extern PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation; 
extern PFNGLMULTITEXCOORD2FPROC glMultiTexCoord2f; 
extern PFNGLMULTITEXCOORD2DPROC glMultiTexCoord2d; 

// Buffers
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;

// Shader
extern PFNGLCREATESHADERPROC glCreateShader; 
extern PFNGLDELETESHADERPROC glDeleteShader; 
extern PFNGLSHADERSOURCEPROC glShaderSource; 
extern PFNGLCOMPILESHADERPROC glCompileShader; 
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform; 

// VBO
extern PFNGLGENBUFFERSPROC glGenBuffers; 
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers; 
extern PFNGLBINDBUFFERPROC glBindBuffer; 
extern PFNGLBUFFERDATAPROC glBufferData; 
extern PFNGLBUFFERSUBDATAPROC glBufferSubData; 
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer; 

// FBO
extern PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers; 
extern PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers; 
extern PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer; 
extern PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus; 
extern PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D; 
extern PFNGLFRAMEBUFFERTEXTURE3DPROC glFramebufferTexture3D; 
extern PFNGLDRAWBUFFERSPROC glDrawBuffers; 
extern PFNGLACTIVETEXTUREPROC glActiveTexture; 
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog; 

// MISC
extern PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
extern PFNGLCLAMPCOLORARBPROC glClampColorARB;
extern PFNGLWINDOWPOS2IPROC glWindowPos2i;
extern PFNGLBLENDEQUATIONPROC glBlendEquation;
extern PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;

// TEXTURE
extern PFNGLTEXIMAGE3DPROC glTexImage3D;
extern PFNGLFRAMEBUFFERTEXTURELAYERPROC glFramebufferTextureLayer;

//#define ADD_EXTENSION(type, name) extern type name;
#define ADD_EXTENSION(type, name) extern type name;
#include "extensionlist.h"
#undef ADD_EXTENSION
