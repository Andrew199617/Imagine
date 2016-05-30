#include "FrameBuffer.h"
#include "..\GameLogger.h"


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
	//generateDepthTexture(width, height);//generate empty texture

	unsigned int attachment_index_color_texture = 0;   //to keep track of our textures
	//bind textures to pipeline. texture_depth is optional .0 is the mipmap level. 0 is the heightest
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachment_index_color_texture, texture_color, 0);
	//glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture_depth, 0);//optional


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
	glGenTextures(1, &texture_color);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, texture_color);

	// Give an empty image to OpenGL ( the last "0" )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	// Poor filtering. Needed !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}
