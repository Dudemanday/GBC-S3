#include "BackgroundScale.h"
#include "Util.h"
#include "TextureManager.h"

BackgroundScale::BackgroundScale()
{
	TextureManager::Instance()->load("../Assets/scale.png", "bg");

	const auto size = TextureManager::Instance()->getTextureSize("bg");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(0, 0);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;
	setType(RAMP);
}

BackgroundScale::~BackgroundScale()
= default;

void BackgroundScale::draw()
{
	//const auto x = getTransform()->position.x;
	//const auto y = getTransform()->position.y;
	//TextureManager::Instance()->draw("bg", x, y, 0, 255, true);

	glm::vec2 screenSize = { 800.0f, 600.0f };
	float scale = 50.0f;

	for (int x = 0; x < screenSize.x; x += scale)
	{
		Util::DrawLine(glm::vec2{ x, 0 }, glm::vec2(x, screenSize.y), glm::vec4{ 80, 80, 80, 255});
	}
}

void BackgroundScale::update()
{

}

void BackgroundScale::clean() {}

void BackgroundScale::setPosition(glm::vec2 pos)
{
	getTransform()->position = pos;
}

void BackgroundScale::m_reset() {}
