/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _USERINTERFACE_H
#define _USERINTERFACE_H

#include <queue>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Rasterizer/Context/Window.h"
#include "Rasterizer/Core/Renderer.h"
#include "Rasterizer/Data/Text.h"

namespace Rasterizer::Core
{
	/**
	* A simple class using SDL_ttf to render things on screens
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
		* Add a text to queue
		* @param p_text
		*/
		void AddText(const Data::Text& p_text);

		/**
		* Draw
		*/
		void Draw();

	private:
		const Context::Window& m_window;
		const Core::Renderer& m_renderer;

	public:
		/* Usefull values that can be used to get main points of the UI canvas */
		const int16_t width;
		const int16_t height;
		const std::pair<int16_t, int16_t> topLeftAnchor;
		const std::pair<int16_t, int16_t> topRightAnchor;
		const std::pair<int16_t, int16_t> bottomLeftAnchor;
		const std::pair<int16_t, int16_t> bottomRightAnchor;
		const std::pair<int16_t, int16_t> centerAnchor;

	private:

		TTF_Font* m_smallFont;
		TTF_Font* m_normalFont;
		TTF_Font* m_bigFont;

		std::queue<Data::Text> m_texts;
	};
}

#endif // _USERINTERFACE_H