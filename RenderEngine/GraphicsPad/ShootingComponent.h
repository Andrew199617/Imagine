#pragma once
#include "ImgnComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#pragma warning (disable:4458)
#include <glm.hpp>
#pragma warning(pop)

class ShootingComponent :
	public ImgnComponent
{
public:
	ShootingComponent();
	~ShootingComponent();

	virtual bool Initialize() override;
	virtual void Update(float dt) override;
	bool arrowHasntBeenShot;

	glm::vec3 viewDirection;

};

