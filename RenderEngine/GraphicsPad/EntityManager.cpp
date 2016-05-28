#include "EntityManager.h"
#include "Vertex.h"
#include <stdio.h>
#include "CollisionInfo.h"
#include "ConfigReader.h"
#include "GameLogger.h"


EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}

bool EntityManager::Initialize()
{
	player.SetName("Player");
	player.AddComponent(&playerSpatial, "PlayerSpatialComponent");
	player.AddComponent(&playerCamera, "PlayerCameraComponent");
	player.AddComponent(&playerKeyboard, "PlayerKeyboardComponent");
	player.AddComponent(&playerMouse, "PlayerMouseComponent");
	player.AddComponent(&playerMove, "PlayerMovementComponent");
	player.AddComponent(&playerShoot, "PlayerShootingComponent");
	//player.AddComponent(&playerGravity, "PlayerGravityComponent");
	//player.AddComponent(&batmanMesh, "PlayerMesh");
	if (!player.Initialize())
	{
		string s = ": did not initialize";
		GameLogger::log(player.GetName() + s);
		return false;
	}
	playerShoot.Disable();

	/*AIWorld.SetName("AIWorld");
	AIWorldSpatial.position = glm::vec3(0.0f, 0.0f, 0.0f);
	AIWorld.AddComponent(&AIWorldSpatial, "AIWorldSpatialComponent");
	AIWorldMesh.vertexShaderLocation = "..\\Graphicspad\\Shader\\VertexShaderCode.glsl";
	AIWorldMesh.fragmentShaderLocation = "..\\Graphicspad\\Shader\\fErosion.glsl";
	AIWorld.AddComponent(&AIWorldMesh, "AIWorldMeshComponent");
	if (!AIWorld.Initialize())
	{
		string s = ": did not initialize";
		GameLogger::log(AIWorld.GetName() + s);
		return false;
	}*/

	noisePlane.SetName("noisePlane");
	noisePlaneSpatial.position = glm::vec3(0.0f, 0.0f, 0.0f);
	noisePlane.AddComponent(&noisePlaneSpatial, "noisePlaneSpatialComponent");
	noisePlane.AddComponent(&noisePlaneMesh, "noisePlaneMeshComponent");
	if (!noisePlane.Initialize())
	{
		string s = ": did not initialize";
		GameLogger::log(noisePlane.GetName() + s);
		return false;
	}
	

	GameLogger::log("Entity Manager Initialized");
	return true;
}

void EntityManager::Update(float dt)
{
	TransformInfo::WorldToViewMatrix = playerCamera.getWorldToViewMatrix();
	static float m_dt = 0;
	m_dt += dt;	
	
	player.Update(dt);
	lightBulbSpatial.position = VertexShaderInfo::lightPosition;

	//AIWorld.Update(dt);
	noisePlane.Update(dt);

}

void EntityManager::ProcessKeys(float m_dt)
{
	playerKeyboard.ProcessKeys(m_dt);
}

void EntityManager::ProcessMouse(QMouseEvent* e)
{
	playerMouse.ProcessMouse(e);
}

void EntityManager::sendDataToOpenGL()
{
	TransformInfo::WorldToViewMatrix = playerCamera.getWorldToViewMatrix();
	/*AIWorldMesh.setRenderInfo("AIWorld");
	RenderEngine::AddRenderInfo(&AIWorldMesh.renderinfo);*/
	noisePlaneMesh.setRenderInfo("Plane");
	RenderEngine::AddRenderInfo(&noisePlaneMesh.renderinfo);
	//playerGravity.DansMesh = &AIWorldMesh.renderinfo;
	
}


