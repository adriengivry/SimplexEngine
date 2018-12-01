/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _EVENTHANDLER_H
#define _EVENTHANDLER_H

#include "Rasterizer/Context/Window.h"
#include "Rasterizer/Utils/Event.h"

namespace Rasterizer::Context
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
		Rasterizer::Utils::Event<> SDLQuitEvent;
	};
}

#endif // _EVENTHANDLER_H