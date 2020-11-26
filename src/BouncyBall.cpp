#include "BouncyBall.h"
#include "TextureManager.h"

BouncyBall::BouncyBall()
{
	TextureManager::Instance()->load("../Assets/textures/detonator1.png", "circle");
	const auto size = TextureManager::Instance()->getTextureSize("circle");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(300.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(-100, 200);
	getRigidBody()->isColliding = false;

	setType(BOUNCE_BALL);
}

BouncyBall::~BouncyBall() = default;

void BouncyBall::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the target
	TextureManager::Instance()->draw("circle", x, y, 0, 255, true);
}

void BouncyBall::update()
{
	if (isPlaying)
	{
		m_move();
		m_checkCollision();
	}
}

void BouncyBall::clean()
{
}

void BouncyBall::setPlay(bool b)
{
	isPlaying = b;
}

void BouncyBall::setCollisionLocation(Col_Location loc)
{
	cur_col = loc;
}

void BouncyBall::setEnergyLost(float l)
{
	E_lost = l;
}

void BouncyBall::m_move()
{
	float deltaTime = 1.0f / 60.0f;
	getTransform()->position += getRigidBody()->velocity * deltaTime;
}

void BouncyBall::m_checkCollision()
{
	if ((getTransform()->position.x <= 0.0f) || (getTransform()->position.x >= 800.0f))
	{
		cur_col = SIDE;
	}

	if ((getTransform()->position.y <= 0.0f) || (getTransform()->position.y >= 600.0f))
	{
		cur_col = TOP_DOWN;
	}

	if (cur_col != NONE)
	{
		switch (cur_col)
		{
		case SIDE:
			getRigidBody()->velocity.x *= (-1.0f * E_lost);
			getRigidBody()->velocity.x += MomentumFactor.x;
			break;
		case TOP_DOWN:
			getRigidBody()->velocity.y *= (-1.0f * E_lost);
			getRigidBody()->velocity.x += MomentumFactor.y;
			break;
		}
		cur_col = NONE;
		MomentumFactor = glm::vec2(0, 0);
	}
}
