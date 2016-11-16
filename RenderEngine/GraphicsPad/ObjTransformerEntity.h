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

	void SetSpatial(SpatialComponent* spatial);
	void SetPosition(glm::vec3 val);
	void SetScale(glm::vec3 val);
private:
	glm::vec3 scale;
	glm::vec3 position;
	MouseComponent* objectTransformerMouse;
	MeshComponent* xMesh;
	MeshComponent* yMesh;
	MeshComponent* zMesh;
};

