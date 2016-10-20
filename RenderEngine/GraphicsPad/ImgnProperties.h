#pragma once

#include "EntityData.h"
#include <string>
class ImgnComponent;

#define IMGN_END(className) isHidden = false;													\
	SetComponentType(temp->currentComponent);													\
	SetComponentTypeNum(temp->numSameComponent[temp->currentComponent]);						\
	layoutInitalized = false;																	\
	layoutHasData = false;																		\
	setMaximumSize(348, 250);																	\
	setMinimumSize(250, 50);																	\
	sizeHint().setHeight(50);																	\
	minimumSizeHint().setHeight(50);															\
	sizePolicy().setHorizontalPolicy(QSizePolicy::Policy::Expanding);								\
	sizePolicy().setVerticalPolicy(QSizePolicy::Policy::Minimum);								\
	m_owner = 0;																				\
}																								\
~##className();																							

#define IMGN_GENERATE(className) public:														\
className(){																					\
	Imgn::ImgnProperties* temp = Imgn::ImgnProperties::Instance();								\
	if(typeid(this) != typeid(ImgnComponent*) && dynamic_cast<ImgnComponent*>(this) == NULL)	\
	{																							\
		string s = ": does not inherit ImgnComponent. Invalid  IMGN_GENERATE";				\
		GameLogger::log(typeid(this).name() + s);												\
		GameLogger::shutdownLog();																\
		exit(1);																				\
	} 																							\
	temp->AddClass(this,typeid(this).name());													\
	Awake();
	
#pragma warning(push)
#pragma warning(disable:4005)
#define IMGN_PROPERTY(name) Imgn::ImgnProperties::Instance()->AddProperty<decltype(&name)>(&name,#name);
#define IMGN_PROPERTY(name, init_value) Imgn::ImgnProperties::Instance()->AddProperty<decltype(&name)>(&name,#name); name = init_value;
#pragma warning(pop)


namespace Imgn {

	struct DisplayData {
		const char** typeName;
		std::string* variableNames;
		void** values;
		int numValues;
		bool hasData;
	};

	class ImgnProperties {

		ImgnProperties() : numComponents(0), numValues(), numSameComponent(), currentComponent(0) {}
	public:

		static ImgnProperties* Instance()
		{
			if (!props)
				props = new ImgnProperties;
			return props;
		}

		template<class V> inline void AddProperty(V var, std::string name)
		{
			if (!isupper(name[0]))
			{
				name[0] = (char)toupper(name[0]);
			}
			for (unsigned i = 1; i < name.length(); i++)
			{
				if (isupper(name.at(i)))
				{
					name += ' ';
					for (unsigned j = name.length(); j > i; j--)
					{
						name[j] = name[j - 1];
					}
					name[i] = ' ';
					name += ' ';
					name[name.length() - 1] = '\0';
					i += 2;
				}
			}
			typeName[currentComponent][numSameComponent[currentComponent]][numValues[currentComponent][numSameComponent[currentComponent]]] = typeid(V).name();
			values[currentComponent][numSameComponent[currentComponent]][numValues[currentComponent][numSameComponent[currentComponent]]] = var;
			variableNames[currentComponent][numSameComponent[currentComponent]][numValues[currentComponent][numSameComponent[currentComponent]]] = name;
			numValues[currentComponent][numSameComponent[currentComponent]]++;
			
		}

		template<class T> DisplayData HasProperties(int componentType,int componentTypeNum)
		{
			DisplayData data;
			data.hasData = false;

			if (typeid(T) == typeid(components[componentType][componentTypeNum]))
			{
				if (numValues[componentType][componentTypeNum] > 0)
				{
					data.values = values[componentType][componentTypeNum];
					data.typeName = typeName[componentType][componentTypeNum];
					data.variableNames = variableNames[componentType][componentTypeNum];
					data.numValues = numValues[componentType][componentTypeNum];
					data.hasData = true;
				}
			}
			
			return data;
		}
		
		void AddClass(ImgnComponent* imgn, const char* typeName);
		
		int currentComponent;
		int numSameComponent[MAX_COMPONENTS];
	private:
		static ImgnProperties* props;
		ImgnComponent* components[MAX_COMPONENTS][MAX_SAME_COMPONENT];
		const char* componentNames[MAX_COMPONENTS];
		int numComponents;
		int numValues[MAX_COMPONENTS][MAX_SAME_COMPONENT];
		std::string variableNames[MAX_COMPONENTS][MAX_SAME_COMPONENT][MAX_VARIABLES];
		const char* typeName[MAX_COMPONENTS][MAX_SAME_COMPONENT][MAX_VARIABLES];
		void* values[MAX_COMPONENTS][MAX_SAME_COMPONENT][MAX_VARIABLES];
	};
}