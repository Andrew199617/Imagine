#pragma once
#include "WeaponEntity.h"
#include "MovementComponent.h"
#include "MeshComponent.h"
#include "GravityComponent.h"

class Throwables
{
public:
	static WeaponEntity Arrow;
	/*static MovementComponent* ArrowMove;
	static SpatialComponent* ArrowSpatial;
	static MeshComponent* ArrowMesh;
	static GravityComponent* ArrowGravity;
	static bool Initialize();*/
	static void Update(float dt);
	static void sendDataToOpenGL();
};

