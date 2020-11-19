#include "StartScene.h"
#include "Scene1.h"
#include "Scene2.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}
}

void StartScene::start()
{
	const SDL_Color blue = { 0, 0, 255, 255 };
	m_pStartLabel = new Label("START SCENE", "Consolas", 80, blue, glm::vec2(400.0f, 40.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	m_pInstructionsLabel = new Label("Press 1 to Play", "Consolas", 40, blue, glm::vec2(400.0f, 120.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);

	m_pJuanInfo = new Label("Juan de Gouveia 101203253", "Consolas", 40, blue, glm::vec2(400.0f, 200.0f));
	m_pJuanInfo->setParent(this);
	addChild(m_pJuanInfo);

	m_pRuiInfo = new Label("Rui Geng 101277255", "Consolas", 40, blue, glm::vec2(400.0f, 250.0f));
	m_pRuiInfo->setParent(this);
	addChild(m_pRuiInfo);

	// Start Button
	m_pStartButton = new Button();
	m_pStartButton->getTransform()->position = glm::vec2(400.0f, 400.0f); 

	m_pStartButton->addEventListener(CLICK, [&]()-> void
	{
		m_pStartButton->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	});
	
	m_pStartButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pStartButton->setAlpha(128);
	});

	m_pStartButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pStartButton->setAlpha(255);
	});
	addChild(m_pStartButton);

	///

	m_pScene1Button = new Button("../Assets/textures/scene1.png", "Scene1", SCENE1_BUTTON);
	m_pScene1Button->getTransform()->position = glm::vec2(200.0f, 500.0f);

	m_pScene1Button->addEventListener(CLICK, [&]()-> void
		{
			m_pScene1Button->setActive(false);
			TheGame::Instance()->changeSceneState(SCENE1);
		});

	m_pScene1Button->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pScene1Button->setAlpha(128);
		});

	m_pScene1Button->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pScene1Button->setAlpha(255);
		});
	addChild(m_pScene1Button);

	///

	m_pScene2Button = new Button("../Assets/textures/scene2.png", "Scene2", SCENE1_BUTTON);
	m_pScene2Button->getTransform()->position = glm::vec2(600.0f, 500.0f);

	m_pScene2Button->addEventListener(CLICK, [&]()-> void
		{
			m_pScene2Button->setActive(false);
			TheGame::Instance()->changeSceneState(SCENE2);
		});

	m_pScene2Button->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pScene2Button->setAlpha(128);
		});

	m_pScene2Button->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pScene2Button->setAlpha(255);
		});
	addChild(m_pScene2Button);
}

