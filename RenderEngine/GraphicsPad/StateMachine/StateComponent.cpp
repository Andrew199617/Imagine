#include "StateComponent.h"
#include "../GameLogger.h"
#include "../Entity.h"

using std::cout;
using std::endl;

StateComponent::StateComponent() :
	m_pCurrentState(NULL),
	m_pPreviousState(NULL),
	m_pGlobalState(NULL)
{
}


StateComponent::~StateComponent()
{
}

bool StateComponent::Initialize()
{
	if(this->GetOwner()) m_owner = this->GetOwner();
	else
	{
		string s = ": Owner was not initialized";
		GameLogger::log(this->GetName() + s);
		return false;
	}
	return true;
}

bool StateComponent::Update(float dt)
{
	if (m_pGlobalState) m_pGlobalState->Execute(this,m_owner,dt);
	if (m_pCurrentState) m_pCurrentState->Execute(this,m_owner,dt);
	return true;
}

void StateComponent::ChangeState(State * pNewState)
{
	if (!m_pCurrentState)
	{
		string s = " : Current state is not good";
		GameLogger::log(this->GetName() + s);
		cout << "check log" << endl;
		return;
	}
	if (!pNewState)
	{
		string s = " : New state is not good";
		GameLogger::log(this->GetName() + s);
		cout << "check log" << endl;
		return;
	}
	
	m_pPreviousState = m_pCurrentState;
	m_pCurrentState->Exit(this,m_owner);
	string s = "Changing state from " + m_pCurrentState->Name() + " to " + pNewState->Name();
	GameLogger::log(s);
	m_pCurrentState = pNewState;
	pNewState->Enter(this,m_owner);

}

bool StateComponent::isInState(const State* st) const
{
	return st == m_pCurrentState;
}
