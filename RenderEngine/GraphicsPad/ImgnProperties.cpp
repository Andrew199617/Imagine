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
				return;
			}
		}
		componentNames[numComponents] = name;
		components[numComponents][numSameComponent[currentComponent]] = imgn;
		currentComponent = numComponents;
		numSameComponent[currentComponent]++;
		numComponents++;
	}
}