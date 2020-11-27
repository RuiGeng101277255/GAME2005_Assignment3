#include "BulletPool.h"
#include <iostream>
#include "Util.h"
#include "CollisionManager.h"

BulletPool::BulletPool()
{
	for (int i = 0; i < PoolSize; i++)
	{
		bullet[i] = new Bullet();
	}
}

BulletPool::~BulletPool() = default;

void BulletPool::draw()
{
	for (int a = 0; a < PoolSize; a++)
	{
		bullet[a]->draw();
	}
}

void BulletPool::update()
{
	for (int b = 0; b < PoolSize; b++)
	{
		bullet[b]->update();
	}
}

void BulletPool::clean()
{
	for (int c = 0; c < PoolSize; c++)
	{
		bullet[c]->clean();
	}
}

void BulletPool::spawnBullet(int num)
{
	if ((num > 0) && (num <= 10))
	{
		for (int j = 0; j < PoolSize; j++)
		{
			if (!bullet[j]->inUse)
			{
				bullet[j]->inUse = true;
				num--;
			}
		}
		num = 0;
	}
}

void BulletPool::setBulletGrav(glm::vec2 grav)
{
	for (int m = 0; m < PoolSize; m++)
	{
		bullet[m]->Gravity = grav;
	}
}

void BulletPool::checkCollisionWith(GameObject* obj)
{
	m_pReference = obj;
	for (int h = 0; h < PoolSize; h++)
	{
		if (CollisionManager::squaredRadiusCheck(obj, bullet[h]))
		{
			bullet[h]->Collided = true;
		}
	}
}

std::string BulletPool::getBulletInUse(int n)
{
	if (n < PoolSize)
	{
		return ("In use: " + std::to_string(bullet[n]->inUse));
	}
}

std::string BulletPool::getBulletPos(int n)
{
	if (n < PoolSize)
	{
		return ("Pos(m) x: " + std::to_string(bullet[n]->getTransform()->position.x) + " y: " + std::to_string(bullet[n]->getTransform()->position.y));
	}
}

std::string BulletPool::getBulletVel(int n)
{
	if (n < PoolSize)
	{
		return ("Vel(m/s) x: " + std::to_string(bullet[n]->getRigidBody()->velocity.x) + " y: " + std::to_string(bullet[n]->getRigidBody()->velocity.y));
	}
}

std::string BulletPool::getBulletAcc(int n)
{
	if (n < PoolSize)
	{
		return ("Grav(m/s^2) x: " + std::to_string(bullet[n]->Gravity.x) + " y: " + std::to_string(bullet[n]->Gravity.y));
	}
}
