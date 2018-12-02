/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <SDL.h>

#include "Rasterizer/Utils/Clock.h"

void Rasterizer::Utils::Clock::Tick()
{
	uint32_t m_currentTime = SDL_GetTicks();
	m_deltaTime = (m_currentTime - m_lastTime) * 0.001f;
	m_lastTime = m_currentTime;

	m_elapsedTime += m_deltaTime;
}

float Rasterizer::Utils::Clock::GetDeltaTime() const
{
	return m_deltaTime;
}

float Rasterizer::Utils::Clock::GetFramerate() const
{
	return 1.0f / m_deltaTime;
}

float Rasterizer::Utils::Clock::GetElapsedTime() const
{
	return m_elapsedTime;
}
