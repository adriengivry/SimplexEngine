/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _USERINTERFACE_H
#define _USERINTERFACE_H

#include <queue>

#include <SDL.h>
#include <SDL_ttf.h>

#include "SimplexEngine/Core/Window.h"
#include "SimplexEngine/Rendering/Renderer.h"
#include "SimplexEngine/Data/Text.h"

namespace SimplexEngine::Rendering
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
		UserInterface(const Core::Window& p_window, const Rendering::Renderer& p_renderer);

		/**
		* Add a text to queue. The text will get renderer at the end of the frame
		* @param p_text
		*/
		void AddText(const Data::Text& p_text);

		/**
		* Draw every queued texts to the screen
		*/
		void Draw();

	private:
		void LoadFonts();

		const Core::Window& m_window;
		const Rendering::Renderer& m_renderer;

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