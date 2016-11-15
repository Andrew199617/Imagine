#pragma once
#include "Entity.h"
#include "ImgnFwd.hpp"
#include "glm.hpp"

class ObjTransformerEntity : public Imgn::Entity
{
public:
	ObjTransformerEntity();
	~ObjTransformerEntity();

	virtual bool Initialize() override;
	void SendDataToOpenGl();

private:
	glm::vec3 scale;
	glm::vec3 position;
	MouseComponent* objectTransformerMouse;
	MeshComponent* xMesh;
	MeshComponent* yMesh;
	MeshComponent* zMesh;
};

