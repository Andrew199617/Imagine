#pragma once
#include "ImgnProperties.h"
#include <glm.hpp>
#include "RenderEngine\TransformInfo.h"

class SpatialComponent : public ImgnComponent
{
	IMGN_GENERATE(SpatialComponent)
	IMGN_PROPERTY(position,glm::vec3(0, 0, 0))
	IMGN_PROPERTY(rotation, glm::vec3(0, 0, 0))
	IMGN_PROPERTY(scale, glm::vec3(0, 0, 0))
	IMGN_END(SpatialComponent)
public:
	void UpdatePosition();
	void UpdateScale();
	void UpdateRotate();

	void SetTransformInfo();


	glm::vec3 velocity;

	glm::vec3 GetPosition() const { return position; }
	void SetPosition(glm::vec3 val);
	glm::vec3 GetRotation() const { return rotation; }
	void SetRotation(glm::vec3 val);
	glm::vec3 GetScale() const { return scale; }
	void SetScale(glm::vec3 val) { scale = val; }
	glm::quat GetRotate() const { return rotate; }
	void SetRotate(glm::quat val);
private:
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;
	glm::quat rotate;
	TransformInfo* transformInfo;

protected:
	virtual void Awake() override;


	virtual void OnValueChange(std::string VariableName) override;

};

