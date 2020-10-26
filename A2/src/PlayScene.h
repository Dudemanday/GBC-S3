#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Label.h"
#include "Projectile.h"
#include "Ramp.h"
#include "BackgroundScale.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
	
private:
	// IMGUI Function
	void GUI_Function();
	char* NameAndFloatToChar(const char* text, float f);
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	//Plane* m_pPlaneSprite;
	//Player* m_pPlayer;
	//bool m_playerFacingRight;

	//physics
	bool m_bSimulationActive = false;
	BackgroundScale* m_pBg;
	Ramp* m_pRamp;
	Projectile* m_pProjectile;
	float m_scale = 50.0f;

	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructionsLabel;
};

#endif /* defined (__PLAY_SCENE__) */