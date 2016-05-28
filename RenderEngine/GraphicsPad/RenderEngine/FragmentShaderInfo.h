#pragma once
#include "GL\glew.h"
#include <string>

class FragmentShaderInfo
{
public:
	FragmentShaderInfo(const char* = "..\\Graphicspad\\Shader\\fragmentShaderCode.glsl");
	~FragmentShaderInfo();
	std::string readShaderCode(const char* filename);
	bool checkShaderStatus(GLuint shaderID);
	bool checkProgStatus(GLuint programID);
	GLuint createShader();
	void deleteShader();
	const char* shaderLocation;
	GLuint fragmentShaderID;
};

