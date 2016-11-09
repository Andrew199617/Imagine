#include "SphereCollider.h"
#include "../RenderEngine/RenderInfo.h"

void SphereCollider::Update(float)
{

}

SphereCollider::~SphereCollider() 
{

}

float SphereCollider::GetRadius()
{
	return radius;
}

void SphereCollider::OnValueChange(std::string VariableName)
{
	Imgn::DisplayData* m_DisplayData = GetDisplayData();
	if (m_DisplayData)
	{
		for (int iCurVal = 0; iCurVal < m_DisplayData->numValues; ++iCurVal)
		{
			if (VariableName == m_DisplayData->variableNames[iCurVal])
			{
				size = glm::vec3(radius, radius, radius);
				DisplayCollider("Sphere");
			}
		}
	}
}

