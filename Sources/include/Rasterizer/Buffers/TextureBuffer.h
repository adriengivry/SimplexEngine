/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _TEXTUREBUFFER_H
#define _TEXTUREBUFFER_H

#include <SDL.h>

#include "Rasterizer/Buffers/Buffer2D.h"
#include "Rasterizer/Data/Color.h"

namespace Rasterizer::Buffers
{
	/**
	* The texture structure wraps the SDL_Texture and allow content modification easily
	*/
	struct TextureBuffer final : public Buffer2D<uint32_t>
	{
		/**
		* Constructor of the texture structure
		* @param p_sdlRenderer (Needed to generate the texture GPU side)
		* @param p_width
		* @param p_height
		* @param p_pixelFormat
		* @param p_textureAccess
		*/
		TextureBuffer(SDL_Renderer* p_sdlRenderer, uint32_t p_width, uint32_t p_height, Uint32 p_pixelFormat, SDL_TextureAccess p_textureAccess);

		/**
		* Texture destructor
		* Will free the memory reserved for SDL_Texutre
		*/
		virtual ~TextureBuffer();

		/**
		* Modify a pixel on the texture
		* @param p_x
		* @param p_y
		* @param p_color
		*/
		void SetPixel(uint32_t p_x, uint32_t p_y, const Data::Color& p_color);

		/**
		* Return the pixel color on the texture
		* @param p_x
		* @param p_y
		*/
		uint32_t GetPixel(uint32_t p_x, uint32_t p_y);

		/**
		* Return the wrapped SDL_Texture*
		*/
		SDL_Texture* GetSDLTexture() const;

		/**
		* Update texture data on the GPU. This must be called at most one per frame.
		* This is a very slow method, be careful!
		*/
		void SendDataToGPU();

	private:
		SDL_Texture* m_sdlTexture;
		const uint32_t m_pixelBufferRowSize;
	};
}

#endif // _TEXTUREBUFFER_H