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
	TextureManager::Instance()->draw("bg", 400, 300, 0, 255, true);
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
		//m_pBrick->MomentumFactor = glm::vec2(dX, dY);
	}

	if (CollisionManager::TopCheck(m_pBrick, m_pBall))
	{
		m_pBall->setCollisionLocation('t');
		if (m_pBall->getTransform()->position.y < m_pBrick->getTransform()->position.y)
		{
			m_pBall->getTransform()->position.y -= 5.0f;
		}
		else
		{
			m_pBall->getTransform()->position.y += 5.0f;
		}
	}

	if (CollisionManager::SideCheck(m_pBrick, m_pBall))
	{
		m_pBall->setCollisionLocation('s');
		if (m_pBall->getTransform()->position.x < m_pBrick->getTransform()->position.x)
		{
			m_pBall->getTransform()->position.x -= 5.0f;
		}
		else
		{
			m_pBall->getTransform()->position.x += 5.0f;
		}
	}

	//checkTop();
	//checkSide();

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
	TextureManager::Instance()->load("../Assets/textures/new/bg2.png", "bg");

	m_pBackButton = new Button("../Assets/textures/new/backButton.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(50.0f, 550.0f);
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

	m_pFireButton = new Button("../Assets/textures/new/activateButton.png", "FireButton", FIRE_BUTTON);
	m_pFireButton->getTransform()->position = glm::vec2(750.0f, 550.0f);
	m_pFireButton->addEventListener(CLICK, [&]()-> void
		{
			m_pFireButton->setActive(false);
			//m_pBulletPool->spawnBullet();
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

void Scene2::checkTop()
{
	if ((m_pBall->getTransform()->position.x + m_pBall->getWidth() >= m_pBrick->getTransform()->position.x)&& (m_pBall->getTransform()->position.x + m_pBall->getWidth() <= m_pBrick->getTransform()->position.x + m_pBrick->getWidth()))
	{
		if ((m_pBall->getTransform()->position.y > m_pBrick->getTransform()->position.y)&&((m_pBall->getTransform()->position.y - m_pBall->getHeight() <= m_pBrick->getTransform()->position.y + m_pBrick->getHeight())))
		{
			m_pBall->setCollisionLocation('t');
		}
		else if ((m_pBall->getTransform()->position.y < m_pBrick->getTransform()->position.y) && ((m_pBall->getTransform()->position.y + m_pBall->getHeight() <= m_pBrick->getTransform()->position.y - m_pBrick->getHeight())))
		{
			m_pBall->setCollisionLocation('t');
		}
	}
}

void Scene2::checkSide()
{
	if ((m_pBall->getTransform()->position.y >= m_pBrick->getTransform()->position.y + m_pBrick->getHeight()) && (m_pBall->getTransform()->position.y + m_pBall->getHeight() <= m_pBrick->getTransform()->position.y + m_pBrick->getHeight()))
	{
		if ((m_pBall->getTransform()->position.x > m_pBrick->getTransform()->position.x) && ((m_pBall->getTransform()->position.x - m_pBall->getWidth() <= m_pBrick->getTransform()->position.x + m_pBrick->getWidth())))
		{
			m_pBall->setCollisionLocation('s');
		}
		else if ((m_pBall->getTransform()->position.x < m_pBrick->getTransform()->position.x) && ((m_pBall->getTransform()->position.x + m_pBall->getWidth() <= m_pBrick->getTransform()->position.x - m_pBrick->getWidth())))
		{
			m_pBall->setCollisionLocation('s');
		}
	}
}
