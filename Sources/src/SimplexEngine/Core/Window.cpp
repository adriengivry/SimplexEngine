/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Core/Window.h"

SimplexEngine::Core::Window::Window(const std::string& p_title, uint16_t p_width, uint16_t p_height) :
	m_width(p_width),
	m_height(p_height),
	m_halfWidth(p_width / 2),
	m_halfHeight(p_height / 2),
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

SimplexEngine::Core::Window::~Window()
{
	SDL_DestroyWindow(m_sdlWindow);
	SDL_Quit();
}

bool SimplexEngine::Core::Window::IsOpened() const
{
	return m_windowState == EWindowState::OK;
}

SimplexEngine::Core::EWindowState SimplexEngine::Core::Window::GetWindowState() const
{
	return m_windowState;
}

SDL_Window * SimplexEngine::Core::Window::GetSDLWindow() const
{
	return m_sdlWindow;
}

SDL_GLContext SimplexEngine::Core::Window::GetGLContext() const
{
	return m_glContext;
}

uint32_t SimplexEngine::Core::Window::GetWidth() const
{
	return m_width;
}

uint32_t SimplexEngine::Core::Window::GetHeight() const
{
	return m_height;
}

int32_t SimplexEngine::Core::Window::GetWidthSigned() const
{
	return static_cast<int32_t>(m_width);
}

int32_t SimplexEngine::Core::Window::GetHeightSigned() const
{
	return static_cast<int32_t>(m_height);
}

int32_t SimplexEngine::Core::Window::GetHalfWidth() const
{
	return m_halfWidth;
}

int32_t SimplexEngine::Core::Window::GetHalfHeight() const
{
	return m_halfHeight;
}

float SimplexEngine::Core::Window::GetAspectRatio() const
{
	return m_aspectRatio;
}

std::pair<uint32_t, uint32_t> SimplexEngine::Core::Window::GetSize() const
{
	return std::pair(m_width, m_height);
}

std::pair<int32_t, int32_t> SimplexEngine::Core::Window::GetSizeSigned() const
{
	return std::pair(static_cast<int32_t>(m_width), static_cast<int32_t>(m_height));
}

bool SimplexEngine::Core::Window::IsPointInWindow(const std::pair<int32_t, int32_t>& p_point) const
{
	return p_point.first >= 0 && p_point.second >= 0 && p_point.first < GetWidthSigned() && p_point.second < GetHeightSigned();
}
