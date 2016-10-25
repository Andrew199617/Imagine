#include "OriginalGame.h"
#include "GameLogger.h"
#include "SaveLogger.h"
#include "RenderEngine\VertexShaderInfo.h"
#include "RenderEngine\FragmentShaderInfo.h"
#include "RenderEngine\RenderEngine.h"
#include "gtx\transform.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using glm::mat4;

GameTime gametime;
VertexShaderInfo vertexShaderInfo;
FragmentShaderInfo fragmentShaderInfo;

static const GLfloat g_quad_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	-1.0f,  1.0f, 0.0f,
	-1.0f,  1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	1.0f,  1.0f, 0.0f,
};
GLuint quad_vertexbuffer;
GLuint quad_VertexArrayID;
GLuint uDiscardBasedOfDepthUL;
GLuint uRegularDepthUL;

EntityManager OriginalGame::entityManager;

void OriginalGame::SetWidth(int Width)
{
	m_Width = Width; 
	if(frameBuffer)
		delete frameBuffer; 
	frameBuffer = new FrameBuffer; 
	frameBuffer->GenerateFBO(m_Width, m_Height);
}

void OriginalGame::SetHeight(int Height)
{
	m_Height = Height; 
	if (frameBuffer)
		delete frameBuffer; 
	frameBuffer = new FrameBuffer; 
	frameBuffer->GenerateFBO(m_Width, m_Height);
}

OriginalGame::OriginalGame()
{

}


OriginalGame::~OriginalGame()
{
	glDeleteVertexArrays(1, &quad_VertexArrayID);
	glDeleteBuffers(1, &quad_vertexbuffer);
}

void OriginalGame::SendDataToOpenGL()
{
	mat4 projectionMatrix = glm::perspective(90.0f, ((float)m_Width) / m_Height, 1.0f, 180.0f);
	TransformInfo::projectionMatrix = projectionMatrix;

	glGenVertexArrays(1, &quad_VertexArrayID);
	glBindVertexArray(quad_VertexArrayID);

	glGenBuffers(1, &quad_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);
	
	vertexShaderInfo.shaderLocation = "..\\GraphicsPad\\Shader\\vPassThrough.glsl";
	fragmentShaderInfo.shaderLocation = "..\\GraphicsPad\\Shader\\fragmentShaderCode.glsl";
	GLuint fragmentShaderID = fragmentShaderInfo.createShader();
	vertexShaderInfo.installShader(fragmentShaderID);

	uDiscardBasedOfDepthUL = glGetUniformLocation(vertexShaderInfo.getProgramID(), "discardBasedOfDepth");
	uRegularDepthUL = glGetUniformLocation(vertexShaderInfo.getProgramID(), "regularDepth");

	glUniform1i(uDiscardBasedOfDepthUL, true);
	glUniform1i(uRegularDepthUL, false);

	entityManager.SendDataToOpenGL();
}

void OriginalGame::InitializeGl()
{
	glewInit();
	m_Width = 1920;
	m_Height = 1080;
	xOffset = 0;
	yOffset = 0;
	frameBuffer = new FrameBuffer;

	glClearColor(0.0f, 0.0f, 0.1f, 0.5f);
	glClearDepth(10.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	frameBuffer->GenerateFBO(m_Width, m_Height);
	SendDataToOpenGL();
}

bool OriginalGame::Initialize()
{
	isPlaying = false;

	if (!entityManager.Initialize())
	{
		GameLogger::log("Entity Manager did not Initialize");
		return false;
	}

	GameLogger::log("Original Game initialized");
	return true;
}

void OriginalGame::Update(bool focus)
{
	gametime.newFrame();
	float dt = gametime.timeElapsedLastFrame();

	if(focus)
	ProcessKeys(dt);

	entityManager.Update(dt,isPlaying);
	
	Draw(dt);
}

void OriginalGame::ProcessKeys(float m_dt)
{
	entityManager.ProcessKeys(m_dt);
}

void OriginalGame::ProcessMouseMove(QMouseEvent* e)
{
	entityManager.ProcessMouseMove(e);
}

void OriginalGame::ProcessMousePress(QMouseEvent * e)
{
	entityManager.ProcessMousePress(e);
}

void OriginalGame::Draw(float dt)
{
	frameBuffer->Bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, m_Width, m_Height);
	RenderEngine::Draw(dt,isPlaying);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	vertexShaderInfo.useProgram();

	frameBuffer->BindTexture();

	glViewport(xOffset, yOffset, m_Width, m_Height);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);
	if (entityManager.num_Objs != 0)
	{
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}

