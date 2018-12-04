/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _USERINTERFACE_H
#define _USERINTERFACE_H

#include <SDL.h>
#include <SDL_ttf.h>

#include "Rasterizer/Context/Window.h"
#include "Rasterizer/Core/Renderer.h"

namespace Rasterizer::Core
{
	/**
	* A simple class using imgui to render things on screens
	*/
	class UserInterface final
	{
	public:
		/**
		* Constructor of the user interface
		* @param p_window
		*/
		UserInterface(const Context::Window& p_window, const Core::Renderer& p_renderer);

		/**
		* Update imgui components
		* @param p_deltaTime
		*/
		void Update(float p_deltaTime);

		/**
		* Draw
		*/
		void Draw();

	private:
		const Context::Window& m_window;
		const Core::Renderer& m_renderer;
		
		float m_framerateUpdateTimer;
		float m_framerateUpdateFrequency;

		uint16_t m_framerate;

		TTF_Font* m_arialFont;
	};
}

#endif // _USERINTERFACE_H