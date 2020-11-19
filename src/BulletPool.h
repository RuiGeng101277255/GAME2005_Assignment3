#pragma once
#ifndef __BULLET_POOL__
#define __BULLET_POOL__
#include "Util.h"
#include "Target.h"

class BulletPool
{
public:
	void createBullet(glm::vec2 Pos, glm::vec2 Vel, int lifeTime)
	{
		for (int i = 0; i < PoolSize; i++)
		{
			bullet[i] = new Target();
		}
	}

private:
	static const int PoolSize = 10;
	Target* bullet[PoolSize];
};

#endif // !__BULLET_POOL__