#pragma once
#include "Entity.h"
#include "ImgnFwd.hpp"
#include "SpatialComponent.h"
#include "ObjTransformerEntity.h"
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

	int CurrentlySelectedObject() const { return currentlySelectedObject; }
	void SetCurrentlySelectedObject(int ObjSelected);
public:
	bool Initialize();
	bool InitializeSaveLoggerObjects();
	void AddEntity();
	bool UpdateSaveLoggerObjects();

public:
	void SaveEntities();

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

	Imgn::Entity entities[MAX_OBJS];
	MeshComponent* entitieMeshs[MAX_OBJS];
	ImgnComponent** entitieComponents[MAX_OBJS];
	int numComponent[MAX_OBJS];

private:
	int currentlySelectedObject;

private:
	/************************************************************************/
	/* 	Used to load saved components;                                      
	/************************************************************************/
	ImgnComponent** GetComponents(int objNum);
	SaveLogger* saveLogger;

	Imgn::Entity player;
	CameraComponent* playerCamera;
	KeyboardComponent* playerKeyboard;
	MovementComponent* playerMove;
	MouseComponent* playerMouse;
	SpatialComponent* playerSpatial;
	ObjectSelectorComponent* objController;

	ObjTransformerEntity objectTransformer;

};

