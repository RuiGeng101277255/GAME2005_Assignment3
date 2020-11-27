#include "Brick.h"
#include "TextureManager.h"

Brick::Brick()
{
	TextureManager::Instance()->load("../Assets/textures/new/brick.png", "brick");
	const auto size = TextureManager::Instance()->getTextureSize("brick");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(50.0f + rand() % 700, 0.0f - rand() % 300); //Possible spawn range 300 off of the top of screen
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(BRICK);
}

Brick::~Brick() = default;

void Brick::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the target
	TextureManager::Instance()->draw("brick", x, y, 0, 255, true);
}

void Brick::update()
{
}

void Brick::clean()
{
}

void Brick::setPosition(glm::vec2 Pos)
{
	getTransform()->position = Pos;
}
