#pragma once
#include "CameraComponent.h"
#include "KeyboardComponent.h"
#include "MeshComponent.h"
#include "SpatialComponent.h"
#include "MouseComponent.h"
#include "GravityComponent.h"
#include "PlayerEntity.h"
#include "SceneryEntity.h"
#include "RenderEngine\TransformInfo.h"
#include "RenderEngine\RenderEngine.h"
#include "NodeMap.h"
#include <Windows.h>
#pragma warning(push)
#pragma warning (disable:4127)
#include <QtGui\qkeyevent>
#pragma warning(pop)
#include "SeekBehaviorComponent.h"
#include "FleeBehaviorComponent.h"
#include "MoveComponent.h"
#include "WanderingComponent.h"
#include "PursuitComponent.h"
#include "EvasionComponent.h"
#include "FlockingComponent.h"
#include "ArrivalComponent.h"
#include "MovementComponent.h"
#include "StateMachine\StateComponent.h"
#include "AIEntity.h"
#include "PathFollowerComponent.h"
#include "ShootingComponent.h"
#include "Throwables.h"
#include "NoiseGenerator.h"
#include "ObjectSelectorComponent.h"
#define MAX_OBJS 500

namespace
{
	PlayerEntity player;
	CameraComponent playerCamera;
	KeyboardComponent playerKeyboard;
	MovementComponent playerMove;
	MouseComponent playerMouse;
	SpatialComponent playerSpatial;
	GravityComponent playerGravity;
	ShootingComponent playerShoot;
	ObjectSelectorComponent objController;

}


class EntityManager
{
public:
	EntityManager();
	~EntityManager();

public:
	bool Initialize();
	bool InitializeSaveLoggerObjects();
	bool UpdateSaveLoggerObjects();

public:
	inline void UpdateObjectPosition(int obj, glm::vec3 Position) { entitieSpatials[obj].SetPosition(Position); }
	inline void UpdateObjectRotate(int obj, glm::vec3 Rotation) { entitieSpatials[obj].SetRotate(Rotation); }
	inline void UpdateObjectScale(int obj, glm::vec3 Scale) { entitieSpatials[obj].SetScale(Scale); }

public:
	void Update(float dt);
	void ProcessKeys(float m_dt);
	void ProcessMouseMove(QMouseEvent* e);
	void ProcessMousePress(QMouseEvent* e);

public:
	void SendDataToOpenGL();
	void SendNewDataToOpenGL();

public:
	NoiseGenerator noiseGenerator;
	NodeMap nodeMap[4];

	int num_Objs;

	SceneryEntity entities[MAX_OBJS];
	SpatialComponent entitieSpatials[MAX_OBJS];
	MeshComponent entitieMeshs[MAX_OBJS];
	int currentlySelectedObject;
};

