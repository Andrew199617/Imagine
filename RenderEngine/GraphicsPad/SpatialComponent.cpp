#include "SpatialComponent.h"
#include "ConfigReader.h"
#include "gtc\matrix_transform.hpp"
#include "gtx\transform.hpp"
#include "MeshComponent.h"
#include "Physics\PhysicsTypeDefs.hpp"


SpatialComponent::~SpatialComponent()
{

}

void SpatialComponent::UpdatePosition()
{
	SetTransformInfo();
	if(transformInfo)
		transformInfo->m_translateTransform = glm::translate(GetPosition());
}

void SpatialComponent::UpdateScale()
{
	SetTransformInfo();
	if (transformInfo)
		transformInfo->m_scaleTransform = glm::scale(GetScale());
}

void SpatialComponent::UpdateRotate()
{
	SetTransformInfo();
	glm::vec3 rotateInRadians = glm::vec3(rotation.x * R_PI / 180, rotation.y * R_PI / 180, rotation.z * R_PI / 180);
	SetRotate(glm::quat(rotateInRadians));
	if (transformInfo)
		transformInfo->m_rotateTransform = glm::mat4_cast(GetRotate());
}

void SpatialComponent::SetTransformInfo()
{
	MeshComponent* mesh = GetSiblingComponent<MeshComponent>();
	if (mesh)
	{
		transformInfo = mesh->renderinfo.getTransformInfo();
	}
}

void SpatialComponent::SetPosition(glm::vec3 val)
{
	position = val;
}

void SpatialComponent::SetRotation(glm::vec3 val)
{
	if (val.x > 360)
	{
		val.x = val.x - 360;
	}
	rotation = val;
}

void SpatialComponent::SetRotate(glm::quat val)
{
	rotate = val;
	SetTransformInfo();
	rotation = glm::eulerAngles(rotate);
	transformInfo->m_rotateTransform = glm::mat4_cast(rotate);
}

void SpatialComponent::Awake() 
{
	rotate = glm::quat();
	transformInfo = 0;
}

void SpatialComponent::OnValueChange(std::string VariableName)
{
	if (VariableName == "Position")
	{
		UpdatePosition();
	}
	if (VariableName == "Scale")
	{
		UpdateScale();
	}
	if (VariableName == "Rotation")
	{
		UpdateRotate();
	}
}