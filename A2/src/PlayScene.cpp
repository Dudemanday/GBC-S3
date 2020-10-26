#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	/*if(EventManager::Instance().isIMGUIActive())
	{*/
		GUI_Function();
	//}
	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";

	//background scale
	//m_pBg = new BackgroundScale();
	//addChild(m_pBg);

	//ramp
	m_pRamp = new Ramp();
	addChild(m_pRamp);

	//projectile
	m_pProjectile = new Projectile();
	m_pProjectile->setScale(m_scale);
	addChild(m_pProjectile);

	/* Instructions Label */
	//m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Debug View", "Consolas");
	//m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 590.0f);
	//addChild(m_pInstructionsLabel);
}

void PlayScene::GUI_Function()
{
	//game screen
	//width: 800, height: 600
	//16m x 12m

	//imgui
	static float buttonWidth = 150.0f;
	static float textWidth = 50.0f;

	//default values
	static float mass = { 12.8f };
	static float friction = { 0.42f };
	static float pos[2] = { 1.0f, 11.0f };
	static float rampSize[2] = { 4.0f, 3.0f };

	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	//Start button
	if (ImGui::Button("Start Simulation"))
	{
		m_bSimulationActive = true;
		m_pProjectile->throwProjectile(glm::vec2(m_pRamp->getWidth(), m_pRamp->getHeight()));
	}
	ImGui::SameLine(buttonWidth + 10);
	if (ImGui::Button("Reset"))
	{
		if (m_bSimulationActive)
		{
			m_bSimulationActive = false;
			m_pRamp->setWidth(rampSize[0] * m_scale);
			m_pRamp->setHeight(rampSize[1] * m_scale);
			m_pProjectile->resetProjectile(glm::vec2(pos[0] * m_scale, pos[1] * m_scale), rampSize[1] * m_scale);
		}
	}

	//mass input
	if (ImGui::SliderFloat("Mass (kg)", &mass, 0.01f, 50.0f))
	{
		if (!m_bSimulationActive)
		{
			m_pProjectile->m_mass = mass;
		}
	}
	ImGui::Separator();

	//------ramp------

	//size input
	if (ImGui::SliderFloat2("Ramp Size (m)", rampSize, 0.01f, 8.0f))
	{
		if (!m_bSimulationActive)
		{
			m_pRamp->setWidth(rampSize[0] * m_scale);
			m_pRamp->setHeight(rampSize[1] * m_scale); 
			m_pProjectile->resetProjectile(glm::vec2(pos[0] * m_scale, pos[1] * m_scale), rampSize[1] * m_scale);
		}
	}
	//position input
	if (ImGui::SliderFloat2("Position (m)", pos, 0.0f, 12.0f))
	{
		if (!m_bSimulationActive)
		{
			//sets ramp pos
			m_pRamp->setPosition(glm::vec2(pos[0] * m_scale, pos[1] * m_scale));
			//sets loot crate to top of the ramp
			m_pProjectile->resetProjectile(glm::vec2(pos[0] * m_scale, pos[1] * m_scale), rampSize[1] * m_scale);
		}
	}
	ImGui::Separator();
	
	//------other------
	//friction
	if (ImGui::SliderFloat("Friction (Uk)", &friction, 0.0f, 1.0f))
	{
		if (!m_bSimulationActive)
		{
			m_pProjectile->m_friction = friction;
		}
	}
	ImGui::Separator();

	//------Statistics output------
	//Velocity
	glm::vec2 v = m_pProjectile->getRigidBody()->velocity;
	//x axis
	char velTextx[16] = "";
	strcat(velTextx, NameAndFloatToChar("Vx:", v.x));
	ImGui::Text(velTextx);
	//y axis
	char velTexty[16] = "";
	strcat(velTexty, NameAndFloatToChar(" | Vy:", v.y));
	ImGui::SameLine(textWidth + 10);
	ImGui::Text(velTexty);

	//acceleration
	glm::vec2 a = m_pProjectile->getRigidBody()->acceleration;
	//x axis
	char accTextx[16] = "";
	strcat(accTextx, NameAndFloatToChar("Ax:", a.x));
	ImGui::SameLine(textWidth * 3 + 10);
	ImGui::Text(accTextx);
	//y axis
	char accTexty[16] = "";
	if (a.y == 0.0)
	{
		strcat(accTexty, NameAndFloatToChar(" | Ay:", a.y));
	}
	else
	{
		strcat(accTexty, NameAndFloatToChar(" | Ay:", -a.y));
	}
	ImGui::SameLine(textWidth * 4 + 10);
	ImGui::Text(accTexty);

	//max velocity
	glm::vec2 vMax = m_pProjectile->maxSpeed;
	char velMaxText[16] = "";
	strcat(velMaxText, NameAndFloatToChar("Max V:", sqrt(pow(vMax.x, 2) + pow(vMax.y, 2))));
	ImGui::Text(velMaxText);

	//position
	glm::vec2 posF = m_pProjectile->getTransform()->position;
	//x axis
	char posOutputTextx[16] = "";
	strcat(posOutputTextx, NameAndFloatToChar("PosX:", posF.x - pos[0] * m_scale));
	ImGui::SameLine(textWidth * 3 - 10);
	ImGui::Text(posOutputTextx);
	//y axis
	char posOutputTexty[16] = "";
	strcat(posOutputTexty, NameAndFloatToChar(" | PosY:", pos[1] * m_scale - posF.y - m_pProjectile->getHeight() / 2));
	ImGui::SameLine(textWidth * 4 + 10);
	ImGui::Text(posOutputTexty);

	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}

char* PlayScene::NameAndFloatToChar(const char* text, float f)
{
	if (sizeof(text) > 0) //checks if numbers are valid
	{
		if (f == f) //checks if text is valid
		{
			char val[16];
			sprintf(val, "%G", floorf((f / m_scale) * 100) / 100); //float to 2 decimals, then float->char
			char temp[32] = "";
			strcat(temp, text);
			strcat(temp, val);
			return temp;
			}
		else
		{
			//std::cout << "invalid float" << std::endl;
		}
	}
	else
	{
		//std::cout << "invalid text" << std::endl;
	}
	return "";
}
