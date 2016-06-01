#include "OriginalGame.h"
#include "MeGlWindow.h"
#include "GameLogger.h"
#include "SaveLogger.h"
#include "RenderEngine\FrameBuffer.h"
#include "RenderEngine\VertexShaderInfo.h"
#include "RenderEngine\FragmentShaderInfo.h"
#include "PostProcessingModel.h"

float dt;
GameTime gametime;
MeGlWindow* meGl;
EntityManager entityManager;
FrameBuffer frameBuffer;
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

OriginalGame::OriginalGame()
{

}


OriginalGame::~OriginalGame()
{
	
}

void OriginalGame::SendDataToOpenGL()
{
	mat4 projectionMatrix = perspective(60.0f, ((float)meGl->width()) / meGl->height(), 1.0f, 180.0f);
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

	entityManager.SendDataToOpenGL();
}

bool OriginalGame::Initialize(MeGlWindow* meGlWindow)
{
	glewInit();
	meGl = meGlWindow;
	SaveLogger::intialize();


	glClearColor(0.0f, 0.0f, 0.1f, 0.5f);
	glClearDepth(10.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


	if (!entityManager.Initialize())
	{
		GameLogger::log("Entity Manager did not Initialize");
		meGl->shutdown();
		return false;
	}

	frameBuffer.GenerateFBO(1920, 1080);
	SendDataToOpenGL();

	GameLogger::log("Original Game initialized");
	return true;
}

bool OriginalGame::Shutdown()
{
	if (GetAsyncKeyState(88) != 0 || GetAsyncKeyState(27) != 0)
	{
		meGl->shutdown();
		return true;
	}
	return false;
}

void OriginalGame::Update()
{
	gametime.newFrame();
	dt = gametime.timeElapsedLastFrame();
	
	VertexShaderInfo::uD = theModel.uD;
	VertexShaderInfo::uR = theModel.uR;

	ProcessKeys(dt);

	entityManager.Update(dt);
	
	Draw();
	Shutdown();
}

void OriginalGame::ProcessKeys(float m_dt)
{
	entityManager.ProcessKeys(m_dt);
}

void OriginalGame::ProcessMouse(QMouseEvent* e)
{
	entityManager.ProcessMouse(e);
}

void OriginalGame::Draw()
{
	frameBuffer.Bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, 1920, 1080);

	RenderEngine::Draw();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	vertexShaderInfo.useProgram();

	frameBuffer.BindTexture();

	glUniform1i(uDiscardBasedOfDepthUL, PostProcessingModel::discardBasedOnDepth);
	glUniform1i(uRegularDepthUL, PostProcessingModel::regularDepth);

	glViewport(0, 0, 1920, 1080);
	glEnableVertexAttribArray(0);
	//glBindVertexArray(quad_VertexArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//RenderEngine::Draw();
}

