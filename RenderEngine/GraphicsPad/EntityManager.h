#pragma once
#include "Entity.h"
#include "SceneryEntity.h"
#include "ImgnFwd.hpp"
#include "SpatialComponent.h"
class NoiseGenerator;
class NodeMap;
class QMouseEvent;
class SaveLogger;
#define MAX_OBJS 500


class EntityManager
{
public:
	EntityManager();
	~EntityManager();

public:
	bool Initialize();
	bool InitializeSaveLoggerObjects();
	void AddEntity();
	bool UpdateSaveLoggerObjects();

public:
	void SaveEntities();
	void UpdateObjectPosition(int obj, glm::vec3 Position);
	void UpdateObjectRotate(int obj, glm::vec3 Rotation);
	void UpdateObjectScale(int obj, glm::vec3 Scale);

public:
	void Update(float dt, bool isPlaying);
	void ProcessKeys(float m_dt);
	void ProcessMouseMove(QMouseEvent* e);
	void ProcessMousePress(QMouseEvent* e);

public:
	void SendDataToOpenGL();
	void SendNewDataToOpenGL();

public:
	int num_Objs;

	SceneryEntity entities[MAX_OBJS];
	SpatialComponent* entitieSpatials[MAX_OBJS];
	MeshComponent* entitieMeshs[MAX_OBJS];
	ImgnComponent** entitieComponents[MAX_OBJS];
	int numComponent[MAX_OBJS];
	int currentlySelectedObject;

private:
	ImgnComponent** GetComponents(int objNum);
	SaveLogger* saveLogger;
	Imgn::Entity player;
	CameraComponent* playerCamera;
	KeyboardComponent* playerKeyboard;
	MovementComponent* playerMove;
	MouseComponent* playerMouse;
	SpatialComponent* playerSpatial;
	GravityComponent* playerGravity;
	ShootingComponent* playerShoot;
	ObjectSelectorComponent* objController;

};

