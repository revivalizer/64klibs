#include "pch.h"
#include "shader.h"

ZShader::ZShader(ZShaderType type)
	: id(0)
	, type(type)
{
}


ZShader::~ZShader(void)
{
	Unload();
}

void ZShader::Compile(const char** strings, uint32_t numStrings)
{
	if (id==0)
		id = glCreateShader(kShaderType[type]);

	glShaderSource(id, numStrings, strings, nullptr);
	glCompileShader(id);
}

void ZShader::Compile(const char* str)
{
	const char* strings[] = {str, nullptr};
	Compile(strings, 1);
}

void ZShader::Unload()
{
	if (id>0)
	{
		glDeleteShader(id);
		id = 0;
	}
}

bool ZShader::DidCompile()
{
	GLint res;
	glGetShaderiv(id, GL_COMPILE_STATUS, &res);
	return res==GL_TRUE;
}

const char* ZShader::GetCompileErrors()
{
	GLint size;
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &size);
	char* str = new char[size+1];
	glGetShaderInfoLog(id, size+1, nullptr, str);
	str[size] = '\0'; // This handles case with 0 log length (needs size+1)
	return str;
}
