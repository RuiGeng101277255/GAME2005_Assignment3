#pragma once
#ifndef __BULLET_POOL__
#define __BULLET_POOL__

#include "Bullet.h"
#include "DisplayObject.h"
#include "GameObject.h"

class BulletPool final : public DisplayObject
{
public:
	BulletPool();
	~BulletPool();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void spawnBullet(int num = 10);
	void setBulletGrav(glm::vec2 grav);

	void checkCollisionWith(GameObject* obj);

private:
	static const int PoolSize = 10;
	Bullet* bullet[PoolSize];
	GameObject* m_pReference;
};

#endif // !__BULLET_POOL__