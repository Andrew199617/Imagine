#pragma once
#include <typeinfo>
#include "GameLogger.h"

class Component;
class Entity
{
	enum
	{
		MAX_COMPONENTS = 10,
		MAX_NAME_LEN = 30
	};

public:
	Entity();
	~Entity();

	bool Update(float dt);
	void SetName(const char * const name);
	void SetName(string s);
	const char * const GetName();
	bool AddComponent(Component* c, const char * const name);
	bool AddComponent(Component* c, string name);
	template <class T> T* GetComponentByType() const;

	bool Initialize();
protected:
	

private:
	Component * m_components[MAX_COMPONENTS];
	char		m_name[MAX_NAME_LEN];
};

template<class T> 
inline T * Entity::GetComponentByType() const
{
	for (int i = 0; i < MAX_COMPONENTS; i++)
	{
		if (!m_components[i]) continue;
		if (typeid(T) == typeid(*m_components[i]))
		{
			//if (m_components[i]->IsDisabled()) return 0;
			return static_cast<T*>(m_components[i]);
		}
	}
	return 0;
}
