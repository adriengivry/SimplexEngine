/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include <iostream>

#include <SDL.h>

#include "SimplexEngine/Eventing/EventHandler.h"

void SimplexEngine::Eventing::EventHandler::HandleEvents(const Core::Window& p_window)
{
	SDL_Event event;

	MouseMovedEvent.Invoke(std::make_pair(0, 0));

	Uint32 windowFlags = SDL_GetWindowFlags(p_window.GetSDLWindow());

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			QuitEvent.Invoke();
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				QuitEvent.Invoke();
			break;

		case SDL_MOUSEMOTION:
			MouseMovedEvent.Invoke(std::make_pair(event.motion.xrel, event.motion.yrel));
			break;

		default:
			break;
		}
	}
}
