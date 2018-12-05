/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _RENDERER_H
#define _RENDERER_H

#include <vector>
#include <SDL_ttf.h>

#include "Rasterizer/Core/Window.h"
#include "Rasterizer/Data/Color.h"
#include "Rasterizer/Data/ETextAlignment.h"

namespace Rasterizer::Core
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
		* Defines a size of the pixel buffer calculated with the window width and height.
		* This method must be called everytime the window size changes
		* @param p_windowSize
		*/
		void InitializePixelBufferSize(std::pair<uint16_t, uint16_t> p_windowSize);

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
		* Return the pixel color on the screen
		* @param p_x
		* @param p_y
		*/
		uint32_t GetColor(uint16_t p_x, uint16_t p_y);

		/**
		* Set a depth for the given screen coordinate
		* @param p_x
		* @param p_y
		* @param p_depth
		*/
		void SetDepth(uint16_t p_x, uint16_t p_y, float p_depth);

		/**
		* Return the depth buffer value for the screen coordinate
		* @param p_x
		* @param p_y
		*/
		float GetDepth(uint16_t p_x, uint16_t p_y);

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

		struct SDL_Renderer* m_sdlRenderer;
		struct SDL_Texture* m_finalTexture;
		std::vector<uint32_t> m_pixelBuffer;
		std::vector<float> m_depthBuffer;
	};
}

#endif // _RENDERER_H