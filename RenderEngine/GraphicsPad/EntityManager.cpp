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
#include "Physics\PhysicsTypeDefs.hpp"

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
		numComponent[i] = 2;
		entitieComponents[i] = GetComponents(i);
	}
	for (int i = 0; i < num_Objs; i++)
	{
		entities[i].SetName(saveLogger->GetName(i));
		entitieSpatials[i]->position = saveLogger->GetPosition(entities[i].GetName());
		entities[i].AddComponent(entitieSpatials[i], "Transform");
		entities[i].AddComponent(entitieMeshs[i], "Mesh");
		for (int j = 0; j < numComponent[i] - 2; ++j)
		{
			entities[i].AddComponent(entitieComponents[i][j], saveLogger->GetComponentName(i, j + 3).c_str());
			saveLogger->SetComponent(i, j + 3, entitieComponents[i][j]);
		}
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

void EntityManager::AddEntity()
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

bool EntityManager::UpdateSaveLoggerObjects()
{
	int pastNumObjs = num_Objs;
	num_Objs = saveLogger->GetNumObjs();

	entitieSpatials[pastNumObjs] = new SpatialComponent;
	entitieMeshs[pastNumObjs] = new MeshComponent;
	entities[pastNumObjs].SetName(saveLogger->GetName(pastNumObjs));
	entitieSpatials[pastNumObjs]->position = saveLogger->GetPosition(entities[pastNumObjs].GetName());
	entities[pastNumObjs].AddComponent(entitieSpatials[pastNumObjs], "Transform");
	entities[pastNumObjs].AddComponent(entitieMeshs[pastNumObjs], "Mesh");
	entitieMeshs[pastNumObjs]->setTransformInfo();
	entitieSpatials[pastNumObjs]->SetRotate(saveLogger->GetRotate(entities[pastNumObjs].GetName()));
	entitieSpatials[pastNumObjs]->SetScale(saveLogger->GetScale(entities[pastNumObjs].GetName()));
	if (!entities[pastNumObjs].Initialize())
	{
		string s = ": did not initialize";
		GameLogger::log(entities[pastNumObjs].GetName() + s);
		return false;
	}
	
	return true;
}

void EntityManager::SaveEntities()
{
	ImgnComponent** components;
	Imgn::DisplayData* displayData;
	for (int i = 0; i < num_Objs; ++i)
	{
		if (!entities[i].IsSaved())
		{
			components = entities[i].GetComponents();
			for (int iComponent = 0; iComponent < entities[i].GetNumComponents(); ++iComponent)
			{
				if (!components[iComponent]->IsSaved())
				{
					displayData = components[iComponent]->GetDisplayData();
					if (displayData)
						saveLogger->AddComponentData(i, components[iComponent]->GetName(), displayData);
				}
			}
		}
	}
}

void EntityManager::UpdateObjectPosition(int obj, glm::vec3 Position)
{
	entitieSpatials[obj]->SetPosition(Position);
	entitieSpatials[obj]->SetSaved(false);
}

void EntityManager::UpdateObjectRotate(int obj, glm::vec3 Rotation)
{
	glm::vec3 rotateInRadians = glm::vec3(Rotation.x * R_PI / 180, Rotation.y * R_PI / 180, Rotation.z * R_PI / 180);
	entitieSpatials[obj]->SetRotate(glm::quat(rotateInRadians));
	entitieSpatials[obj]->SetSaved(false);
}

void EntityManager::UpdateObjectScale(int obj, glm::vec3 Scale)
{
	entitieSpatials[obj]->SetScale(Scale);
	entitieSpatials[obj]->SetSaved(false);
}

void EntityManager::Update(float dt, bool isPlaying)
{
	TransformInfo::WorldToViewMatrix = playerCamera->getWorldToViewMatrix();
	
	player.Update(dt);

	if (isPlaying)
	{
		SaveEntities();
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
		entitieMeshs[i]->setRenderInfo(saveLogger->GetSceneName(i));
		RenderEngine::AddRenderInfo(&entitieMeshs[i]->renderinfo);
	}
	
}

void EntityManager::SendNewDataToOpenGL()
{
	entitieMeshs[num_Objs-1]->setRenderInfo(saveLogger->GetSceneName(num_Objs-1));
	RenderEngine::AddRenderInfo(&entitieMeshs[num_Objs-1]->renderinfo);
}

//DO NOT REMOVE THESE COMMENTS
//Add Here
#include "Physics/RigidBody.h"
#include "MovementComponent.h"

ImgnComponent ** EntityManager::GetComponents(int objNum)
{
	ImgnComponent** components = new ImgnComponent*[Imgn::MAX_COMPONENTS - 2];
	string name = saveLogger->GetName(objNum);
	int numComponents = 0;
	Imgn::DisplayData* displayData;
	int iVar = 0;

	if (name == "AIWorld")
	{																		
	}
	if (name == "Cube")
	{																		
		components[numComponents] = new MovementComponent();
		displayData = components[numComponents]->GetDisplayData();
		if (displayData)
		{
			iVar = 0; float* val0 = reinterpret_cast<float*>(displayData->values[iVar]); *val0 = (float)50.000000;
		}
		numComponents++;
		components[numComponents] = new Imgn::RigidBody();
		displayData = components[numComponents]->GetDisplayData();
		if (displayData)
		{
			iVar = 0; bool* val0 = reinterpret_cast<bool*>(displayData->values[iVar]); *val0 = (bool)1;
			iVar = 1; double* val1 = reinterpret_cast<double*>(displayData->values[iVar]); *val1 = (double)1.000000;
			iVar = 2; float* val2 = reinterpret_cast<float*>(displayData->values[iVar]); *val2 = (float)0.020000;
			iVar = 3; float* val3 = reinterpret_cast<float*>(displayData->values[iVar]); *val3 = (float)0.050000;
			iVar = 4; bool* val4 = reinterpret_cast<bool*>(displayData->values[iVar]); *val4 = (bool)1;
			iVar = 5; bool* val5 = reinterpret_cast<bool*>(displayData->values[iVar]); *val5 = (bool)0;
		}
		numComponents++;
	}

	numComponent[objNum] += numComponents;										
	return components;															
}																				
