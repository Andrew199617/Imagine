#include "EntityManager.h"
#include <stdio.h>
#include "ConfigReader.h"
#include "GameLogger.h"
#include "SaveLogger.h"
#include "DetailsLayout.h"
#pragma warning(push)
#pragma warning (disable:4127)
#include <QtGui\qkeyevent>
#pragma warning(pop)
#include <Windows.h>
#include "KeyboardComponent.h"
#include "MouseComponent.h"
#include "ObjectSelectorComponent.h"
#include "MeshComponent.h"
#include "MovementComponent.h"
#include "RenderEngine\RenderEngine.h"



EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
	delete playerCamera;
	delete playerKeyboard;
	delete playerMove;
	delete playerMouse;
	delete playerSpatial;
	delete objController;
}

bool EntityManager::Initialize()
{
	saveLogger = SaveLogger::Instance();
	currentlySelectedObject = -1;
	player.SetName("Player");
	player.AddComponent(playerSpatial = new SpatialComponent, "PlayerSpatialComponent");
	player.AddComponent(playerCamera = new CameraComponent, "PlayerCameraComponent");
	player.AddComponent(playerKeyboard = new KeyboardComponent, "PlayerKeyboardComponent");
	player.AddComponent(playerMouse = new MouseComponent, "PlayerMouseComponent");
	player.AddComponent(playerMove = new MovementComponent, "PlayerMovementComponent");
	player.AddComponent(objController = new ObjectSelectorComponent, "PlayerShootingComponent");
	if (!player.Initialize())
	{
		string s = ": did not initialize";
		GameLogger::log(player.GetName() + s);
		return false;
	}

	if (!InitializeSaveLoggerObjects())
	{
		string s = "Save Logger Objects did not initialize";
		GameLogger::log(s);
		return false;
	}

	if (num_Objs > 0)
	{
		currentlySelectedObject = 0;
		DetailsLayout::Instance()->SetEntity(&entities[0]);
		objController->SetMeshs(num_Objs, entitieMeshs);
	}
	GameLogger::log("Imgn::Entity Manager Initialized");
	return true;
}

bool EntityManager::InitializeSaveLoggerObjects()
{
	num_Objs = saveLogger->GetNumObjs();
	for (int i = 0; i < num_Objs; i++)
	{
		entitieSpatials[i] = new SpatialComponent;
		entitieMeshs[i] = new MeshComponent;
	}
	for (int i = 0; i < num_Objs; i++)
	{
		entities[i].SetName(saveLogger->GetName(i));
		entitieSpatials[i]->position = saveLogger->GetPosition(entities[i].GetName());
		string componentType = "Transform";
		entities[i].AddComponent(entitieSpatials[i], componentType);
		componentType = "Mesh";
		entities[i].AddComponent(entitieMeshs[i], componentType);
		entitieMeshs[i]->setTransformInfo();
		entitieSpatials[i]->SetRotate(saveLogger->GetRotate(entities[i].GetName()));
		entitieSpatials[i]->SetScale(saveLogger->GetScale(entities[i].GetName()));
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
	num_Objs = saveLogger->GetNumObjs();
	for (int i = pastNumObjs; i < num_Objs; i++)
	{
		entitieSpatials[i] = new SpatialComponent;
		entitieMeshs[i] = new MeshComponent;
	}
	for (int i = pastNumObjs; i < num_Objs; i++)
	{
		entities[i].SetName(saveLogger->GetName(i));
		entitieSpatials[i]->position = saveLogger->GetPosition(entities[i].GetName());
		string componentType = "Transform";
		entities[i].AddComponent(entitieSpatials[i], componentType);
		componentType = "Mesh";
		entities[i].AddComponent(entitieMeshs[i], componentType);
		entitieMeshs[i]->setTransformInfo();
		entitieSpatials[i]->SetRotate(saveLogger->GetRotate(entities[i].GetName()));
		entitieSpatials[i]->SetScale(saveLogger->GetScale(entities[i].GetName()));
		if (!entities[i].Initialize())
		{
			string s = ": did not initialize";
			GameLogger::log(entities[i].GetName() + s);
			return false;
		}
	}

	return true;
}



void EntityManager::Update(float dt, bool isPlaying)
{
	TransformInfo::WorldToViewMatrix = playerCamera->getWorldToViewMatrix();
	
	player.Update(dt);

	if (saveLogger->ValueChanged())
	{

		if (!UpdateSaveLoggerObjects())
		{
			string s = "Save Logger Objects did not Update";
			GameLogger::log(s);
			GameLogger::shutdownLog();
			exit(1);
		}

		objController->SetMeshs(num_Objs, entitieMeshs);
		SendNewDataToOpenGL();
	}

	if (isPlaying)
	{
		for (int i = 0; i < num_Objs; i++)
		{
			entities[i].Update(dt);
		}
	}
}

void EntityManager::ProcessKeys(float m_dt)
{
	playerKeyboard->ProcessKeys(m_dt);
	objController->ProcessKeys();
}

void EntityManager::ProcessMouseMove(QMouseEvent* e)
{
	playerMouse->ProcessMouseMove(e);
}

void EntityManager::ProcessMousePress(QMouseEvent * e)
{
	objController->ProcessMousePress(e, this);
}

void EntityManager::SendDataToOpenGL()
{
	TransformInfo::WorldToViewMatrix = playerCamera->getWorldToViewMatrix();
	for (int i = 0; i < num_Objs; i++)
	{
		entitieMeshs[i]->setRenderInfo(saveLogger->GetObj(entities[i].GetName()));
		RenderEngine::AddRenderInfo(&entitieMeshs[i]->renderinfo);
	}
	
}

void EntityManager::SendNewDataToOpenGL()
{
	for (int i = num_Objs-1; i < num_Objs; i++)
	{
		entitieMeshs[i]->setRenderInfo(saveLogger->GetObj(entities[i].GetName()));
		RenderEngine::AddRenderInfo(&entitieMeshs[i]->renderinfo);
	}
}


