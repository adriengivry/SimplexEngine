/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _USERINTERFACE_H
#define _USERINTERFACE_H

#include <queue>

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Settings/UserInterfaceSettings.h"
#include "SimplexEngine/Windowing/Window.h"
#include "SimplexEngine/Rendering/Renderer.h"
#include "SimplexEngine/Data/Text.h"

namespace SimplexEngine::Rendering
{
	/**
	* A simple class using SDL_ttf to render things on screens
	*/
	class API_SIMPLEXENGINE UserInterface final
	{
	public:
		/**
		* Constructor of the user interface
		* @param p_window
		* @param p_renderer
		* @param p_userInterfaceSettings
		*/
		UserInterface(const Windowing::Window& p_window, const Rendering::Renderer& p_renderer, const Settings::UserInterfaceSettings& p_userInterfaceSettings);

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
		void LoadFonts(const std::string& p_fontPath, uint32_t p_defaultFontSize, bool p_scaleWithScreenWidth);

		const Windowing::Window& m_window;
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

		/* 1 vw = 1% of the viewport width */
		const float vw;

		/* 1 vh = 1% of the viewport height */
		const float vh;

	private:
		struct _TTF_Font* m_smallFont;
		struct _TTF_Font* m_normalFont;
		struct _TTF_Font* m_bigFont;

		std::queue<Data::Text> m_texts;
	};
}

#endif // _USERINTERFACE_H