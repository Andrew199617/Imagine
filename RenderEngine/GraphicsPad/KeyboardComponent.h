#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm.hpp>
#pragma warning(pop)
#include "Component.h"
class KeyboardComponent :
	public Component
{
public:
	KeyboardComponent();
	~KeyboardComponent();

public:
	void ProcessKeys(float m_dt);
};

