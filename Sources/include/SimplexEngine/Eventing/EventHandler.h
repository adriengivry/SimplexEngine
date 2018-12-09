/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _EVENTHANDLER_H
#define _EVENTHANDLER_H

#include "SimplexEngine/Windowing/Window.h"
#include "SimplexEngine/Eventing/Event.h"

namespace SimplexEngine::Eventing
{
	/**
	* This class handles SDL events
	*/
	class EventHandler final
	{
	public:
		/**
		* Handle SDL events
		* @param p_window (Window that contains the actual SDL_Window)
		*/
		void HandleEvents(const Windowing::Window& p_window);

	public:
		/* Events */
		SimplexEngine::Eventing::Event<>						QuitEvent;
		SimplexEngine::Eventing::Event<std::pair<int, int>>		MouseMovedEvent;
	};
}

#endif // _EVENTHANDLER_H