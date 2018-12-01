/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _RENDERER_H
#define _RENDERER_H

#include <vector>

#include <SDL.h>

#include "Rasterizer/Context/Window.h"
#include "Rasterizer/Data/Color.h"

namespace Rasterizer::Core
{
	class Renderer final
	{
	public:
		/**
		* Create the renderer
		* @param p_window
		*/
		Renderer(const Context::Window& p_window);

		/**
		* Defines a size of the pixel buffer calculated with the window width and height.
		* This method must be called everytime the window size changes
		* @param p_windowSize
		*/
		void InitializePixelBufferSize(std::pair<uint16_t, uint16_t> p_windowSize);

		/**
		* Clear the pixel buffer
		*/
		void ClearPixelBuffer();

		/**
		* Modify a pixel on the screen
		* @param p_x
		* @param p_y
		* @param p_color
		*/
		void SetPixel(uint16_t p_x, uint16_t p_y, const Data::Color& p_color);

		/**
		* Generate the final texture using the current pixel buffer
		*/
		void GenerateFinalTexture();

		/**
		* Draw the final texture on the screen
		*/
		void DrawFinalTexture();

		/**
		* Actually render things on screen
		*/
		void Render();

	private:
		uint16_t m_bufferWidth;
		uint16_t m_bufferHeight;

		SDL_Renderer* m_sdlRenderer;
		SDL_Texture* m_finalTexture;
		std::vector<uint32_t> m_pixelBuffer;
	};
}

#endif // _RENDERER_H