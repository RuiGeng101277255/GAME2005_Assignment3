#pragma once
#ifndef __BRICK__
#define __BRICK__

#include "DisplayObject.h"

class Brick final : public DisplayObject
{
public:
	Brick();
	~Brick();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void setPosition(glm::vec2 Pos);
	glm::vec2 Prev_Pos;
	glm::vec2 MomentumFactor;
	float mass = 10.0f;

private:

};

#endif // !__BRICK__