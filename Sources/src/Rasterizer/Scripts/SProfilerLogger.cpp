/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <iostream>

#include "Rasterizer/Scripts/SProfilerLogger.h"
#include "Rasterizer/Utils/IniIndexer.h"

Rasterizer::Scripts::SProfilerLogger::SProfilerLogger(Rasterizer::Analytics::Profiler& p_profiler, const Context::InputManager& p_inputManager) :
	m_inputManager(p_inputManager),
	m_profiler(p_profiler),
	m_logTimer(0.0f)
{
}

void Rasterizer::Scripts::SProfilerLogger::Update(float p_deltaTime)
{
	if (m_profiler.IsEnabled())
	{
		m_logTimer += p_deltaTime;

		if (m_logTimer >= Utils::IniIndexer::Application->Get<float>("profiler_log_frequency"))
		{
			m_profiler.Log();
			m_profiler.ClearHistory();
			m_logTimer = 0.0f;
		}
	}

	if (m_inputManager.IsKeyEventOccured(SDL_SCANCODE_P))
	{
		m_profiler.ToggleEnable();
	}
}
