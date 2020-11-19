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
	m_pBulletPool->checkCollisionWith(m_pPlayer);
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

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		m_pPlayer->getTransform()->position += glm::vec2(-3, 0);
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		m_pPlayer->getTransform()->position += glm::vec2(3, 0);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
	{
		m_pPlayer->getTransform()->position += glm::vec2(0, -3);
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	{
		m_pPlayer->getTransform()->position += glm::vec2(0, 3);
	}
}

void Scene1::start()
{
	m_pBulletPool = new BulletPool();
	addChild(m_pBulletPool);

	m_pPlayer = new Player();
	addChild(m_pPlayer);


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