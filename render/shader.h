#pragma once

enum ZShaderType
{
	kVertexShader = 0,
	kFragmentShader,
	kGeometryShader,
};

const GLenum kShaderType[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER};

class ZShader : public align16
{
public:
	ZShader(ZShaderType type);
	virtual ~ZShader(void);

	void Compile(const char** strings, uint32_t numStrings);
	void Compile(const char* str);
	void Unload();

	bool        DidCompile();
	const char* GetCompileErrors();

	GLuint      id;
	ZShaderType type;
};

