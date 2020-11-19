#include "Bullet.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include <iostream>

Bullet::Bullet()
{
	TextureManager::Instance()->load("../Assets/textures/detonator1.png", "circle");
	const auto size = TextureManager::Instance()->getTextureSize("circle");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(50.0f + rand() % 700, 0.0f - rand() % 300); //Possible spawn range 300 off of the top of screen
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(BULLET);

	SoundManager::Instance().load("../Assets/audio/thunder.ogg", "explosion", SOUND_SFX);
}

Bullet::~Bullet() = default;

void Bullet::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the target
	TextureManager::Instance()->draw("circle", x, y, 0, 255, true);
}

void Bullet::update()
{
	if (inUse)
	{
		m_move();
		m_checkCollision();
		if (Collided)
		{
			SoundManager::Instance().playSound("explosion");
			m_reset();
		}
	}
}

void Bullet::clean()
{
}

void Bullet::m_move()
{
	float deltaTime = 1.0f / 60.0f;

	if (getTransform()->position.y <= 600.0f)
	{
		getRigidBody()->acceleration = Gravity;
		getRigidBody()->velocity += getRigidBody()->acceleration * deltaTime;
	}
	else
	{
		m_reset();
	}
	getTransform()->position += getRigidBody()->velocity * deltaTime;
}

void Bullet::m_reset()
{
	inUse = false;
	Collided = false;
	getRigidBody()->isColliding = false;
	getTransform()->position = glm::vec2(50.0f + rand() % 700, 0.0f - rand() % 300); //Possible spawn range 300 off of the top of screen
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->acceleration = glm::vec2(0, 0);
}

void Bullet::m_checkCollision()
{
}
