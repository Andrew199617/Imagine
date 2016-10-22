#pragma once
#include "..\ImgnFwd.hpp"
#include <string>

class StateComponent;

class State
{
protected:
	std::string m_name;

public:
	State() {}
	virtual ~State() {}
	virtual void Enter(StateComponent*,Imgn::Entity*) = 0;
	virtual void Execute(StateComponent*, Imgn::Entity*,float) = 0;
	virtual void Exit(StateComponent*, Imgn::Entity*) = 0;

public:
	std::string Name() { return m_name; }
};

