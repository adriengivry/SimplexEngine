/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Inputs/InputManager.h"

SimplexEngine::Inputs::InputManager::InputManager(Eventing::EventHandler& p_eventHandler)
{
	p_eventHandler.MouseMovedEvent.AddListener(std::bind(&InputManager::OnMouseMotion, this, std::placeholders::_1));
}

void SimplexEngine::Inputs::InputManager::Update()
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
		EKey key = static_cast<EKey>(i);

		bool keyState = keyboardState[i];
		m_keyPressedEvents[key] = keyState && !m_keyStates[key];	/* The key wasn't pressed and is now pressed */
		m_keyReleasedEvents[key] = !keyState && m_keyStates[key];	/* The key was pressed and is now not pressed */
		m_keyStates[key] = keyState;								/* Save the current state of the key (True for pressed, false for realeased) */
	}

	SDL_GetMouseState(&m_cursorPosition.first, &m_cursorPosition.second);
}

void SimplexEngine::Inputs::InputManager::LockMouse() const
{
	if (!IsMouseLocked())
		SDL_SetRelativeMouseMode(SDL_TRUE);
}

void SimplexEngine::Inputs::InputManager::UnlockMouse() const
{
	if (IsMouseLocked())
		SDL_SetRelativeMouseMode(SDL_FALSE);
}

bool SimplexEngine::Inputs::InputManager::IsMouseLocked() const
{
	return SDL_GetRelativeMouseMode() == SDL_TRUE;
}

bool SimplexEngine::Inputs::InputManager::IsKeyDown(EKey p_key) const
{
	return m_keyStates.at(p_key);
}

bool SimplexEngine::Inputs::InputManager::IsKeyUp(EKey p_key) const
{
	return !m_keyStates.at(p_key);
}

bool SimplexEngine::Inputs::InputManager::HasKeyBeenPressed(EKey p_key) const
{
	return m_keyPressedEvents.at(p_key);
}

bool SimplexEngine::Inputs::InputManager::HasKeyBeenReleased(EKey p_key) const
{
	return m_keyReleasedEvents.at(p_key);
}

const std::pair<int, int>& SimplexEngine::Inputs::InputManager::GetCursorPosition() const
{
	return m_cursorPosition;
}

void SimplexEngine::Inputs::InputManager::OnMouseMotion(std::pair<int, int> p_motion)
{
	m_mouseMotion = p_motion;
}

std::pair<int, int> SimplexEngine::Inputs::InputManager::GetMouseMotion() const
{
	return m_mouseMotion;
}
