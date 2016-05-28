#pragma once
#include "../Entity.h"
#include <string.h>

class StateComponent;

class State
{
protected:
	string m_name;

public:
	State() {}
	virtual ~State() {}
	virtual void Enter(StateComponent*,Entity*) = 0;
	virtual void Execute(StateComponent*,Entity*,float) = 0;
	virtual void Exit(StateComponent*,Entity*) = 0;

public:
	string Name() { return m_name; }
};

