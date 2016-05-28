#pragma once
#include "HealthEntity.h"
class WeaponEntity :
	public HealthEntity
{
private:
	float m_dmg;
public:
	WeaponEntity() { m_dmg = 55; }
	~WeaponEntity(){}

	void SetDmg(float dmg) { m_dmg = dmg; }
	float Dmg() { return m_dmg; }
	void DealDmgTo(HealthEntity* target) { target->GotHit(m_dmg); }
};

