#include "Entity.h"
#include <string>
#include "ImgnComponent.h"
#include "GameLogger.h"
#include "SaveLogger.h"

using std::cout;
using std::endl;

namespace Imgn
{
	Entity::Entity()
	{
		memset(m_components, 0, MAX_COMPONENTS * sizeof(m_components[0]));
		numComponents = 0;
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
				m_components[i]->Update(dt);
			}
		}
		for (int i = 0; i < MAX_COMPONENTS; i++)
		{
			if (m_components[i] && m_components[i]->IsEnabled())
			{
				m_components[i]->Draw(dt);
			}
		}
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
		SetName(s.c_str());
	}

	const char * const Entity::GetName()
	{
		return m_name;
	}

	bool Entity::AddComponent(ImgnComponent * c, const char * const name)
	{
		for (int i = 0; i < MAX_COMPONENTS; ++i)
		{
			if (!m_components[i])
			{
				numComponents++;
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

	bool Entity::AddComponent(ImgnComponent * c, string name, string componentName)
	{
		bool added = AddComponent(c, name.c_str());
		if (added)
		{
			componentName.erase(std::remove_if(componentName.begin(), componentName.end(), isspace), componentName.end());
			SaveLogger::Instance()->AddComponent(m_name,componentName, c);
		}
		return added;
	}

	bool Entity::AddComponent(void * c, string name)
	{
		ImgnComponent* component = reinterpret_cast<ImgnComponent*>(c);
		bool added = AddComponent(component, name, name);
		if (added)
		{
			if (!component->Init())
			{
				string s = ": Could not be initialized;";
				GameLogger::log(name + s);
				cout << "check log" << endl;
				return false;
			}
		}
		return added;
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
}