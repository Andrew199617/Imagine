#pragma once
#include "HealthEntity.h"

class AIEntity :
	public HealthEntity
{
private:
	float m_fatigue;
	float m_dmg;
public:
	AIEntity();
	~AIEntity();

public:
	float Fatigue() { return m_fatigue; }
	float Dmg() { return m_dmg; }
	void GainFatigue(const float amount) { m_fatigue += amount; if (m_fatigue > 100) m_fatigue = 100; }
	void LoseFatigue(const float amount) { m_fatigue -= amount; if (m_fatigue < 0) m_fatigue = 0; }
};

