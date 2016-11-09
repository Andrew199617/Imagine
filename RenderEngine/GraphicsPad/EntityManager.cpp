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
		entitieMeshs[i] = new MeshComponent;
		numComponent[i] = 0;
		entitieComponents[i] = GetComponents(i);
	}
	for (int i = 0; i < num_Objs; i++)
	{
		entities[i].SetName(saveLogger->GetName(i));

		SpatialComponent* spatial = new SpatialComponent;
		spatial->SetPosition(saveLogger->GetComponentData(i, 2, 0));
		spatial->SetRotation(saveLogger->GetComponentData(i, 2, 1));
		spatial->SetScale(saveLogger->GetComponentData(i, 2, 2));
		entitieComponents[i][0] = spatial;
		entities[i].AddComponent(entitieComponents[i][0], "SpatialComponent");
		saveLogger->SetComponent(i, 2, entitieComponents[i][0]);

		entities[i].AddComponent(entitieMeshs[i], "Mesh");

		for (int j = 1; j < numComponent[i]; ++j)
		{
			entities[i].AddComponent(entitieComponents[i][j], saveLogger->GetComponentName(i, j + 2).c_str());
			saveLogger->SetComponent(i, j + 2, entitieComponents[i][j]);
		}
		entitieMeshs[i]->setTransformInfo();
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

	SpatialComponent* spatial = new SpatialComponent;
	entitieMeshs[pastNumObjs] = new MeshComponent;

	entities[pastNumObjs].SetName(saveLogger->GetName(pastNumObjs));
	entities[pastNumObjs].AddComponent(entitieMeshs[pastNumObjs], "Mesh");
	entities[pastNumObjs].AddComponent(spatial, "SpatialComponent");
	saveLogger->SetComponent(pastNumObjs, 2, spatial);
	entitieMeshs[pastNumObjs]->setTransformInfo();
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
					components[iComponent]->SetSaved(true);
				}
			}
		}
	}
}

void EntityManager::Update(float dt, bool isPlaying)
{
	TransformInfo::WorldToViewMatrix = playerCamera->getWorldToViewMatrix();
	
	player.Update(dt);

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
#include "CollisionDetection/BoxCollider.h"
#include "Physics/RigidBody.h"
#include "MovementComponent.h"
#include "CollisionDetection/SphereCollider.h"

ImgnComponent ** EntityManager::GetComponents(int objNum)
{
	ImgnComponent** components;
	string name = saveLogger->GetName(objNum);
	int numComponents = 1;
	Imgn::DisplayData* displayData;
	int iVar = 0;

	if (name == "AIWorld")
	{																		
	components = new ImgnComponent*[3];
		components[numComponents] = new BoxCollider();
		displayData = components[numComponents]->GetDisplayData();
		if (displayData)
		{
			iVar = 0; bool* val0 = reinterpret_cast<bool*>(displayData->values[iVar]); *val0 = (bool)0;
			iVar = 1; glm::detail::tvec3<float>* val1 = reinterpret_cast<glm::detail::tvec3<float>*>(displayData->values[iVar]); *val1 = glm::vec3(0.000000,-0.100000,0.000000);
			iVar = 2; glm::detail::tvec3<float>* val2 = reinterpret_cast<glm::detail::tvec3<float>*>(displayData->values[iVar]); *val2 = glm::vec3(333.000000,0.200000,280.000000);
		}
		numComponents++;
	}
	if (name == "Cube")
	{																		
	components = new ImgnComponent*[5];
		components[numComponents] = new MovementComponent();
		displayData = components[numComponents]->GetDisplayData();
		if (displayData)
		{
		}
		numComponents++;
		components[numComponents] = new Imgn::RigidBody();
		displayData = components[numComponents]->GetDisplayData();
		if (displayData)
		{
			iVar = 0; bool* val0 = reinterpret_cast<bool*>(displayData->values[iVar]); *val0 = (bool)1;
			iVar = 1; double* val1 = reinterpret_cast<double*>(displayData->values[iVar]); *val1 = (double)1.000000;
			iVar = 2; float* val2 = reinterpret_cast<float*>(displayData->values[iVar]); *val2 = (float)0.050000;
			iVar = 3; float* val3 = reinterpret_cast<float*>(displayData->values[iVar]); *val3 = (float)0.050000;
			iVar = 4; glm::detail::tvec3<float>* val4 = reinterpret_cast<glm::detail::tvec3<float>*>(displayData->values[iVar]); *val4 = glm::vec3(0.000000,-9.800000,0.000000);
			iVar = 5; bool* val5 = reinterpret_cast<bool*>(displayData->values[iVar]); *val5 = (bool)1;
			iVar = 6; bool* val6 = reinterpret_cast<bool*>(displayData->values[iVar]); *val6 = (bool)0;
		}
		numComponents++;
		components[numComponents] = new BoxCollider();
		displayData = components[numComponents]->GetDisplayData();
		if (displayData)
		{
			iVar = 0; bool* val0 = reinterpret_cast<bool*>(displayData->values[iVar]); *val0 = (bool)0;
			iVar = 1; glm::detail::tvec3<float>* val1 = reinterpret_cast<glm::detail::tvec3<float>*>(displayData->values[iVar]); *val1 = glm::vec3(0.000000,0.000000,0.000000);
			iVar = 2; glm::detail::tvec3<float>* val2 = reinterpret_cast<glm::detail::tvec3<float>*>(displayData->values[iVar]); *val2 = glm::vec3(2.000000,2.000000,2.000000);
		}
		numComponents++;
	}
	if (name == "Sphere3")
	{																		
	components = new ImgnComponent*[4];
		components[numComponents] = new Imgn::RigidBody();
		displayData = components[numComponents]->GetDisplayData();
		if (displayData)
		{
			iVar = 0; bool* val0 = reinterpret_cast<bool*>(displayData->values[iVar]); *val0 = (bool)1;
			iVar = 1; double* val1 = reinterpret_cast<double*>(displayData->values[iVar]); *val1 = (double)1.000000;
			iVar = 2; float* val2 = reinterpret_cast<float*>(displayData->values[iVar]); *val2 = (float)0.050000;
			iVar = 3; float* val3 = reinterpret_cast<float*>(displayData->values[iVar]); *val3 = (float)0.050000;
			iVar = 4; glm::detail::tvec3<float>* val4 = reinterpret_cast<glm::detail::tvec3<float>*>(displayData->values[iVar]); *val4 = glm::vec3(0.000000,-18.799999,0.000000);
			iVar = 5; bool* val5 = reinterpret_cast<bool*>(displayData->values[iVar]); *val5 = (bool)1;
			iVar = 6; bool* val6 = reinterpret_cast<bool*>(displayData->values[iVar]); *val6 = (bool)0;
		}
		numComponents++;
		components[numComponents] = new SphereCollider();
		displayData = components[numComponents]->GetDisplayData();
		if (displayData)
		{
			iVar = 0; bool* val0 = reinterpret_cast<bool*>(displayData->values[iVar]); *val0 = (bool)0;
			iVar = 1; glm::detail::tvec3<float>* val1 = reinterpret_cast<glm::detail::tvec3<float>*>(displayData->values[iVar]); *val1 = glm::vec3(0.000000,0.000000,0.000000);
			iVar = 2; float* val2 = reinterpret_cast<float*>(displayData->values[iVar]); *val2 = (float)1.000000;
		}
		numComponents++;
	}

	if(numComponents == 1){ components = new ImgnComponent*[1]; }
	numComponent[objNum] += numComponents;
	return components;
}
