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
#include "Hierarchy.h"


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

void EntityManager::SetCurrentlySelectedObject(int ObjSelected)
{
	currentlySelectedObject = ObjSelected;
	DetailsLayout::Instance()->SetEntity(&entities[ObjSelected]);
	Hierarchy::Instance()->SetEntity(entities[ObjSelected].GetName());
	SpatialComponent* spatial = entities[ObjSelected].GetComponentByType<SpatialComponent>();
	//objectTransformer.SetPosition(spatial->GetPosition());
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

	/*if (!objectTransformer.Initialize())
	{
		string s = ": did not initialize";
		GameLogger::log(player.GetName() + s);
		return false;
	}*/

	if (!InitializeSaveLoggerObjects())
	{
		string s = "Save Logger Objects did not initialize";
		GameLogger::log(s);
		return false;
	}

	if (num_Objs > 0)
	{
		//currentlySelectedObject = 0;
		//DetailsLayout::Instance()->SetEntity(&entities[0]);
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
		spatial->SetPosition(saveLogger->GetSpatialData(i, 0));
		spatial->SetRotation(saveLogger->GetSpatialData(i, 1));
		spatial->SetScale(saveLogger->GetSpatialData(i, 2));
		entitieComponents[i][0] = spatial;
		entities[i].AddComponent(entitieComponents[i][0], "SpatialComponent");
		saveLogger->SetComponent(i, 2, entitieComponents[i][0]);

		entities[i].AddComponent(entitieMeshs[i], "MeshComponent");
		entitieMeshs[i]->SetTexPath(saveLogger->GetMeshData(i, 0));
		saveLogger->SetComponent(i, 1, entitieMeshs[i]);

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
	Hierarchy::Instance()->AddEntity(entities[num_Objs-1]);
}

bool EntityManager::UpdateSaveLoggerObjects()
{
	int pastNumObjs = num_Objs;
	num_Objs = saveLogger->GetNumObjs();

	entities[pastNumObjs].SetName(saveLogger->GetName(pastNumObjs));

	SpatialComponent* spatial = new SpatialComponent;
	entities[pastNumObjs].AddComponent(spatial, "SpatialComponent","SpatialComponent");
	saveLogger->AddComponentData(pastNumObjs,"SpatialComponent",spatial->GetDisplayData());

	entitieMeshs[pastNumObjs] = new MeshComponent;
	entities[pastNumObjs].AddComponent(entitieMeshs[pastNumObjs], "MeshComponent");
	saveLogger->SetComponent(pastNumObjs, 1, entitieMeshs[pastNumObjs]);
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
					{
						saveLogger->AddComponentData(i, components[iComponent]->GetName(), displayData);
					}
					components[iComponent]->SetSaved(true);
				}
			}
		}
	}
}

void EntityManager::RemoveEntity(int EntityToRemove)
{
	if (currentlySelectedObject == EntityToRemove)
	{
		for (int i = 0; i < num_Objs; ++i)
		{
			if (i != EntityToRemove)
			{
				SetCurrentlySelectedObject(i);
				break;
			}
		}
	}
	entities[EntityToRemove].Disable();
	RenderEngine::RemoveRenderInfo(&entitieMeshs[EntityToRemove]->renderinfo);
	for (int jNumComponents = 0; jNumComponents < numComponent[EntityToRemove]; ++jNumComponents)
	{
		delete entitieComponents[EntityToRemove][jNumComponents];
	}
	for (int iCurEntity = EntityToRemove; iCurEntity < num_Objs - 1; ++iCurEntity)
	{
		entities[iCurEntity] = entities[iCurEntity+1];
		entitieMeshs[iCurEntity] = entitieMeshs[iCurEntity + 1];
		int biggerNumComponents = (numComponent[iCurEntity + 1] > numComponent[iCurEntity]) ? numComponent[iCurEntity + 1] : numComponent[iCurEntity];
		for (int jNumComponents = 0; jNumComponents < biggerNumComponents; ++jNumComponents)
		{
			entitieComponents[iCurEntity][jNumComponents] = entitieComponents[iCurEntity + 1][jNumComponents];
		}
		numComponent[iCurEntity] = numComponent[iCurEntity + 1];
	}
	num_Objs--;
	entities[num_Objs] = Imgn::Entity();
	entitieMeshs[num_Objs] = 0; 
	if(entitieComponents[num_Objs])
		memset(entitieComponents[num_Objs], 0, sizeof(entitieComponents[num_Objs]));
	numComponent[num_Objs] = 0;
	objController->SetMeshs(num_Objs, entitieMeshs);
	saveLogger->RemoveEntity(EntityToRemove);
}

void EntityManager::Update(float dt, bool isPlaying)
{
	TransformInfo::WorldToViewMatrix = playerCamera->getWorldToViewMatrix();
	
	player.Update(dt);

	if (isPlaying)
	{
		std::string obj = "Cue_Stick";
		for (int i = 0; i < num_Objs; i++)
		{
			entities[i].Update(dt);
			bool trail = true;
			for (int j = 0; j < obj.length(); j++)
			{
				if (entities[i].GetName()[j] != obj[j])
				{
					trail = false;
					break;
				}

			}
			if (trail)
			{
				SpatialComponent* spatial = entities[i].GetComponentByType<SpatialComponent>();
				playerSpatial->SetPosition(spatial->GetPosition() + glm::vec3(0,5,0));
				playerSpatial->UpdatePosition();
			}
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
	objController->SendDataToOpenGl();
	//objectTransformer.SendDataToOpenGl();
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
#include "MovementComponent.h"
#include "Physics/RigidBody.h"
#include "CollisionDetection/SphereCollider.h"

ImgnComponent ** EntityManager::GetComponents(int objNum)
{
	ImgnComponent** components;
	string name = saveLogger->GetName(objNum);
	int numComponents = 1;
	Imgn::DisplayData* displayData;
	int iVar = 0;

	if (name == "Cue_Ball")
	{																		
		components = new ImgnComponent*[3];
		components[numComponents] = new Imgn::RigidBody();
		displayData = components[numComponents]->GetDisplayData();
		if (displayData)
		{
			iVar = 0; bool* val0 = reinterpret_cast<bool*>(displayData->values[iVar]); *val0 = (bool)1;
			iVar = 1; double* val1 = reinterpret_cast<double*>(displayData->values[iVar]); *val1 = (double)1.000000;
			iVar = 2; float* val2 = reinterpret_cast<float*>(displayData->values[iVar]); *val2 = (float)0.700000;
			iVar = 3; float* val3 = reinterpret_cast<float*>(displayData->values[iVar]); *val3 = (float)0.050000;
			iVar = 4; glm::detail::tvec3<float>* val4 = reinterpret_cast<glm::detail::tvec3<float>*>(displayData->values[iVar]); *val4 = glm::vec3(0.000000,-9.800000,0.000000);
			iVar = 5; bool* val5 = reinterpret_cast<bool*>(displayData->values[iVar]); *val5 = (bool)1;
			iVar = 6; bool* val6 = reinterpret_cast<bool*>(displayData->values[iVar]); *val6 = (bool)0;
		}
		numComponents++;
		components[numComponents] = new SphereCollider();
		displayData = components[numComponents]->GetDisplayData();
		if (displayData)
		{
		}
		numComponents++;
	}
	if (name == "Ball_1")
	{																		
		components = new ImgnComponent*[3];
		components[numComponents] = new Imgn::RigidBody();
		displayData = components[numComponents]->GetDisplayData();
		if (displayData)
		{
			iVar = 0; bool* val0 = reinterpret_cast<bool*>(displayData->values[iVar]); *val0 = (bool)1;
			iVar = 1; double* val1 = reinterpret_cast<double*>(displayData->values[iVar]); *val1 = (double)1.000000;
			iVar = 2; float* val2 = reinterpret_cast<float*>(displayData->values[iVar]); *val2 = (float)0.700000;
			iVar = 3; float* val3 = reinterpret_cast<float*>(displayData->values[iVar]); *val3 = (float)0.050000;
			iVar = 4; glm::detail::tvec3<float>* val4 = reinterpret_cast<glm::detail::tvec3<float>*>(displayData->values[iVar]); *val4 = glm::vec3(0.000000,-9.800000,0.000000);
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
			iVar = 2; float* val2 = reinterpret_cast<float*>(displayData->values[iVar]); *val2 = (float)2.000000;
		}
		numComponents++;
	}
	if (name == "Ball_2")
	{																		
		components = new ImgnComponent*[3];
		components[numComponents] = new Imgn::RigidBody();
		displayData = components[numComponents]->GetDisplayData();
		if (displayData)
		{
			iVar = 0; bool* val0 = reinterpret_cast<bool*>(displayData->values[iVar]); *val0 = (bool)1;
			iVar = 1; double* val1 = reinterpret_cast<double*>(displayData->values[iVar]); *val1 = (double)1.000000;
			iVar = 2; float* val2 = reinterpret_cast<float*>(displayData->values[iVar]); *val2 = (float)0.700000;
			iVar = 3; float* val3 = reinterpret_cast<float*>(displayData->values[iVar]); *val3 = (float)0.050000;
			iVar = 4; glm::detail::tvec3<float>* val4 = reinterpret_cast<glm::detail::tvec3<float>*>(displayData->values[iVar]); *val4 = glm::vec3(0.000000,-9.800000,0.000000);
			iVar = 5; bool* val5 = reinterpret_cast<bool*>(displayData->values[iVar]); *val5 = (bool)1;
			iVar = 6; bool* val6 = reinterpret_cast<bool*>(displayData->values[iVar]); *val6 = (bool)0;
		}
		numComponents++;
		components[numComponents] = new SphereCollider();
		displayData = components[numComponents]->GetDisplayData();
		if (displayData)
		{
		}
		numComponents++;
	}
	if (name == "Cue_Stick")
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
			iVar = 4; glm::detail::tvec3<float>* val4 = reinterpret_cast<glm::detail::tvec3<float>*>(displayData->values[iVar]); *val4 = glm::vec3(0.000000,-9.800000,0.000000);
			iVar = 5; bool* val5 = reinterpret_cast<bool*>(displayData->values[iVar]); *val5 = (bool)0;
			iVar = 6; bool* val6 = reinterpret_cast<bool*>(displayData->values[iVar]); *val6 = (bool)0;
		}
		numComponents++;
		components[numComponents] = new BoxCollider();
		displayData = components[numComponents]->GetDisplayData();
		if (displayData)
		{
			iVar = 0; bool* val0 = reinterpret_cast<bool*>(displayData->values[iVar]); *val0 = (bool)1;
			iVar = 1; glm::detail::tvec3<float>* val1 = reinterpret_cast<glm::detail::tvec3<float>*>(displayData->values[iVar]); *val1 = glm::vec3(0.000000,-0.400000,0.000000);
			iVar = 2; glm::detail::tvec3<float>* val2 = reinterpret_cast<glm::detail::tvec3<float>*>(displayData->values[iVar]); *val2 = glm::vec3(0.600000,0.600000,66.199997);
			iVar = 3; bool* val3 = reinterpret_cast<bool*>(displayData->values[iVar]); *val3 = (bool)0;
		}
		numComponents++;
		components[numComponents] = new MovementComponent();
		displayData = components[numComponents]->GetDisplayData();
		if (displayData)
		{
			iVar = 0; float* val0 = reinterpret_cast<float*>(displayData->values[iVar]); *val0 = (float)100.000000;
		}
		numComponents++;
	}
	if (name == "Ball_3")
	{																		
		components = new ImgnComponent*[3];
		components[numComponents] = new Imgn::RigidBody();
		displayData = components[numComponents]->GetDisplayData();
		if (displayData)
		{
			iVar = 0; bool* val0 = reinterpret_cast<bool*>(displayData->values[iVar]); *val0 = (bool)1;
			iVar = 1; double* val1 = reinterpret_cast<double*>(displayData->values[iVar]); *val1 = (double)1.000000;
			iVar = 2; float* val2 = reinterpret_cast<float*>(displayData->values[iVar]); *val2 = (float)0.700000;
			iVar = 3; float* val3 = reinterpret_cast<float*>(displayData->values[iVar]); *val3 = (float)1.000000;
			iVar = 4; glm::detail::tvec3<float>* val4 = reinterpret_cast<glm::detail::tvec3<float>*>(displayData->values[iVar]); *val4 = glm::vec3(0.000000,-9.800000,0.000000);
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
	if (name == "Ball_4")
	{																		
		components = new ImgnComponent*[3];
		components[numComponents] = new Imgn::RigidBody();
		displayData = components[numComponents]->GetDisplayData();
		if (displayData)
		{
			iVar = 0; bool* val0 = reinterpret_cast<bool*>(displayData->values[iVar]); *val0 = (bool)1;
			iVar = 1; double* val1 = reinterpret_cast<double*>(displayData->values[iVar]); *val1 = (double)1.000000;
			iVar = 2; float* val2 = reinterpret_cast<float*>(displayData->values[iVar]); *val2 = (float)0.700000;
			iVar = 3; float* val3 = reinterpret_cast<float*>(displayData->values[iVar]); *val3 = (float)0.050000;
			iVar = 4; glm::detail::tvec3<float>* val4 = reinterpret_cast<glm::detail::tvec3<float>*>(displayData->values[iVar]); *val4 = glm::vec3(0.000000,-9.800000,0.000000);
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
	if (name == "Pool_Table_Collider")
	{																		
		components = new ImgnComponent*[3];
		components[numComponents] = new Imgn::RigidBody();
		displayData = components[numComponents]->GetDisplayData();
		if (displayData)
		{
			iVar = 0; bool* val0 = reinterpret_cast<bool*>(displayData->values[iVar]); *val0 = (bool)1;
			iVar = 1; double* val1 = reinterpret_cast<double*>(displayData->values[iVar]); *val1 = (double)1.000000;
			iVar = 2; float* val2 = reinterpret_cast<float*>(displayData->values[iVar]); *val2 = (float)0.050000;
			iVar = 3; float* val3 = reinterpret_cast<float*>(displayData->values[iVar]); *val3 = (float)0.050000;
			iVar = 4; glm::detail::tvec3<float>* val4 = reinterpret_cast<glm::detail::tvec3<float>*>(displayData->values[iVar]); *val4 = glm::vec3(0.000000,-9.800000,0.000000);
			iVar = 5; bool* val5 = reinterpret_cast<bool*>(displayData->values[iVar]); *val5 = (bool)0;
			iVar = 6; bool* val6 = reinterpret_cast<bool*>(displayData->values[iVar]); *val6 = (bool)0;
		}
		numComponents++;
		components[numComponents] = new BoxCollider();
		displayData = components[numComponents]->GetDisplayData();
		if (displayData)
		{
			iVar = 0; bool* val0 = reinterpret_cast<bool*>(displayData->values[iVar]); *val0 = (bool)0;
			iVar = 1; glm::detail::tvec3<float>* val1 = reinterpret_cast<glm::detail::tvec3<float>*>(displayData->values[iVar]); *val1 = glm::vec3(0.000000,2.000000,0.000000);
			iVar = 2; glm::detail::tvec3<float>* val2 = reinterpret_cast<glm::detail::tvec3<float>*>(displayData->values[iVar]); *val2 = glm::vec3(45.000000,2.000000,2.000000);
			iVar = 3; bool* val3 = reinterpret_cast<bool*>(displayData->values[iVar]); *val3 = (bool)0;
		}
		numComponents++;
	}
	if (name == "Pool_Table_Collider_2")
	{																		
		components = new ImgnComponent*[3];
		components[numComponents] = new Imgn::RigidBody();
		displayData = components[numComponents]->GetDisplayData();
		if (displayData)
		{
			iVar = 0; bool* val0 = reinterpret_cast<bool*>(displayData->values[iVar]); *val0 = (bool)0;
			iVar = 1; double* val1 = reinterpret_cast<double*>(displayData->values[iVar]); *val1 = (double)1.000000;
			iVar = 2; float* val2 = reinterpret_cast<float*>(displayData->values[iVar]); *val2 = (float)0.050000;
			iVar = 3; float* val3 = reinterpret_cast<float*>(displayData->values[iVar]); *val3 = (float)0.050000;
			iVar = 4; glm::detail::tvec3<float>* val4 = reinterpret_cast<glm::detail::tvec3<float>*>(displayData->values[iVar]); *val4 = glm::vec3(0.000000,-9.800000,0.000000);
			iVar = 5; bool* val5 = reinterpret_cast<bool*>(displayData->values[iVar]); *val5 = (bool)0;
			iVar = 6; bool* val6 = reinterpret_cast<bool*>(displayData->values[iVar]); *val6 = (bool)0;
		}
		numComponents++;
		components[numComponents] = new BoxCollider();
		displayData = components[numComponents]->GetDisplayData();
		if (displayData)
		{
			iVar = 0; bool* val0 = reinterpret_cast<bool*>(displayData->values[iVar]); *val0 = (bool)0;
			iVar = 1; glm::detail::tvec3<float>* val1 = reinterpret_cast<glm::detail::tvec3<float>*>(displayData->values[iVar]); *val1 = glm::vec3(0.000000,2.000000,0.000000);
			iVar = 2; glm::detail::tvec3<float>* val2 = reinterpret_cast<glm::detail::tvec3<float>*>(displayData->values[iVar]); *val2 = glm::vec3(45.000000,2.000000,2.000000);
			iVar = 3; bool* val3 = reinterpret_cast<bool*>(displayData->values[iVar]); *val3 = (bool)0;
		}
		numComponents++;
	}

	if(numComponents == 1){ components = new ImgnComponent*[1]; }
	numComponent[objNum] += numComponents;
	return components;
}
