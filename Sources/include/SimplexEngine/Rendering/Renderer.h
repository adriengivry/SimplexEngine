/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _RENDERER_H
#define _RENDERER_H

#include <vector>
#include <SDL_ttf.h>

#include "SimplexEngine/Core/Window.h"
#include "SimplexEngine/Data/Color.h"
#include "SimplexEngine/Data/ETextAlignment.h"
#include "SimplexEngine/Buffers/TextureBuffer.h"

namespace SimplexEngine::Rendering
{
	class Renderer final
	{
	public:
		/**
		* Create the renderer
		* @param p_window
		*/
		Renderer(const Core::Window& p_window);

		/**
		* Return the SDL renderer wrapped by this instance
		*/
		struct SDL_Renderer* GetSDLRenderer() const;

		/**
		* Render a text on the screen
		* @param p_text
		* @param p_font
		* @param p_position
		* @param p_color
		* @param p_horizontalAlign
		* @param p_verticalAlign
		*/
		void DrawText(const std::string& p_text, TTF_Font* p_font, const std::pair<int, int>& p_position, const Data::Color& p_color = Data::Color::White, Data::ETextHorizontalAlignment = Data::ETextHorizontalAlignment::ALIGN_LEFT, Data::ETextVerticalAlignment p_verticalAlign = Data::ETextVerticalAlignment::ALIGN_TOP) const;

		/**
		* Draw a texture on the screen
		*/
		void DrawTextureBufferContent(const Buffers::TextureBuffer& p_texture);

		/**
		* Actually render things on screen
		*/
		void Render();

	private:
		uint16_t m_bufferWidth;
		uint16_t m_bufferHeight;

		struct SDL_Renderer* m_sdlRenderer;
	};
}

#endif // _RENDERER_H