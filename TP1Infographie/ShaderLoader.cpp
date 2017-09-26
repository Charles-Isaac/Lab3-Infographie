#include "ShaderLoader.h"

#include <iostream>
#include <fstream>
#include <vector>

ShaderLoader::ShaderLoader() {}
ShaderLoader::~ShaderLoader() {}

std::string ShaderLoader::ReadShader(char* filename)
{
	std::string shaderCode;

	std::ifstream file(filename, std::ios::in);
	if (!file.good())
	{
		std::cout << "can't read file " << filename << std::endl;
		std::terminate();
	}
	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	
	file.seekg(0, std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}


GLuint ShaderLoader::CreateShader(GLenum shaderType, std::string source, char* shaderName)
{
	int compileResult = 0;
	GLuint shader = glCreateShader(shaderType);
	const char* shaderCodePtr = source.c_str();
	const int shaderCodeSize = source.size();

	glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize);
	glCompileShader(shader);
	
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

	if (compileResult == GL_FALSE)
	{
		int infoLogLenght = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLenght);
		std::vector<char> shaderLog(infoLogLenght);
		glGetShaderInfoLog(shader, infoLogLenght, NULL, &shaderLog[0]);
		std::cout << "Error compiling shader: " << shaderName << std::endl << &shaderLog[0] << std::endl;
		return 0;
	}
	return shader;
}


GLuint ShaderLoader::CreateProgram(char* VertexShaderFilename, char* FragmentShaderFilename)
{
	std::string vertexShaderCode = ReadShader(VertexShaderFilename);
	std::string fragmentShaderCode = ReadShader(FragmentShaderFilename);

	GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderCode, "vertex shader");
	GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderCode, "fragment shader");

	int linkResult = 0;

	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	//glBindFragDataLocation(program, 1, "color");
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);
	
	if (linkResult == GL_FALSE)
	{
		int infoLogLenght = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLenght);
		std::vector<char> programLog(infoLogLenght);
		glGetProgramInfoLog(program, infoLogLenght, NULL, &programLog[0]);
		std::cout << "shader loader : LINK_ERROR" << std::endl << &programLog[0] << std::endl;
		return 0;
	}
	return program;
}