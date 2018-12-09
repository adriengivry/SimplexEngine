/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H

#include <unordered_map>

#include <SDL.h>

#include "SimplexEngine/Inputs/EKey.h"
#include "SimplexEngine/Eventing/EventHandler.h"

namespace SimplexEngine::Inputs
{
	/**
	* The input manager is an easy way to check inputs
	*/
	class InputManager final
	{
	public:
		/**
		* Contructor of the InputManager
		* @param p_eventHandler
		*/
		InputManager(Eventing::EventHandler& p_eventHandler);

		/**
		* Update the input manager
		*/
		void Update();

		/**
		* Lock the mouse to the window
		*/
		void LockMouse() const;

		/**
		* Unlock the mouse from the window
		*/
		void UnlockMouse() const;

		/**
		* Check if the mouse is currently locked
		*/
		bool IsMouseLocked() const;

		/**
		* Check if the given key is currently down
		* @param p_key
		*/
		bool IsKeyDown(EKey p_key) const;

		/**
		* Check if the given key is currently up
		* @param p_key
		*/
		bool IsKeyUp(EKey p_key) const;

		/**
		* Check if the given key has been pressed during this frame
		* @param p_key
		*/
		bool HasKeyBeenPressed(EKey p_key) const;

		/**
		* Check if the given key has been released during this frame
		* @param p_keyCode
		*/
		bool HasKeyBeenReleased(EKey p_key) const;

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
		std::pair<int, int> GetMouseMotion() const;

	private:
		std::unordered_map<EKey, bool> m_keyPressedEvents;
		std::unordered_map<EKey, bool> m_keyReleasedEvents;
		std::unordered_map<EKey, bool> m_keyStates;

		std::pair<int, int> m_cursorPosition;
		std::pair<int, int> m_mouseMotion;
	};
}

#endif // _INPUTMANAGER_H
