#pragma once
#include "../Component.h"
#include "../StateMachine\State.h"
#include "../Entity.h"
class StateComponent :
	public Component
{
private:
	State* m_pCurrentState;
	State* m_pPreviousState;
	State* m_pGlobalState;

private:
	Entity* m_owner;

public:
	StateComponent();
	~StateComponent();

	bool Initialize() override;
	bool Update(float dt) override;
	void ChangeState(State* pNewState);
	void RevertToPreviousState() { ChangeState(m_pPreviousState); }
	bool isInState(const State* st) const;

public:
	void SetCurrentState(State* s) { m_pCurrentState = s; m_pCurrentState->Enter(this, m_owner);}
	void SetGlobalState(State* s) { m_pGlobalState = s; }
	void SetPreviousState(State* s) { m_pPreviousState = s; }
	State* CurrentState() const { return m_pCurrentState; }
	State* GlobalState() const { return m_pGlobalState; }
	State* PreviousState() const { return m_pPreviousState; }
};

