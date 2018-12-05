/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Core/Window.h"

Rasterizer::Core::Window::Window(const std::string& p_title, uint16_t p_width, uint16_t p_height) :
	m_width(p_width),
	m_height(p_height),
	m_title(p_title),
	m_aspectRatio(static_cast<float>(p_width) / static_cast<float>(p_height)),
	m_windowState(EWindowState::NONE), m_sdlWindow(nullptr)
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
		m_glContext = SDL_GL_CreateContext(m_sdlWindow);
		m_windowState = EWindowState::OK;
	}
}

Rasterizer::Core::Window::~Window()
{
	SDL_DestroyWindow(m_sdlWindow);
	SDL_Quit();
}

bool Rasterizer::Core::Window::IsOpened() const
{
	return m_windowState == EWindowState::OK;
}

Rasterizer::Core::EWindowState Rasterizer::Core::Window::GetWindowState() const
{
	return m_windowState;
}

SDL_Window * Rasterizer::Core::Window::GetSDLWindow() const
{
	return m_sdlWindow;
}

SDL_GLContext Rasterizer::Core::Window::GetGLContext() const
{
	return m_glContext;
}

uint32_t Rasterizer::Core::Window::GetWidth() const
{
	return m_width;
}

uint32_t Rasterizer::Core::Window::GetHeight() const
{
	return m_height;
}

float Rasterizer::Core::Window::GetAspectRatio() const
{
	return m_aspectRatio;
}

std::pair<uint16_t, uint16_t> Rasterizer::Core::Window::GetSize() const
{
	return std::pair(m_width, m_height);
}

bool Rasterizer::Core::Window::IsPointInWindow(const std::pair<uint32_t, uint32_t>& p_point) const
{
	return p_point.first >= 0 && p_point.second >= 0 && p_point.first < m_width && p_point.second < m_height;
}
