#include "FragmentShaderInfo.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <windows.h>
#include "..\GameLogger.h"

using namespace std;

FragmentShaderInfo::FragmentShaderInfo(const char* filename)
{
	shaderLocation = filename;
}


FragmentShaderInfo::~FragmentShaderInfo()
{
}

string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}

string FragmentShaderInfo::readShaderCode(const char* filename)
{
	stringstream buffer;
	ifstream meInput(ExePath() + "\\" + filename);

	if (!meInput.good())
	{
		string s = "file failed to load: ";
		GameLogger::log(s + ExePath() + filename);
		GameLogger::shutdownLog();
		exit(1);
	}
	buffer << meInput.rdbuf();
	return buffer.str();

}

bool FragmentShaderInfo::checkShaderStatus(GLuint shaderID)
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

GLuint FragmentShaderInfo::createShader()
{
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const char* adapter[1];
	string temp = readShaderCode(shaderLocation);
	adapter[0] = temp.c_str();
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	glCompileShader(fragmentShaderID);

	if ( !checkShaderStatus(fragmentShaderID))
		return (GLuint)-1;

	return fragmentShaderID;

}

void FragmentShaderInfo::deleteShader()
{
	glDeleteShader(fragmentShaderID);
}