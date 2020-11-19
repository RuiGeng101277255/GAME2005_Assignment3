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
	m_pBulletPool = new BulletPool();
	addChild(m_pBulletPool);

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

	m_pFireButton = new Button("../Assets/textures/mine.png", "FireButton", FIRE_BUTTON);
	m_pFireButton->getTransform()->position = glm::vec2(400.0f, 500.0f);
	m_pFireButton->addEventListener(CLICK, [&]()-> void
		{
			m_pFireButton->setActive(false);
			m_pBulletPool->spawnBullet();
		});

	m_pFireButton->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pFireButton->setAlpha(128);
		});

	m_pFireButton->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pFireButton->setAlpha(255);
		});

	addChild(m_pFireButton);
}