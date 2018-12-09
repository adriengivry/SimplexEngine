/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Core/InputManager.h"

SimplexEngine::Core::InputManager::InputManager(Eventing::EventHandler& p_eventHandler)
{
	p_eventHandler.MouseMovedEvent.AddListener(std::bind(&InputManager::OnMouseMotion, this, std::placeholders::_1));
}

void SimplexEngine::Core::InputManager::Update()
{
	m_keyPressedEvents.clear();
	m_keyReleasedEvents.clear();

	m_mouseMotion.first = 0;
	m_mouseMotion.second = 0;

	SDL_PumpEvents();

	int keyCount;
	const Uint8* keyboardState = SDL_GetKeyboardState(&keyCount);

	for (int i = 0; i < keyCount; ++i)
	{
		bool keyState = keyboardState[i];
		m_keyPressedEvents[i] = keyState && !m_keyStates[i];	/* The key wasn't pressed and is now pressed */
		m_keyReleasedEvents[i] = !keyState && m_keyStates[i];	/* The key was pressed and is now not pressed */
		m_keyStates[i] = keyState;								/* Save the current state of the key (True for pressed, false for realeased) */
	}

	SDL_GetMouseState(&m_cursorPosition.first, &m_cursorPosition.second);
}

void SimplexEngine::Core::InputManager::LockMouse() const
{
	if (!IsMouseLocked())
		SDL_SetRelativeMouseMode(SDL_TRUE);
}

void SimplexEngine::Core::InputManager::UnlockMouse() const
{
	if (IsMouseLocked())
		SDL_SetRelativeMouseMode(SDL_FALSE);
}

bool SimplexEngine::Core::InputManager::IsMouseLocked() const
{
	return SDL_GetRelativeMouseMode() == SDL_TRUE;
}

bool SimplexEngine::Core::InputManager::IsKeyDown(int p_keyCode) const
{
	return m_keyStates.at(p_keyCode);
}

bool SimplexEngine::Core::InputManager::IsKeyUp(int p_keyCode) const
{
	return !m_keyStates.at(p_keyCode);
}

bool SimplexEngine::Core::InputManager::HasKeyBeenPressed(int p_keyCode) const
{
	return m_keyPressedEvents.at(p_keyCode);
}

bool SimplexEngine::Core::InputManager::HasKeyBeenReleased(int p_keyCode) const
{
	return m_keyReleasedEvents.at(p_keyCode);
}

const std::pair<int, int>& SimplexEngine::Core::InputManager::GetCursorPosition() const
{
	return m_cursorPosition;
}

void SimplexEngine::Core::InputManager::OnMouseMotion(std::pair<int, int> p_motion)
{
	m_mouseMotion = p_motion;
}

std::pair<int, int> SimplexEngine::Core::InputManager::GetMouseMotion() const
{
	return m_mouseMotion;
}
