#pragma once

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>

class ShaderLoader
{
public:
	ShaderLoader(void);
	~ShaderLoader(void);
	GLuint CreateProgram(char* VertexShaderFilename, char* FragmentShaderFilename);

private:
	std::string ReadShader(char* Filename);
	GLuint CreateShader(GLenum shaderType, std::string source, char* shaderName);
};