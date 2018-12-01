/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Context/EventHandler.h"

void Rasterizer::Context::EventHandler::HandleEvents(const Window& p_window)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			SDLQuitEvent.Invoke();
			break;

		default:
			break;
		}
	}
}
