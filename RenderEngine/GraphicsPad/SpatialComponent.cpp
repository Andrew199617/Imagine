#include "SpatialComponent.h"
#include "ConfigReader.h"


SpatialComponent::SpatialComponent() :
	UP(0.0f, 1.0f, 0.0f) , velocity(0.0f,0.0f,0.0f)
{
	//ConfigReader::Initialize();
	//position = ConfigReader::findVec3ForKey("CameraPosition");
}


SpatialComponent::~SpatialComponent()
{
}
