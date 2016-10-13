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
	currentlySelectedObject = 0;
	player.SetName("Player");
	player.AddComponent(&playerSpatial, "PlayerSpatialComponent");
	player.AddComponent(&playerCamera, "PlayerCameraComponent");
	player.AddComponent(&playerKeyboard, "PlayerKeyboardComponent");
	player.AddComponent(&playerMouse, "PlayerMouseComponent");
	player.AddComponent(&playerMove, "PlayerMovementComponent");
	player.AddComponent(&playerShoot, "PlayerShootingComponent");
	player.AddComponent(&objController, "PlayerShootingComponent");
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
	/*for (int i = 0; i < num_Objs; i++)
	{
		entities[i] = SceneryEntity();
	}*/
	for (int i = 0; i < num_Objs; i++)
	{
		entities[i].SetName(SaveLogger::GetName(i));
		entitieSpatials[i].position = SaveLogger::GetPosition(entities[i].GetName());
		string componentType = "SpatialComponent";
		entities[i].AddComponent(&entitieSpatials[i], entities[i].GetName() + componentType);
		componentType = "MeshComponent";
		entities[i].AddComponent(&entitieMeshs[i], entities[i].GetName() + componentType);
		entitieMeshs[i].setTransformInfo();
		entitieSpatials[i].SetRotate(SaveLogger::GetRotate(entities[i].GetName()));
		entitieSpatials[i].SetScale(SaveLogger::GetScale(entities[i].GetName()));
		if (!entities[i].Initialize())
		{
			string s = ": did not initialize";
			GameLogger::log(entities[i].GetName() + s);
			return false;
		}
	}

	return true;
}

bool EntityManager::UpdateSaveLoggerObjects()
{
	int pastNumObjs = num_Objs;
	num_Objs = SaveLogger::GetNumObjs();
	/*for (int i = pastNumObjs; i < num_Objs; i++)
	{
		entities[i] = SceneryEntity();
	}*/
	for (int i = pastNumObjs; i < num_Objs; i++)
	{
		entities[i].SetName(SaveLogger::GetName(i));
		entitieSpatials[i].position = SaveLogger::GetPosition(entities[i].GetName());
		string componentType = "SpatialComponent";
		entities[i].AddComponent(&entitieSpatials[i], entities[i].GetName() + componentType);
		componentType = "MeshComponent";
		entities[i].AddComponent(&entitieMeshs[i], entities[i].GetName() + componentType);
		entitieMeshs[i].setTransformInfo();
		entitieSpatials[i].SetRotate(SaveLogger::GetRotate(entities[i].GetName()));
		entitieSpatials[i].SetScale(SaveLogger::GetScale(entities[i].GetName()));
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

		if (!UpdateSaveLoggerObjects())
		{
			string s = "Save Logger Objects did not Update";
			GameLogger::log(s);
			GameLogger::shutdownLog();
			exit(1);
		}
		
		SendNewDataToOpenGL();
	}

	//objController.Update();
	objController.SetMeshs(num_Objs, entitieMeshs);

	for (int i = 0; i < num_Objs; i++)
	{
		entities[i].Update(dt);
	}
}

void EntityManager::ProcessKeys(float m_dt)
{
	playerKeyboard.ProcessKeys(m_dt);
	objController.ProcessKeys();
}

void EntityManager::ProcessMouseMove(QMouseEvent* e)
{
	playerMouse.ProcessMouseMove(e);
}

void EntityManager::ProcessMousePress(QMouseEvent * e)
{
	objController.ProcessMousePress(e, this);
}

void EntityManager::SendDataToOpenGL()
{
	TransformInfo::WorldToViewMatrix = playerCamera.getWorldToViewMatrix();
	for (int i = 0; i < num_Objs; i++)
	{
		entitieMeshs[i].setRenderInfo(SaveLogger::GetObj(entities[i].GetName()));
		RenderEngine::AddRenderInfo(&entitieMeshs[i].renderinfo);
	}
	
}

void EntityManager::SendNewDataToOpenGL()
{
	for (int i = num_Objs-1; i < num_Objs; i++)
	{
		entitieMeshs[i].setRenderInfo(SaveLogger::GetObj(entities[i].GetName()));
		RenderEngine::AddRenderInfo(&entitieMeshs[i].renderinfo);
	}
}


