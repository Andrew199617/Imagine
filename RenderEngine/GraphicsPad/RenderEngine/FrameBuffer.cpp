#include "FrameBuffer.h"
#include "..\GameLogger.h"
#include "VertexShaderInfo.h"


FrameBuffer::FrameBuffer()
{

}


FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &frameBufferName);
}

void FrameBuffer::GenerateFBO(unsigned int width, unsigned int height)
{
	glGenFramebuffers(1, &frameBufferName);                     //Generate a framebuffer object(FBO)
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferName);         // and bind it to the pipeline

	GenerateColorTexture(width, height);//generate empty texture
	GenerateDepthTexture(width, height);//generate empty texture

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture_color, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);//optional


	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {  //Check for FBO completeness
		GameLogger::log("FrameBuffer is not complete");
		GameLogger::shutdownLog();
		exit(1);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);    //unbind framebuffer

}

void FrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferName);
}

void FrameBuffer::GenerateColorTexture(unsigned int width, unsigned int height)
{

	//glUniform1i(VertexShaderInfo::uRenderedTexUL, 2);
	glActiveTexture(GL_TEXTURE0 + 2);
	glGenTextures(1,&texture_color);
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, texture_color);

	// Give an empty image to OpenGL ( the last "0" )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, 0);

	// Poor filtering. Needed !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


}

void FrameBuffer::GenerateDepthTexture(unsigned int width, unsigned int height)
{
	glActiveTexture(GL_TEXTURE0 + 3);
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT24, width, height, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
}

void FrameBuffer::BindTexture()
{
	if (VertexShaderInfo::uRenderedTexUL > 0)
	{
		glActiveTexture(GL_TEXTURE0 + 2);
		glBindTexture(GL_TEXTURE_2D, texture_color);

	}
	glActiveTexture(GL_TEXTURE0 + 3);
	glBindTexture(GL_TEXTURE_2D, depthTexture);

}
