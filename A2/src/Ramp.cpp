#include "Ramp.h"
#include "Util.h"

Ramp::Ramp()
{
	setWidth(200.0f);
	setHeight(150.0f);
	getTransform()->position = glm::vec2(50, 550.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;
	setType(RAMP);
}

Ramp::~Ramp()
= default;

void Ramp::draw()
{
	glm::vec2 pos = getTransform()->position;

	//black ground line
	Util::DrawLine(glm::vec2(0, pos[1]), glm::vec2(800, pos[1]), glm::vec4(255, 255, 255, 255));

	//green ramp
	Util::DrawLine(pos, glm::vec2(pos[0] + getWidth(), pos[1]));
	Util::DrawLine(pos, glm::vec2(pos[0], pos[1] - getHeight()));
	Util::DrawLine(glm::vec2(pos[0], pos[1] - getHeight()), glm::vec2(pos[0] + getWidth(), pos[1]));
}

void Ramp::update()
{

}

void Ramp::clean() {}

void Ramp::setPosition(glm::vec2 pos)
{
	getTransform()->position = pos;
}

void Ramp::m_reset() {}
