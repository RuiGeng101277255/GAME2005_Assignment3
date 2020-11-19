#pragma once
#ifndef __SCENE1__
#define __SCENE1__

#include "Scene.h"
#include "Button.h"
#include "BulletPool.h"

class Scene1 : public Scene
{
public:
	Scene1();
	~Scene1();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

private:

	Button* m_pBackButton;
	Button* m_pFireButton;

	BulletPool* m_pBulletPool;
};

#endif // !__SCENE1__