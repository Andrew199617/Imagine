#pragma once
#include "Entity.h"
class Component
{
	enum
	{
		MAX_NAME_LEN = 35
	};

public:
	Component();
	~Component();

	bool Init();
	virtual bool Initialize() { return true; }
	virtual bool Update(float dt) { dt; return true; }
	virtual bool Draw() { return true; }
	void Enable(bool enabled = true) { m_enabled = enabled; }
	void Disable(bool enabled = false) { m_enabled = enabled; }
	bool isEnabled() const { return m_enabled; }
	bool IsDisabled() const { return !m_enabled; }
	void SetName(const char* const name);
	void SetName(string name);
	const char * const GetName() { return m_name; }
	void SetOwner(Entity* owner) { m_owner = owner; }
	Entity* GetOwner() { return m_owner; }

public:
	static void SetBreak(bool enabled = true);
	static void ToggleBreak() { s_breakable = !s_breakable; }
	static void Break(bool condition = true, bool keepBreakable = true);
	static void BreakIf(bool condition = true);

protected:
	template <class T> T* GetSiblingComponent() 
	{ 
		//assert(m_owner); 
		return m_owner->GetComponentByType<T>();
	}
	

private:
	Entity* m_owner;
	char	m_name[MAX_NAME_LEN];
	bool	m_enabled;

private:
	static bool s_breakable;
};

