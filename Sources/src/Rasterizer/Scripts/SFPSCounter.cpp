/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <iostream>

#include "Rasterizer/Scripts/SFPSCounter.h"
#include "Rasterizer/Utils/IniIndexer.h"

Rasterizer::Scripts::SFPSCounter::SFPSCounter(const Context::InputManager& p_inputManager) :
	m_inputManager(p_inputManager),
	m_logTimer(0.0f),
	m_logFrequency(Utils::IniIndexer::Application->Get<float>("fps_log_frequency"))
{
}

void Rasterizer::Scripts::SFPSCounter::Update(float p_deltaTime)
{
	if (Utils::IniIndexer::Application->Get<float>("fps_log_auto"))
	{
		m_logTimer += p_deltaTime;

		if (m_logTimer >= Utils::IniIndexer::Application->Get<float>("fps_log_frequency"))
		{
			PrintFPS(p_deltaTime);
			m_logTimer = 0.0f;
		}
	}

	if (m_inputManager.IsKeyEventOccured(SDL_SCANCODE_F))
		PrintFPS(p_deltaTime);
}

void Rasterizer::Scripts::SFPSCounter::PrintFPS(float p_deltaTime)
{
	std::cout << "FPS: " << 1.0f / p_deltaTime << std::endl;
}
