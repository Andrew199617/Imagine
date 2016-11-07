#pragma once
#include "ImgnCollider.h"
class RenderInfo;

class BoxCollider : public ImgnCollider
{
	IMGN_GENERATE(BoxCollider)
	IMGN_PROPERTY(isTrigger, false)
	IMGN_PROPERTY(center, glm::vec3())
	IMGN_PROPERTY_DEFAULT(size)
	IMGN_END(BoxCollider)
private:
	bool Initialize() override;
	void Update(float) override;
	void Draw(float) override;
	void DrawBox();

	RenderInfo* renderInfo;
protected:
	void OnValueChange(std::string VariableName) override;	
	
public:
	void focusOutEvent(QFocusEvent *) override;
	void focusInEvent(QFocusEvent *) override;

	glm::vec3 GetHalfSize() { return size / 2.0f; }
private:
	glm::vec3 size;

};

