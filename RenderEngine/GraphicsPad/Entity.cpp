#include "Entity.h"
#include <string.h>
#include "Component.h"
#include "GameLogger.h"

Entity::Entity()
{
	memset(m_components, 0, MAX_COMPONENTS * sizeof(m_components[0]));
}


Entity::~Entity()
{
}

bool Entity::Update(float dt)
{
	for (int i = 0; i < MAX_COMPONENTS; i++)
	{
		if (m_components[i] && m_components[i]->isEnabled())
		{
			bool result = m_components[i]->Update(dt);
			if (!result)
			{
				string s = ": failed to update";
				GameLogger::log(m_components[i]->GetName() + s);
				GameLogger::shutdownLog();
				exit(1);
			}
		}
	}
	/*for (int i = 0; i < MAX_COMPONENTS; i++)
	{
		if (m_components[i] && m_components[i]->isEnabled())
		{
			bool result = m_components[i]->Draw();
			if (!result) GameLogger::log("Component " + to_string(i) + " failed to draw");
		}
	}*/
	return true;
}

void Entity::SetName(const char * const name)
{
	for (int i = 0; i < MAX_NAME_LEN; ++i)
	{
		m_name[i] = name[i];
		if (!name[i]) return;
	}
	m_name[MAX_NAME_LEN - 1] = 0;
}

void Entity::SetName(string s)
{
	const char* c = s.c_str();
	for (int i = 0; i < MAX_NAME_LEN; ++i)
	{
		m_name[i] = c[i];
		if (!c[i]) return;
	}
	m_name[MAX_NAME_LEN - 1] = 0;
}

const char * const Entity::GetName()
{
	return m_name;
}

bool Entity::AddComponent(Component * c, const char * const name)
{
	for (int i = 0; i < MAX_COMPONENTS; ++i)
	{
		if (!m_components[i])
		{
			m_components[i] = c;
			c->SetOwner(this);
			c->SetName(name);
			return true;
		}
	}
	string s = ": Could not be added";
	GameLogger::log(name + s);
	cout << "check log" << endl;
	return false;
}

bool Entity::AddComponent(Component * c, string name)
{
	for (int i = 0; i < MAX_COMPONENTS; ++i)
	{
		if (!m_components[i])
		{
			m_components[i] = c;
			c->SetOwner(this);
			c->SetName(name);
			return true;
		}
	}
	string s = ": Could not be added";
	GameLogger::log(name + s);
	cout << "check log" << endl;
	return false;
}

bool Entity::Initialize()
{
	for (int i = 0; i < MAX_COMPONENTS; ++i)
	{
		if (m_components[i])
		{
			if (!m_components[i]->Init())  return false;
		}
	}
	return true;
}
