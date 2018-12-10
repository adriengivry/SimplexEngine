/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include <iostream>

#include <GyvrIni/GyvrIni.h>

#include "SimplexEngine/Scripts/GlobalScripts/FPSCounter.h"

SimplexEngine::Scripts::GlobalScripts::FPSCounter::FPSCounter(Rendering::UserInterface& p_userInterface, float p_updateFrequency) :
	m_userInterface(p_userInterface),
	m_updateFrequency(p_updateFrequency),
	m_updateTimer(p_updateFrequency),
	m_fps(0)
{
}

void SimplexEngine::Scripts::GlobalScripts::FPSCounter::Update(float p_deltaTime)
{
	m_updateTimer += p_deltaTime;

	if (m_updateTimer >= m_updateFrequency)
	{
		m_fps = static_cast<uint16_t>(1.0f / p_deltaTime);
		m_updateTimer = 0.0f;
	}

	ShowFPS();
}

void SimplexEngine::Scripts::GlobalScripts::FPSCounter::ShowFPS()
{
	std::string textContent = std::to_string(m_fps) + " FPS";

	m_userInterface.AddText({ textContent, m_userInterface.topRightAnchor, Data::EFontSize::SMALL_FONT, Data::Color::White, Data::ETextHorizontalAlignment::ALIGN_RIGHT });
}