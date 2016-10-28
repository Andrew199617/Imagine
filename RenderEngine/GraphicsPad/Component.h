#pragma once
#include "EntityData.h"
#include <string>

using std::string;

class Component
{

public:
	Component();
	virtual ~Component();

	virtual bool Initialize() { return true; }
	virtual bool Update(float dt) { dt; return true; }
	virtual bool Draw() { return true; }
	void Enable(bool enabled = true) { m_enabled = enabled; }
	void Disable(bool enabled = false) { m_enabled = enabled; }
	bool IsEnabled() const { return m_enabled; }
	bool IsDisabled() const { return !m_enabled; }
	bool IsSaved() const { return saved; }
	void SetSaved(bool val) { saved = val; SetSaved_Implentation(val); }
	void SetName(const char* const name);
	void SetName(string name);
	const char * const GetName() { return m_name; }
	

public:
	static void SetBreak(bool enabled = true);
	static void ToggleBreak() { s_breakable = !s_breakable; }
	static void Break(bool condition = true, bool keepBreakable = true);
	static void BreakIf(bool condition = true);

protected:
	virtual void SetSaved_Implentation(bool) = 0;

protected:
	char	m_name[Imgn::MAX_NAME_LEN];
	bool	m_enabled;

private:
	static bool s_breakable;
	bool saved;
};

