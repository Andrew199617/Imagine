#include "GravityComponent.h"
#include "RenderEngine\RenderEngine.h"
#include "Throwables.h"

GravityComponent::GravityComponent()
{
}


GravityComponent::~GravityComponent()
{
}

void GravityComponent::fall(SpatialComponent* spatial,float dt)
{
	spatial->position.y -= GravitySpeed * dt;
}

CollisionInfo GravityComponent::SomethingIsBelow(SpatialComponent* spatial)
{
	
	vPositionTextureNormal* Verts = reinterpret_cast<vPositionTextureNormal*>(DansMesh->getGeometry()->vertices);
	int numVerts = DansMesh->getGeometry()->m_indexCount;
	glm::vec3 UP = spatial->UP;
	glm::vec3 Position = spatial->position;


	CollisionInfo info = CollisionInfo(FLT_MAX);

	for (int i = 0; i < numVerts; i += 3)
	{
		float tempMinT = CollisionTester::rayTriangleIntersect(Position, -UP, Verts[i].position, Verts[i+1].position, Verts[i+2].position, info.minT);
		if (tempMinT < info.minT)
		{
			info.minT = tempMinT;
			info.p0 = Verts[i].position;
			info.p1 = Verts[i+1].position;
			info.p2 = Verts[i+2].position;
		}
	}
	

	return info;
}

bool GravityComponent::Update(float dt)
{
	SpatialComponent* spatial = this->GetSiblingComponent<SpatialComponent>();
	if (!spatial)
	{
		string s = ": can not obtain a Component";
		GameLogger::log(this->GetName() + s);
		GameLogger::shutdownLog();
		return false;
	}
	CollisionInfo FloorCollision = CollisionInfo(FLT_MAX);
	//should check to see the scene output format and do a switch
	FloorCollision = SomethingIsBelow(spatial);

	if (FloorCollision.minT > DistanceFromGround && GetAsyncKeyState(Qt::Key::Key_R) == 0)
	{
		fall(spatial,dt);
	}
	else if (FloorCollision.minT < DistanceFromGround - .1 && GetAsyncKeyState(Qt::Key::Key_F) == 0)
	{
		if (FloorCollision.p1.x != 0 && FloorCollision.p1.y != 0 && FloorCollision.p1.z != 0)
			spatial->position.y = ((FloorCollision.p0.y + FloorCollision.p1.y + FloorCollision.p2.y) / 3) + DistanceFromGround;
	}
	return true;
}

bool GravityComponent::Initialize()
{

	DistanceFromGround = 4;
	GravitySpeed = 9.8f;
	return true;
}

