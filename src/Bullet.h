#pragma once
#ifndef __BULLET__
#define __BULLET__

#include "DisplayObject.h"
#include <string>

class Bullet final : public DisplayObject {
public:
	Bullet();
	~Bullet();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	bool inUse = false;
	glm::vec2 Gravity = glm::vec2 (0.0f, 9.8f);


private:
	void m_move();
	void m_reset();
	void m_checkCollision();
};

#endif // !__BULLET__