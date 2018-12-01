#include "Rasterizer/Utils/Clock.h"

void Rasterizer::Utils::Clock::Tick()
{
	uint32_t m_currentTime = SDL_GetTicks();
	m_deltaTime = (m_currentTime - m_lastTime) * 0.001f;
	m_lastTime = m_currentTime;
}

float Rasterizer::Utils::Clock::GetDeltaTime() const
{
	return m_deltaTime;
}
