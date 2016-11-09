#pragma once
#include "../ImgnComponent.h"
#include "../ImgnProperties.h"
#include "glm.hpp"
#include <vector>
class RenderInfo;

class ImgnCollider : public ImgnComponent
{
	
public:
	ImgnCollider() : size(glm::vec3()), center(glm::vec3()), isTrigger(0), renderInfo(0) {}
	~ImgnCollider() {}
protected:
	bool isTrigger;
	glm::vec3 center;
	glm::vec3 size;

	RenderInfo* renderInfo;
	Imgn::CollisionData* collisionData;

protected:
	void DisplayCollider(std::string objName);
	void Awake() override;

public:
	void focusOutEvent(QFocusEvent *) override;
	void focusInEvent(QFocusEvent *) override;
};

