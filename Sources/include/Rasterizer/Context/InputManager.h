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

#include "Rasterizer/Context/EventHandler.h"

namespace Rasterizer::Context
{
	class InputManager final
	{
	public:
		/**
		* Contructor of the InputManager
		* @param p_eventHandler
		*/
		InputManager(EventHandler& p_eventHandler);

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

		/**
		* Return the current cursor position
		*/
		const std::pair<int, int>& GetCursorPosition() const;

		/**
		* This method is fired when mouse move
		* @param p_motion
		*/
		void OnMouseMotion(std::pair<int, int> p_motion);

		/**
		* Return the current cursor position
		*/
		const std::pair<float, float>& GetMouseMotion() const;

	private:
		std::unordered_map<int, bool> m_keyEvents;
		std::unordered_map<int, bool> m_keyStates;

		std::pair<int, int> m_cursorPosition;
		std::pair<int, int> m_mouseMotion;
	};
}

#endif // _INPUTMANAGER_H
