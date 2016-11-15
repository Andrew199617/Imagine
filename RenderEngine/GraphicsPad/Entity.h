#pragma once
#include <typeinfo>
#include "GameLogger.h"
#include "EntityData.h"
class ImgnComponent;

namespace Imgn
{

	class Entity
	{

	public:
		Entity();
		~Entity();

		void Update(float dt);
		void SetName(const char * const name);
		void SetName(string s);
		const char * const GetName();
		bool AddComponent(ImgnComponent* c, const char * const name);
		bool AddComponent(ImgnComponent* c, string name, string componentName);
		bool AddComponent(void* c, string name);
		template <class T> T* GetComponentByType() const;
		void Disable();
		void Enable();

		virtual bool Initialize();
		void Collided(Entity* entity);

		inline ImgnComponent** GetComponents() { return m_components; }
		inline int GetNumComponents() { return numComponents; }
		bool alreadyAdded;
		bool IsSaved() const { return saved; }
		void SetSaved(bool val) { saved = val; }
	protected:
		int numComponents;

	private:
		ImgnComponent* m_components[Imgn::MAX_COMPONENTS_PERENTITY];
		char m_name[Imgn::MAX_NAME_LEN];
		bool saved;
	};

	template<class T>
	inline T * Entity::GetComponentByType() const
	{
		for (int i = 0; i < Imgn::MAX_COMPONENTS_PERENTITY; i++)
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
}
