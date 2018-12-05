/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <SDL.h>

#include "Rasterizer/Core/EventHandler.h"

void Rasterizer::Core::EventHandler::HandleEvents(const Window& p_window)
{
	SDL_Event event;

	SDLMouseMovedEvent.Invoke(std::make_pair(0, 0));

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			SDLQuitEvent.Invoke();
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				SDLQuitEvent.Invoke();
			break;

		case SDL_MOUSEMOTION:
			SDLMouseMovedEvent.Invoke(std::make_pair(event.motion.xrel, event.motion.yrel));
			break;

		default:
			break;
		}
	}
}
