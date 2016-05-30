#include "OriginalGame.h"
#include "MeGlWindow.h"
#include "GameLogger.h"
#include "SaveLogger.h"
#include "RenderEngine\FrameBuffer.h"

float dt;
GameTime gametime;
MeGlWindow* meGl;
EntityManager entityManager;
FrameBuffer frameBuffer;

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

	entityManager.SendDataToOpenGL();
}

bool OriginalGame::Initialize(MeGlWindow* meGlWindow)
{
	glewInit();
	meGl = meGlWindow;
	SaveLogger::intialize();

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
	SendDataToOpenGL();
	//frameBuffer.GenerateFBO(1920, 1080);

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
	//frameBuffer.Bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, 1920, 1080);

	RenderEngine::Draw();

}

