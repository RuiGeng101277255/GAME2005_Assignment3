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

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void setPlay(bool b);
	void setCollisionLocation(char loc);
	void setEnergyLost(float l);

	glm::vec2 MomentumFactor;

private:
	void m_move();
	void m_checkCollision();
	bool isPlaying = true;
	Col_Location cur_col = NONE;
	float p_lostFactor = 0.995f; //momentum loss factor
};

#endif // !__BOUNCY_BALL__