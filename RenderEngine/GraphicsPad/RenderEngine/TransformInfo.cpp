#include "TransformInfo.h"
#include "gtc\matrix_transform.hpp"
#include "gtx\transform.hpp"

glm::mat4 TransformInfo::projectionMatrix = glm::mat4();
glm::mat4 TransformInfo::WorldToViewMatrix = glm::mat4();

TransformInfo::TransformInfo(glm::vec3 m_translateTransform, glm::vec3 m_scaleTransform, float angle,
	glm::vec3 m_rotateTransform)
{
	this->m_translateTransform = glm::translate(m_translateTransform);
	this->m_scaleTransform = glm::scale(m_scaleTransform);
	this->m_rotateTransform = glm::rotate(angle, m_rotateTransform);
	this->angle = angle;
}

TransformInfo::TransformInfo(glm::vec3 m_translateTransform, glm::vec3 m_scaleTransform, glm::quat rotation)
{
	this->m_translateTransform = glm::translate(m_translateTransform);
	this->m_scaleTransform = glm::scale(m_scaleTransform);
	this->m_rotateTransform = glm::mat4_cast(rotation);
}

TransformInfo::~TransformInfo()
{

}

