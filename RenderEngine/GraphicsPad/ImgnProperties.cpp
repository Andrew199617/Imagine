#include "ImgnProperties.h"

namespace Imgn
{
	ImgnProperties* ImgnProperties::props = 0;

	void ImgnProperties::AddClass(ImgnComponent * imgn,const char* name)
	{
		for (int i = 0; i < numComponents; i++)
		{
			if (name == componentNames[i])
			{
				currentComponent = i;
				components[currentComponent][numSameComponent[currentComponent]] = imgn;
				numSameComponent[currentComponent]++;
				numValues[currentComponent] = 0;
				return;
			}
		}
		currentComponent = numComponents;
		componentNames[numComponents] = name;
		components[numComponents][numSameComponent[currentComponent]] = imgn;
		numSameComponent[currentComponent]++;
		numComponents++;
	}
}