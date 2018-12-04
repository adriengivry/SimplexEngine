/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Core/UserInterface.h"

Rasterizer::Core::UserInterface::UserInterface(const Context::Window& p_window, const Core::Renderer& p_renderer) :
	m_window(p_window),
	m_renderer(p_renderer)
{
	TTF_Init();
	m_arialFont = TTF_OpenFont("arial.ttf", 24);

	m_framerateUpdateFrequency = 0.5f;
	m_framerateUpdateTimer = m_framerateUpdateFrequency;
}

void Rasterizer::Core::UserInterface::Update(float p_deltaTime)
{
	m_framerateUpdateTimer += p_deltaTime;

	if (m_framerateUpdateTimer >= m_framerateUpdateFrequency)
	{
		m_framerate = static_cast<uint16_t>(1.0f / p_deltaTime);
		m_framerateUpdateTimer = 0.0f;
	}
}

void Rasterizer::Core::UserInterface::Draw()
{
	m_renderer.DrawText("FPS: " + std::to_string(m_framerate), m_arialFont, { 0, 0 }, Data::Color::Yellow);
}
