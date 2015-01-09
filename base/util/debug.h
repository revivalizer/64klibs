#pragma once

void vzmsg(const char* const str, va_list argp);
void _zmsg(const char* const str, ...);

#ifdef ENABLE_ZDEBUG
	#define zmsg(...) _zmsg(__VA_ARGS__)
	#define OGL(STAT) { GLenum err = glGetError(); STAT; err = glGetError(); if( err != GL_NO_ERROR ) zmsg("OpenGL error: %s(%i): %s", __FILE__,__LINE__,(char*)gluErrorString( err ) ); }
#else
	#define zmsg(...) void(0)
	#define OGL(STAT) STAT
#endif 