/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Context/InputManager.h"

void Rasterizer::Context::InputManager::Update()
{
	// m_keyEvents.clear();

	SDL_PumpEvents();

	int keyCount;
	const Uint8* keyboardState = SDL_GetKeyboardState(&keyCount);

	for (int i = 0; i < keyCount; ++i)
	{
		bool keyState = keyboardState[i];
		m_keyEvents[i] = keyState && !m_keyStates[i]; /* Boolean = the key wasn't pressed and is now pressed */
		m_keyStates[i] = keyState;
	}
}

bool Rasterizer::Context::InputManager::IsKeyPressed(int p_key) const
{
	return m_keyStates.find(p_key) != m_keyStates.end() && m_keyStates.at(p_key);
}

bool Rasterizer::Context::InputManager::IsKeyEventOccured(int p_key) const
{
	return m_keyEvents.find(p_key) != m_keyEvents.end() && m_keyEvents.at(p_key);
}
