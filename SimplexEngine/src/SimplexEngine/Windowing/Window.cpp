/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include <SDL.h>

#include "SimplexEngine/Windowing/Window.h"

SimplexEngine::Windowing::Window::Window(const Settings::WindowSettings& p_windowSettings) :
	m_initialWidth(p_windowSettings.width),
	m_initialHeight(p_windowSettings.height),
	m_width(m_initialWidth),
	m_height(m_initialHeight),
	m_halfWidth(m_width / 2),
	m_halfHeight(m_halfHeight / 2),
	m_aspectRatio(static_cast<float>(m_width) / static_cast<float>(m_height)),
	m_title(p_windowSettings.title),
	m_windowState(EWindowState::NONE),
	m_sdlWindow(nullptr)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
	{
		m_windowState = EWindowState::INIT_FAILED;
	}
	else
	{
		int width = static_cast<int>(m_width);
		int height = static_cast<int>(m_height);

		m_sdlWindow = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, p_windowSettings.fullScreen ? SDL_WINDOW_FULLSCREEN : 0);

		if (m_sdlWindow)
		{
			m_windowState = EWindowState::OK;

			/* Fullscreen can alter window final size, so we update the size if we are in fullscreen mode */
			if (p_windowSettings.fullScreen)
				UpdateWindowSizeFromSDL();
		}
	}
}

SimplexEngine::Windowing::Window::~Window()
{
	SDL_DestroyWindow(m_sdlWindow);
	SDL_Quit();
}

void SimplexEngine::Windowing::Window::UpdateWindowSizeFromSDL()
{
	/* Find the real window size (Fullscreen can alter window size) */
	int realWidth;
	int realHeight;
	SDL_GetWindowSize(m_sdlWindow, &realWidth, &realHeight);

	/* Update width, height, halfWidth, halfHeight with real window size */
	m_width = static_cast<uint32_t>(realWidth);
	m_height = static_cast<uint32_t>(realHeight);
	m_halfWidth = m_width / 2;
	m_halfHeight = m_height / 2;

	/* Update the aspect ratio with new width and height */
	m_aspectRatio = static_cast<float>(m_width) / static_cast<float>(m_height);
}

bool SimplexEngine::Windowing::Window::IsOpened() const
{
	return m_windowState == EWindowState::OK;
}

SimplexEngine::Windowing::EWindowState SimplexEngine::Windowing::Window::GetWindowState() const
{
	return m_windowState;
}

SDL_Window * SimplexEngine::Windowing::Window::GetSDLWindow() const
{
	return m_sdlWindow;
}

uint32_t SimplexEngine::Windowing::Window::GetInitialWidth() const
{
	return m_initialWidth;
}

uint32_t SimplexEngine::Windowing::Window::GetInitialHeight() const
{
	return m_initialHeight;
}

uint32_t SimplexEngine::Windowing::Window::GetWidth() const
{
	return m_width;
}

uint32_t SimplexEngine::Windowing::Window::GetHeight() const
{
	return m_height;
}

int32_t SimplexEngine::Windowing::Window::GetWidthSigned() const
{
	return static_cast<int32_t>(m_width);
}

int32_t SimplexEngine::Windowing::Window::GetHeightSigned() const
{
	return static_cast<int32_t>(m_height);
}

int32_t SimplexEngine::Windowing::Window::GetHalfWidth() const
{
	return m_halfWidth;
}

int32_t SimplexEngine::Windowing::Window::GetHalfHeight() const
{
	return m_halfHeight;
}

float SimplexEngine::Windowing::Window::GetAspectRatio() const
{
	return m_aspectRatio;
}

std::pair<uint32_t, uint32_t> SimplexEngine::Windowing::Window::GetSize() const
{
	return std::pair(m_width, m_height);
}

std::pair<int32_t, int32_t> SimplexEngine::Windowing::Window::GetSizeSigned() const
{
	return std::pair(static_cast<int32_t>(m_width), static_cast<int32_t>(m_height));
}

bool SimplexEngine::Windowing::Window::IsPointInWindow(const std::pair<int32_t, int32_t>& p_point) const
{
	return p_point.first >= 0 && p_point.second >= 0 && p_point.first < GetWidthSigned() && p_point.second < GetHeightSigned();
}
