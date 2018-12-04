/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Context/InputManager.h"

Rasterizer::Context::InputManager::InputManager(EventHandler& p_eventHandler)
{
	p_eventHandler.SDLMouseMovedEvent.AddListener(std::bind(&InputManager::OnMouseMotion, this, std::placeholders::_1));
}

void Rasterizer::Context::InputManager::Update()
{
	m_keyEvents.clear();

	m_mouseMotion.first = 0;
	m_mouseMotion.second = 0;

	SDL_PumpEvents();

	int keyCount;
	const Uint8* keyboardState = SDL_GetKeyboardState(&keyCount);

	for (int i = 0; i < keyCount; ++i)
	{
		bool keyState = keyboardState[i];
		m_keyEvents[i] = keyState && !m_keyStates[i]; /* Boolean = the key wasn't pressed and is now pressed */
		m_keyStates[i] = keyState;
	}

	SDL_GetMouseState(&m_cursorPosition.first, &m_cursorPosition.second);
}

bool Rasterizer::Context::InputManager::IsKeyPressed(int p_key) const
{
	return m_keyStates.find(p_key) != m_keyStates.end() && m_keyStates.at(p_key);
}

bool Rasterizer::Context::InputManager::IsKeyEventOccured(int p_key) const
{
	return m_keyEvents.find(p_key) != m_keyEvents.end() && m_keyEvents.at(p_key);
}

const std::pair<int, int>& Rasterizer::Context::InputManager::GetCursorPosition() const
{
	return m_cursorPosition;
}

void Rasterizer::Context::InputManager::OnMouseMotion(std::pair<int, int> p_motion)
{
	m_mouseMotion = p_motion;
}

std::pair<int, int> Rasterizer::Context::InputManager::GetMouseMotion() const
{
	return m_mouseMotion;
}
