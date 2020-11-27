#pragma once
#ifndef __BOUNCY_BALL__
#define __BOUNCY_BALL__

#include "DisplayObject.h"

class BouncyBall final : public DisplayObject
{
public:
	BouncyBall();
	~BouncyBall();

	enum Col_Location //Collision location
	{
		NONE,
		SIDE,
		TOP_DOWN
	};

	enum Texture_Choice
	{
		BALL,
		CUBE,
		TRIANGLE
	};

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void setPlay(bool b);
	void setCollisionLocation(char loc);
	void setEnergyLost(float l);

	void changeDrawTexture(int n);

	glm::vec2 MomentumFactor;

	std::string getBallPos();
	std::string getBallVel();

	float mass = 5.0f;

private:
	void m_move();
	void m_checkCollision();
	bool isPlaying = true;
	Col_Location cur_col = NONE;
	float p_lostFactor = 0.995f; //momentum loss factor
	Texture_Choice choice = BALL;
	glm::vec2 sizeB;
	glm::vec2 sizeC;
	glm::vec2 sizeT;
};

#endif // !__BOUNCY_BALL__