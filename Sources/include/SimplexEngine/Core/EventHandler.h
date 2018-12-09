/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _EVENTHANDLER_H
#define _EVENTHANDLER_H

#include "SimplexEngine/Core/Window.h"
#include "SimplexEngine/Utils/Event.h"

namespace SimplexEngine::Core
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
		void HandleEvents(const Window& p_window);

	public:
		/* Events */
		SimplexEngine::Utils::Event<>							SDLQuitEvent;
		SimplexEngine::Utils::Event<std::pair<int, int>>		SDLMouseMovedEvent;
	};
}

#endif // _EVENTHANDLER_H