#pragma once
#include "GL\glew.h"

class FrameBuffer
{
private:
	GLuint frameBufferName;
	GLuint texture_color;
	GLuint depthTexture;

private:
	void GenerateColorTexture(unsigned int width, unsigned int height);
	void GenerateDepthTexture(unsigned int width, unsigned int height);

public:
	FrameBuffer();
	~FrameBuffer();
	void GenerateFBO(unsigned int width, unsigned int height);
	void Bind();
	void BindTexture();
};

