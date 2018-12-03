/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <SDL.h>

#include "Rasterizer/Utils/Clock.h"

Rasterizer::Utils::Clock::Clock() : m_lastTime(std::chrono::steady_clock::now())
{
}

void Rasterizer::Utils::Clock::Tick()
{
	m_currentTime = std::chrono::steady_clock::now();
	m_deltaTime = static_cast<float>(std::chrono::duration_cast<std::chrono::nanoseconds>(m_currentTime - m_lastTime).count() * 0.000000001);
	m_lastTime = std::chrono::steady_clock::now();

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
