#pragma once
#ifndef __SCENE2__
#define __SCENE2__

#include "Scene.h"
#include "Button.h"

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

	Button* m_pBackButton;
};

#endif // !__SCENE2__