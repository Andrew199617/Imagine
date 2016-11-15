#include "VertexShaderInfo.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <windows.h>
#include "..\GameLogger.h"

using namespace std;

glm::vec3 VertexShaderInfo::lightPosition = glm::vec3(0, 0, 0);
float VertexShaderInfo::percentLerped = 0;
float VertexShaderInfo::uD = 1;
float VertexShaderInfo::uR = 1;
float VertexShaderInfo::uMax = .8f;
float VertexShaderInfo::uMin = .2f;
GLuint VertexShaderInfo::uRenderedTexUL = 0;

VertexShaderInfo::VertexShaderInfo(const char* path)
{
	this->shaderLocation = path;
	percentRippled = .1f;
	density = 0.5f;
	uR = 10.0f;
}

VertexShaderInfo::~VertexShaderInfo()
{
	glDeleteProgram(programID);
}

string ExePath2() {
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}

string VertexShaderInfo::readShaderCode(const char* filename)
{
	stringstream buffer;
	ifstream meInput(ExePath2() + "\\" + filename);
	if (!meInput.good())
	{
		cout << "my directory is " << ExePath2() << "\n";
		cout << "file failed to load..." << filename;
		cin.get();
		exit(1);
	}
	buffer << meInput.rdbuf();
	return buffer.str();

}

bool VertexShaderInfo::checkShaderStatus(GLuint shaderID)
{
	GLint compilestatus;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compilestatus);
	if (compilestatus != GL_TRUE)
	{
		GLint infoLogLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		glGetShaderInfoLog(shaderID, infoLogLength, &bufferSize, buffer);
		cout << buffer << endl;
		cin.get();
		delete[] buffer;
		return false;
	}
	return true;
}

bool VertexShaderInfo::checkProgStatus(GLuint m_programID)
{
	GLint linkstatus;
	glGetProgramiv(m_programID, GL_LINK_STATUS, &linkstatus);
	if (linkstatus != GL_TRUE)
	{
		GLint infoLogLength;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		glGetProgramInfoLog(m_programID, infoLogLength, &bufferSize, buffer);
		cout << buffer << endl;
		cin.get();
		delete[] buffer;
		return false;
	}
	return true;
}

void VertexShaderInfo::installShader(GLuint fragmentShaderID)
{
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	const char* adapter[1];
	string temp = readShaderCode(shaderLocation);
	adapter[0] = temp.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);
	

	glCompileShader(vertexShaderID);

	if (!checkShaderStatus(vertexShaderID) )
		return;


	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	if (!checkProgStatus(programID))
		return;

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	glUseProgram(programID);
	glValidateProgram(programID);

	GLint validatestatus;
	glGetProgramiv(programID, GL_VALIDATE_STATUS, &validatestatus);
	if (validatestatus != GL_TRUE)
	{
		GLint infoLogLength;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		glGetProgramInfoLog(programID, infoLogLength, &bufferSize, buffer);
		cout << buffer << endl;
		cin.get();
		delete[] buffer;
	}

	uPercentLerped = glGetUniformLocation(programID, "uPercentLerped");
	uLightPositionUL = glGetUniformLocation(programID, "uLightPosition");
	percentRippledUniformLocaton = glGetUniformLocation(programID, "percentRippled");
	densityUniformLocation = glGetUniformLocation(programID, "density");
	frequencyUniformLocation = glGetUniformLocation(programID, "uR");
	uDUniformLocation = glGetUniformLocation(programID, "uD");

	uObjectColor = glGetUniformLocation(programID, "objectColor");
	uMaxUL = glGetUniformLocation(programID, "uMax");
	uMinUL = glGetUniformLocation(programID, "uMin");
	uIsBumpedUL = glGetUniformLocation(programID, "isBumped");
	uRenderedTexUL = glGetUniformLocation(programID, "renderedTexture");
	uModelViewMatrixUL = glGetUniformLocation(programID,"uModelViewMatrix");
	uProjectionMatrixUL = glGetUniformLocation(programID, "uProjectionMatrix");
	uModelViewProjectionMatrixUL = glGetUniformLocation(programID, "uModelViewProjectionMatrix");
	uNormalMatrixUL = glGetUniformLocation(programID, "uNormalMatrix");
	GLuint uDepthTextureUL = glGetUniformLocation(programID, "depthTexture");

	glUniform1i(glGetUniformLocation(programID, "myTextureSampler"), 0);
	glUniform1i(glGetUniformLocation(programID, "bumpMap"), 1);
	glUniform1i(uRenderedTexUL, 2);
	glUniform1i(uDepthTextureUL, 3);
}

void VertexShaderInfo::useProgram()
{
	glUseProgram(programID);
}

GLuint VertexShaderInfo::getProgramID()
{
	return programID;
}