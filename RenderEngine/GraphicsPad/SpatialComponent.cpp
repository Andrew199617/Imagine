#include "SpatialComponent.h"
#include "ConfigReader.h"
#include "gtc\matrix_transform.hpp"
#include "gtx\transform.hpp"
#include "MeshComponent.h"

SpatialComponent::SpatialComponent() :
	UP(0.0f, 1.0f, 0.0f) , velocity(0.0f,0.0f,0.0f)
{
	transformInfo = 0;
	position = glm::vec3(0, 0, 0);
	rotate = glm::vec3(0, 1, 0);
	scale = glm::vec3(1, 1, 1);
}


SpatialComponent::~SpatialComponent()
{

}

void SpatialComponent::SetPosition(glm::vec3 Position)
{
	this->position = Position;
	if(!transformInfo)
		transformInfo = this->GetSiblingComponent<MeshComponent>()->renderinfo.getTransformInfo();
	transformInfo->m_translateTransform = glm::translate(position);
}

void SpatialComponent::SetScale(glm::vec3 Scale)
{
	this->scale = Scale;
	if (!transformInfo)
		transformInfo = this->GetSiblingComponent<MeshComponent>()->renderinfo.getTransformInfo();
	transformInfo->m_scaleTransform = glm::scale(scale);
}

void SpatialComponent::SetRotate(glm::vec3 Rotate)
{
	this->rotate = Rotate;
	if (!transformInfo)
		transformInfo = this->GetSiblingComponent<MeshComponent>()->renderinfo.getTransformInfo();
	transformInfo->m_rotateTransform = glm::rotate(transformInfo->angle,rotate);
}
