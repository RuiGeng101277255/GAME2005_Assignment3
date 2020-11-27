#include "BouncyBall.h"
#include "TextureManager.h"

BouncyBall::BouncyBall()
{
	TextureManager::Instance()->load("../Assets/textures/new/ball.png", "ball");
	const auto size = TextureManager::Instance()->getTextureSize("ball");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(300.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(-200.0f, 75.0f);
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
	TextureManager::Instance()->draw("ball", x, y, 0, 255, true);
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

void BouncyBall::setCollisionLocation(char loc)
{
	switch (loc)
	{
	case 's':
		cur_col = SIDE;
		break;
	case 't':
		cur_col = TOP_DOWN;
		break;
	}
}

void BouncyBall::setEnergyLost(float l)
{
	p_lostFactor = l;
}

void BouncyBall::m_move()
{
	float deltaTime = 1.0f / 60.0f;
	if (abs(getRigidBody()->velocity.x) < 0.05f)
	{
		getRigidBody()->velocity.x = 0.0f;
	}

	if (abs(getRigidBody()->velocity.y) < 0.05f)
	{
		getRigidBody()->velocity.y = 0.0f;
	}
	getTransform()->position += getRigidBody()->velocity * deltaTime;
}

void BouncyBall::m_checkCollision()
{
	if (cur_col == NONE)
	{
		if ((getTransform()->position.x <= 32.0f) || (getTransform()->position.x >= 768.0f))
		{
			cur_col = SIDE;
		}

		if ((getTransform()->position.y <= 32.0f) || (getTransform()->position.y >= 568.0f))
		{
			cur_col = TOP_DOWN;
		}
	}
	if (cur_col != NONE)
	{
		switch (cur_col)
		{
		case SIDE:
			getRigidBody()->velocity.x *= -p_lostFactor;
			getRigidBody()->velocity.x += MomentumFactor.x;
			cur_col = NONE;
			break;
		case TOP_DOWN:
			getRigidBody()->velocity.y *= -p_lostFactor;
			getRigidBody()->velocity.x += MomentumFactor.y;
			cur_col = NONE;
			break;
		}
		cur_col = NONE;
		MomentumFactor = glm::vec2(0.0f, 0.0f);
	}
}
