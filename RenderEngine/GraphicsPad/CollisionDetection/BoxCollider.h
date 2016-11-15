#pragma once
#include "ImgnCollider.h"

class BoxCollider : public ImgnCollider
{
	IMGN_GENERATE(BoxCollider)
	IMGN_PROPERTY(isTrigger, false)
	IMGN_PROPERTY(center, glm::vec3())
	IMGN_PROPERTY(size,glm::vec3(1,1,1))
	IMGN_END(BoxCollider)
private:
	bool Initialize() override;
	void Update(float) override;
	void Draw(float) override;

protected:
	void OnValueChange(std::string VariableName) override;	
	
	glm::vec3 GetHalfSize() { return size / 2.0f; }

};

