#pragma once
#include "ImgnCollider.h"

class SphereCollider : public ImgnCollider
{
	IMGN_GENERATE(SphereCollider)
	IMGN_PROPERTY(isTrigger,false)
	IMGN_PROPERTY(center, glm::vec3())
	IMGN_PROPERTY(radius, 1.0f)
	IMGN_END(SphereCollider)
public:
	virtual void Update(float) override;

private:
	float radius;

};
