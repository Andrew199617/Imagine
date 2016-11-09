#pragma once

#include "EntityData.h"
#include <string>
class ImgnComponent;

#define IMGN_END(className) isHidden = false;													\
	SetComponentType(imgnProps->currentComponent);												\
	SetComponentTypeNum(imgnProps->numSameComponent[imgnProps->currentComponent] - 1);			\
	layoutInitalized = false;																	\
	layoutHasData = false;																		\
	setMaximumSize(348, 250);																	\
	setMinimumSize(280, 50);																	\
	sizeHint().setHeight(50);																	\
	minimumSizeHint().setHeight(50);															\
	sizePolicy().setHorizontalPolicy(QSizePolicy::Policy::Expanding);							\
	sizePolicy().setVerticalPolicy(QSizePolicy::Policy::Minimum);								\
	setFocusPolicy(Qt::ClickFocus);																\
	m_owner = 0;																				\
	AwakeSuper(); 																				\
}																								\
~##className();																							

#define IMGN_GENERATE(className) public:														\
className(){																					\
	Imgn::ImgnProperties* imgnProps = Imgn::ImgnProperties::Instance();							\
	if(typeid(this) != typeid(ImgnComponent*) && dynamic_cast<ImgnComponent*>(this) == NULL)	\
	{																							\
		string errorMsg = ": does not inherit ImgnComponent. Invalid  IMGN_GENERATE";					\
		GameLogger::log(typeid(this).name() + errorMsg);												\
		GameLogger::shutdownLog();																\
		exit(1);																				\
	} 																							\
	imgnProps->AddClass(this,typeid(this).name());												
	

#define IMGN_PROPERTY_DEFAULT(name) imgnProps->AddProperty<decltype(&name)>(&name,#name);
#define IMGN_PROPERTY(name, init_value) imgnProps->AddProperty<decltype(&name)>(&name,#name); name = init_value;



namespace Imgn {

	struct CollisionData
	{
		ImgnComponent*** components;
		std::string* componentNames;
		int numComponents;
		int* numSameComponents;
	};

	struct DisplayData {
		std::string* typeName;
		std::string* variableNames;
		void** values;
		int numValues;
		bool hasData;
	};

	class ImgnProperties {

		ImgnProperties() : numComponents(0), numValues(), numSameComponent(), currentComponent(0) { }
	public:

		static ImgnProperties* Instance()
		{
			if (!props)
				props = new ImgnProperties;
			return props;
		}

		template<class V> inline void AddProperty(V var, std::string name)
		{
			name[0] = (char)toupper(name[0]);
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

			int i = currentComponent;
			int j = numSameComponent[i] - 1;
			int k = numValues[i];

			values[i][j][k] = var;
			numValues[i]++;
			if (j == 0)
			{
				typeName[i][k] = typeid(V).name();
				variableNames[i][k] = name;
			}
		}

		DisplayData* GetMyProperties(int componentType,int componentTypeNum)
		{
			datas[componentType][componentTypeNum] = new DisplayData;
			datas[componentType][componentTypeNum]->hasData = false;

			if (numValues[componentType] > 0)
			{
				datas[componentType][componentTypeNum]->values = values[componentType][componentTypeNum];
				datas[componentType][componentTypeNum]->typeName = typeName[componentType];
				datas[componentType][componentTypeNum]->variableNames = variableNames[componentType];
				datas[componentType][componentTypeNum]->numValues = numValues[componentType];
				datas[componentType][componentTypeNum]->hasData = true;
			}
			else
			{
				delete datas[componentType][componentTypeNum];
				return 0;
			}
			
			
			return datas[componentType][componentTypeNum];
		}
		
		inline void GetAllComponentData(CollisionData* componentData)
		{
			componentData->numComponents = 0;
			componentData->numSameComponents = new int[NUM_COLLIDERS];
			componentData->componentNames = new std::string[NUM_COLLIDERS];
			componentData->components = new ImgnComponent**[NUM_COLLIDERS];

			int cdCurComponent = 0;

			for (int iCurComp = 0; iCurComp < numComponents; ++iCurComp)
			{
				if (componentNames[iCurComp] == "class BoxCollider *" || componentNames[iCurComp] == "class SphereCollider *")
				{
					componentData->components[cdCurComponent] = components[iCurComp];
					componentData->componentNames[cdCurComponent] = componentNames[iCurComp];
					componentData->numSameComponents[cdCurComponent] = numSameComponent[iCurComp];
					++componentData->numComponents; 
					++cdCurComponent;
				}
			}
		}

		void AddClass(ImgnComponent* imgn, const char* typeName);
		
		int currentComponent;
		int numSameComponent[MAX_COMPONENTCLASS];
	private:
		DisplayData* datas[MAX_COMPONENTCLASS][MAX_SAME_COMPONENT];
		static ImgnProperties* props;
		ImgnComponent* components[MAX_COMPONENTCLASS][MAX_SAME_COMPONENT];
		std::string componentNames[MAX_COMPONENTCLASS];
		int numComponents;
		int numValues[MAX_COMPONENTCLASS];
		std::string variableNames[MAX_COMPONENTCLASS][MAX_VARIABLES];
		std::string typeName[MAX_COMPONENTCLASS][MAX_VARIABLES];
		void* values[MAX_COMPONENTCLASS][MAX_SAME_COMPONENT][MAX_VARIABLES];
	};
}