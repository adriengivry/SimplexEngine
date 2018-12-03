/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <iostream>

#include "Rasterizer/Scripts/SFPSCounter.h"
#include "Rasterizer/Utils/IniIndexer.h"

Rasterizer::Scripts::SFPSCounter::SFPSCounter() :
	m_logTimer(0.0f),
	m_logFrequency(Utils::IniIndexer::Application->Get<float>("fps_log_frequency"))
{
}

void Rasterizer::Scripts::SFPSCounter::Update(float p_deltaTime)
{
	m_logTimer += p_deltaTime;

	if (m_logTimer >= m_logFrequency)
	{
		std::cout << "FPS: " << 1.0f / p_deltaTime << std::endl;
		m_logTimer = 0.0f;
	}
}
