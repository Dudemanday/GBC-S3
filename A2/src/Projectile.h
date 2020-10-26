#pragma once
#ifndef __PROJECTILE__
#define __PROJECTILE__

#include "DisplayObject.h"
class Projectile : public DisplayObject
{
public:
	Projectile();
	~Projectile();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	bool m_bGravity;
	glm::vec2 throwSpeed;
	float m_mass;
	float m_friction;
	glm::vec2 maxSpeed = { 0, 0 };

	void throwProjectile(glm::vec2 rampSize);
	void setScale(int scale);
	void resetProjectile(glm::vec2 rampPos, float rampHeight);

private:
	void m_move();
	void m_checkBounds();
	void m_reset();

	template <typename N> inline
		N radToDeg(N r);

	int m_scale;
	float m_gravity;
	float groundLevel;
	glm::vec2 accelerationWithFriction;
};
#endif /* defined (__PROJECTILE__) */