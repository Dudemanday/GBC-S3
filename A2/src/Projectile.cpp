#include "Projectile.h"
#include "TextureManager.h"
#include <math.h> 
#include <stdio.h>
#include "Util.h"

Projectile::Projectile()
{
	TextureManager::Instance()->load("../Assets/textures/Circle.png", "circle");

	const auto size = TextureManager::Instance()->getTextureSize("circle");
	setWidth(size.x);
	setHeight(size.y);
	getRigidBody()->isColliding = false;
	setType(TARGET);
	getTransform()->position = glm::vec2(50.0f, 400.0f - getHeight() / 2);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	groundLevel = 550.0f;
	m_mass = 12.8f;
	m_friction = 0.42;
}

Projectile::~Projectile()
= default;

void Projectile::resetProjectile(glm::vec2 rampPos, float rampHeight)
{
	getTransform()->position = glm::vec2(rampPos.x, rampPos.y - rampHeight - getHeight() / 2);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	groundLevel = rampPos[1];
	maxSpeed = glm::vec2(0.0f, 0.0f);
}

void Projectile::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the target
	TextureManager::Instance()->draw("circle", x, y, 0, 255, true);
}

void Projectile::update()
{
	m_move();
	m_checkBounds();
}

void Projectile::clean()
{
}

void Projectile::throwProjectile(glm::vec2 rampSize)
{
	//acceleration
	float rampLength = sqrt(pow(rampSize.x, 2) + pow(rampSize.y, 2));
	float rampAngle = atan(rampSize.y / rampSize.x);

	m_gravity = (9.8 * m_scale) * sin(rampAngle);
	getRigidBody()->acceleration = glm::vec2(m_gravity * cos(rampAngle), m_gravity * sin(rampAngle));
	accelerationWithFriction = glm::vec2(-(m_friction * m_gravity), 0.0f);

	//gives the projectile a one time kick start
	getRigidBody()->velocity.x += 0.000001f;
}

void Projectile::setScale(int scale)
{
	m_scale = scale;
}

void Projectile::m_move()
{
	float deltaTime = 1.0f / 60.0f;

	//projectile hits the ground
	if (getTransform()->position.y + getHeight() / 2 >= groundLevel)
	{
		getTransform()->position.y = groundLevel - getHeight() / 2; //-sets the projectile on the ground
		getRigidBody()->velocity.y = 0.0f; //-zeroes out y velocity
		getRigidBody()->acceleration = accelerationWithFriction; //replaces acceleration with friction
	}

	//works for both speeding up down the ramp and slowing down due to friction
	if (getRigidBody()->velocity.x > 0)
	{
		getRigidBody()->velocity += getRigidBody()->acceleration * deltaTime;
	}
	//zeroes out velocity when it is slow enough 
	else if (getRigidBody()->velocity.x < 0.05)
	{
		getRigidBody()->velocity.x = 0;
		getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	}
	getTransform()->position += getRigidBody()->velocity * deltaTime;

	if (getRigidBody()->velocity.x > maxSpeed.x || getRigidBody()->velocity.y > maxSpeed.y)
	{
		maxSpeed = getRigidBody()->velocity;
	}
}

void Projectile::m_checkBounds()
{
}

void Projectile::m_reset()
{
}

template<typename N>
inline N Projectile::radToDeg(N r)
{
	return r * 3.14159265 / 180;
}