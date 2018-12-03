/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H

#include <unordered_map>

#include <SDL.h>

namespace Rasterizer::Context
{
	class InputManager final
	{
	public:
		/**
		* Contructor of the InputManager
		*/
		InputManager() = default;

		/**
		* Update the input manager
		*/
		void Update();

		/**
		* Check if the given key is pressed
		* @param p_key (SDL Key Code)
		*/
		bool IsKeyPressed(int p_keyCode) const;

		/**
		* Check if the given key has been pressed during this frame
		* @param p_key (SDL Key Code)
		*/
		bool IsKeyEventOccured(int p_keyCode) const;

	private:
		std::unordered_map<int, bool> m_keyEvents;
		std::unordered_map<int, bool> m_keyStates;
	};
}

#endif // _INPUTMANAGER_H
