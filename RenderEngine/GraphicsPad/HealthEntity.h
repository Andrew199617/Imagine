#pragma once
#include "Entity.h"
#define MAX_HP 100
#define MIN_HP 0

class HealthEntity :
	public Imgn::Entity
{
public:
	HealthEntity() { m_health = 100; }
	~HealthEntity() {}

protected:
	float m_health;
public:
	bool IsDead() { return m_health <= MIN_HP; }
	bool IsAlive() { return m_health > MIN_HP; }
	float Health() { return m_health; }
	void Heal(const float amount) { m_health += amount; if (m_health > MAX_HP) m_health = MAX_HP; }
	void GotHit(float dmg) {
		m_health -= dmg; 
		if (m_health < MIN_HP)
			m_health = MIN_HP;
	}
};
