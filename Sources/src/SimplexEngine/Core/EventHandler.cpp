/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include <iostream>

#include <SDL.h>

#include "SimplexEngine/Core/EventHandler.h"

void SimplexEngine::Core::EventHandler::HandleEvents(const Window& p_window)
{
	SDL_Event event;

	SDLMouseMovedEvent.Invoke(std::make_pair(0, 0));

	Uint32 windowFlags = SDL_GetWindowFlags(p_window.GetSDLWindow());

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
