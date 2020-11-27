#include "Scene1.h"
#include "Game.h"
#include "EventManager.h"

#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

Scene1::Scene1()
{
	Scene1::start();
}

Scene1::~Scene1() = default;

void Scene1::draw()
{
	TextureManager::Instance()->draw("gameBG", 400, 300, 0, 255, true);
	drawDisplayList();
	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}
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
		m_pPlayer->getTransform()->position += glm::vec2(-5, 0);
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		m_pPlayer->getTransform()->position += glm::vec2(5, 0);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
	{
		m_pPlayer->getTransform()->position += glm::vec2(0, -5);
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	{
		m_pPlayer->getTransform()->position += glm::vec2(0, 5);
	}
}

void Scene1::start()
{
	TextureManager::Instance()->load("../Assets/textures/new/gameBG.png", "gameBG");

	m_pBulletPool = new BulletPool();
	addChild(m_pBulletPool);

	m_pPlayer = new Player();
	addChild(m_pPlayer);

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

	m_pFireButton = new Button("../Assets/textures/new/activateButton.png", "FireButton", FIRE_BUTTON);
	m_pFireButton->getTransform()->position = glm::vec2(750.0f, 550.0f);
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

void Scene1::GUI_Function() const
{
	ImGui::NewFrame();
	ImGui::Begin("Game Physics Controller", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	static float gravScale = 9.8f;
	if (ImGui::SliderFloat("Gravity: ", &gravScale, 0, 100.0f))
	{
		m_pBulletPool->setBulletGrav(glm::vec2(0.0f, gravScale));
	}

	for (int i = 0; i < 10; i++)
	{
		ImGui::Text(("Bullet #" + std::to_string(i) + " ").c_str());
		ImGui::Text(m_pBulletPool->getBulletInUse(i).c_str());
		ImGui::Text(m_pBulletPool->getBulletPos(i).c_str());
		ImGui::Text(m_pBulletPool->getBulletVel(i).c_str());
		ImGui::Text(m_pBulletPool->getBulletAcc(i).c_str());
	}



	ImGui::End();
	ImGui::EndFrame();

	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
