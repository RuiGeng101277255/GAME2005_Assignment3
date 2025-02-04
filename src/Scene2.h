#pragma once
#ifndef __SCENE2__
#define __SCENE2__

#include "Scene.h"
#include "Button.h"
#include "Brick.h"
#include "BouncyBall.h"

class Scene2 : public Scene
{
public:
	Scene2();
	~Scene2();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

private:
	Brick* m_pBrick;
	BouncyBall* m_pBall;
	Button* m_pFireButton;
	Button* m_pBackButton;

	void CollisionCheck();
	void checkTop();
	void checkSide();

	void GUI_Function() const;
};

#endif // !__SCENE2__