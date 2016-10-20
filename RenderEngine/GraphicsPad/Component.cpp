#include "Component.h"
#include "GameLogger.h"

bool Component::s_breakable = false;

Component::Component()
{
}


Component::~Component()
{
}

bool Component::Init()
{
	m_enabled = true;
	bool result = Initialize();
	if (!result)
	{
		string s = ": failed to initialize";
		GameLogger::log(this->GetName() + s);
	}
	return result;
}

void Component::SetName(const char * const name)
{
	for (int i = 0; i < Imgn::MAX_NAME_LEN; ++i)
	{
		m_name[i] = name[i];
		if (!name[i]) return;
	}
	m_name[Imgn::MAX_NAME_LEN - 1] = 0;
}

void Component::SetName(string name)
{
	const char* c = name.c_str();
	for (int i = 0; i < Imgn::MAX_NAME_LEN; ++i)
	{
		m_name[i] = c[i];
		if (!c[i]) return;
	}
	m_name[Imgn::MAX_NAME_LEN - 1] = 0;
}

void Component::SetBreak(bool enabled)
{
	s_breakable = enabled;
}

void Component::Break(bool condition, bool keepBreakable)
{
	if (condition && s_breakable)
	{
		__debugbreak();
		s_breakable = keepBreakable;
	}
}

void Component::BreakIf(bool condition)
{
	if (condition)
	{
		__debugbreak();
	}
}
