#include "EntityManager.h"
#include "Vertex.h"
#include <stdio.h>
#include "CollisionInfo.h"
#include "ConfigReader.h"
#include "GameLogger.h"
#include "SaveLogger.h"


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

	if (!InitializeSaveLoggerObjects())
	{
		string s = "Save Logger Objects did not initialize";
		GameLogger::log(s);
		return false;
	}
	
	GameLogger::log("Entity Manager Initialized");
	return true;
}

bool EntityManager::InitializeSaveLoggerObjects()
{
	num_Objs = SaveLogger::GetNumObjs();
	for (int i = 0; i < num_Objs; i++)
	{
		entities[i] = SceneryEntity();
	}
	for (int i = 0; i < num_Objs; i++)
	{
		entities[i].SetName(SaveLogger::GetName(i));
		entitieSpatials[i].position = SaveLogger::GetPosition(entities[i].GetName());
		string componentType = "SpatialComponent";
		entities[i].AddComponent(&entitieSpatials[i], entities[i].GetName() + componentType);
		componentType = "MeshComponent";
		entities[i].AddComponent(&entitieMeshs[i], entities[i].GetName() + componentType);
		if (!entities[i].Initialize())
		{
			string s = ": did not initialize";
			GameLogger::log(entities[i].GetName() + s);
			return false;
		}
	}

	return true;
}

void EntityManager::Update(float dt)
{
	TransformInfo::WorldToViewMatrix = playerCamera.getWorldToViewMatrix();
	static float m_dt = 0;
	m_dt += dt;	
	
	player.Update(dt);

	if (SaveLogger::ValueChanged())
	{
		RenderEngine::RemoveRenderInfo();
		
		if (!InitializeSaveLoggerObjects())
		{
			string s = "Save Logger Objects did not initialze";
			GameLogger::log(s);
			GameLogger::shutdownLog();
			exit(1);
		}
		SendDataToOpenGL();
	}

	for (int i = 0; i < num_Objs; i++)
	{
		entities[i].Update(dt);
	}

}

void EntityManager::ProcessKeys(float m_dt)
{
	playerKeyboard.ProcessKeys(m_dt);
}

void EntityManager::ProcessMouse(QMouseEvent* e)
{
	playerMouse.ProcessMouse(e);
}

void EntityManager::SendDataToOpenGL()
{
	TransformInfo::WorldToViewMatrix = playerCamera.getWorldToViewMatrix();
	/*AIWorldMesh.setRenderInfo("AIWorld");
	RenderEngine::AddRenderInfo(&AIWorldMesh.renderinfo);*/
	for (int i = 0; i < num_Objs; i++)
	{
		entitieMeshs[i].setRenderInfo(SaveLogger::GetObj(entities[i].GetName()));
		RenderEngine::AddRenderInfo(&entitieMeshs[i].renderinfo);
	}
	//playerGravity.DansMesh = &AIWorldMesh.renderinfo;
	
}


