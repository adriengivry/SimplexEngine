/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <SDL.h>

#include "Rasterizer/Context/Window.h"

Rasterizer::Context::Window::Window(const std::string& p_title, uint16_t p_width, uint16_t p_height) :
	m_width(p_width), m_height(p_height), m_title(p_title), m_windowState(EWindowState::NONE), m_sdlWindow(nullptr)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
	{
		/* SDL Initialization failed */
		m_windowState = EWindowState::INIT_FAILED;
	}
	else
	{
		/* SDL Initiailization succeed*/
		m_sdlWindow = SDL_CreateWindow(p_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, static_cast<int>(m_width), static_cast<int>(m_height), 0);
		m_windowState = EWindowState::OK;
	}
}

Rasterizer::Context::Window::~Window()
{
	SDL_DestroyWindow(m_sdlWindow);
	SDL_Quit();
}

bool Rasterizer::Context::Window::IsOpened() const
{
	return m_windowState == EWindowState::OK;
}

Rasterizer::Context::EWindowState Rasterizer::Context::Window::GetWindowState() const
{
	return m_windowState;
}

SDL_Window * Rasterizer::Context::Window::GetSDLWindow() const
{
	return m_sdlWindow;
}

uint32_t Rasterizer::Context::Window::GetWidth() const
{
	return m_width;
}

uint32_t Rasterizer::Context::Window::GetHeight() const
{
	return m_height;
}

std::pair<uint16_t, uint16_t> Rasterizer::Context::Window::GetSize() const
{
	return std::pair(m_width, m_height);
}

bool Rasterizer::Context::Window::IsPointInWindow(const AltMath::Vector2i & p_point)
{
	return p_point.x >= 0 && p_point.y >= 0 && p_point.x <= m_width && p_point.y <= m_height;
}
