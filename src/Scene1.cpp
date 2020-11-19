#include "Scene1.h"
#include "Game.h"
#include "EventManager.h"

Scene1::Scene1()
{
	Scene1::start();
}

Scene1::~Scene1() = default;

void Scene1::draw()
{
	drawDisplayList();
}

void Scene1::update()
{
	updateDisplayList();
}

void Scene1::clean()
{
	removeAllChildren();
}

void Scene1::handleEvents()
{
	EventManager::Instance().update();

	// Button Events
	m_pBackButton->update();

	// Keyboard Events
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}
}

void Scene1::start()
{
	m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(400.0f, 400.0f);
	m_pBackButton->addEventListener(CLICK, [&]()-> void
		{
			m_pBackButton->setActive(false);
			TheGame::Instance()->changeSceneState(START_SCENE);
		});

	m_pBackButton->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pBackButton->setAlpha(128);
		});

	m_pBackButton->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pBackButton->setAlpha(255);
		});

	addChild(m_pBackButton);
}
