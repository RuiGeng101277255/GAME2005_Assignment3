#include "Scene2.h"
#include "Game.h"
#include "EventManager.h"

Scene2::Scene2()
{
	Scene2::start();
}

Scene2::~Scene2() = default;

void Scene2::draw()
{
	drawDisplayList();
}

void Scene2::update()
{
	if (m_pBrick->getTransform()->position != EventManager::Instance().getMousePosition())
	{
		m_pBrick->Prev_Pos = m_pBrick->getTransform()->position;
		m_pBrick->getTransform()->position = EventManager::Instance().getMousePosition();
		auto dX = m_pBrick->getTransform()->position.x - m_pBrick->Prev_Pos.x;
		auto dY = m_pBrick->getTransform()->position.y - m_pBrick->Prev_Pos.y;
		m_pBrick->MomentumFactor = glm::vec2(dX, dY);
	}

	if (CollisionManager::AABBCheck(m_pBrick, m_pBall))
	{
		m_pBall->MomentumFactor = m_pBrick->MomentumFactor;
		
	}
	updateDisplayList();
}

void Scene2::clean()
{
	removeAllChildren();
}

void Scene2::handleEvents()
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

void Scene2::start()
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

	m_pBrick = new Brick();
	addChild(m_pBrick);

	m_pBall = new BouncyBall();
	addChild(m_pBall);
}
