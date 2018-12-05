/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <iostream>

#include "Rasterizer/Scripts/SFPSCounter.h"
#include "Rasterizer/Utils/IniIndexer.h"

Rasterizer::Scripts::SFPSCounter::SFPSCounter(Core::UserInterface& p_userInterface) :
	m_userInterface(p_userInterface),
	m_logTimer(Utils::IniIndexer::Application->Get<float>("fps_log_frequency")),
	m_logFrequency(Utils::IniIndexer::Application->Get<float>("fps_log_frequency")),
	m_fps(0)
{
}

void Rasterizer::Scripts::SFPSCounter::Update(float p_deltaTime)
{
	m_logTimer += p_deltaTime;

	if (m_logTimer >= Utils::IniIndexer::Application->Get<float>("fps_update_frequency"))
	{
		m_fps = static_cast<uint16_t>(1.0f / p_deltaTime);
		m_logTimer = 0.0f;
	}

	ShowFPS();
}

void Rasterizer::Scripts::SFPSCounter::ShowFPS()
{
	std::string textContent = std::to_string(m_fps) + " FPS";

	m_userInterface.AddText({ textContent, m_userInterface.topRightAnchor, Data::EFontSize::SMALL_FONT, Data::Color::White, Data::ETextHorizontalAlignment::ALIGN_RIGHT });
}