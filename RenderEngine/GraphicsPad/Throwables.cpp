#include "Throwables.h"
#include "RenderEngine\RenderEngine.h"

WeaponEntity Throwables::Arrow = WeaponEntity();
//MovementComponent* Throwables::ArrowMove = new MovementComponent();
//SpatialComponent* Throwables::ArrowSpatial = new SpatialComponent();
//MeshComponent* Throwables::ArrowMesh = new MeshComponent();
//GravityComponent* Throwables::ArrowGravity = new GravityComponent();
//
//bool Throwables::Initialize()
//{
//	Arrow.SetName("Arrow");
//	Arrow.AddComponent(ArrowMove, "ArrowMovement");
//	Arrow.AddComponent(ArrowSpatial, "ArrowSpatial");
//	Arrow.AddComponent(ArrowMesh, "ArrowMesh");
//	Arrow.AddComponent(ArrowGravity, "ArrowGravity");
//	if(!Arrow.Initialize())
//	{
//		string s = ": did not initialize";
//		GameLogger::log(Arrow.GetName() + s);
//		return false;
//	}
//	return true;
//}

void Throwables::Update(float dt)
{
	Arrow.Update(dt);
}

void Throwables::sendDataToOpenGL()
{
	//ArrowMesh->setRenderInfo("Arrow");
	//RenderEngine::AddRenderInfo(&ArrowMesh->renderinfo);
	
}
