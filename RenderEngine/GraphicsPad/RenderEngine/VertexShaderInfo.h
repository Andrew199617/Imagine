#pragma once
#include "GL\glew.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm.hpp>
#pragma warning(pop)
#include <string>
#include "..\ConfigReader.h"

class VertexShaderInfo
{
public:
	VertexShaderInfo(const char* path = "..\\Graphicspad\\Shader\\VertexShaderCode.glsl");
	~VertexShaderInfo();
	std::string readShaderCode(const char* filename);
	bool checkShaderStatus(GLuint shaderID);
	bool checkProgStatus(GLuint programID);
	void installShader(GLuint fragmentShaderID);
	void useProgram();
	GLuint getProgramID();

public:
	//UL = UniformLocation
	const char* shaderLocation;
	GLuint programID;

	GLint uPercentLerped;
	static float percentLerped;
	GLint uLightPositionUL;
	static glm::vec3 lightPosition;
	GLint percentRippledUniformLocaton;
	GLint densityUniformLocation;
	GLint frequencyUniformLocation;
	float percentRippled;
	float density;
	static bool isBumped;
	static float uMin, uMax;

	static float uR;
	static float uD;
	
	GLint uDUniformLocation;
	GLint uMinUL, uMaxUL;
	GLint uTexCoordOffsetUL;
	GLint uIsBumpedUL;
	GLint uBumpMapUL;
	GLint uTextureUL;
	GLint uModelViewMatrixUL;
	GLint uProjectionMatrixUL;
	GLint uModelViewProjectionMatrixUL;
	GLint uNormalMatrixUL;

	static GLuint uRenderedTexUL;
};

