/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _TEXTUREBUFFER_H
#define _TEXTUREBUFFER_H

#include "SimplexEngine/Buffers/Buffer2D.h"
#include "SimplexEngine/Data/Color.h"

namespace SimplexEngine::Buffers
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
		TextureBuffer(struct SDL_Renderer* p_sdlRenderer, uint32_t p_width, uint32_t p_height, uint32_t p_pixelFormat, uint32_t p_textureAccess);

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
		uint32_t GetPixel(uint32_t p_x, uint32_t p_y) const;

		/**
		* Return the wrapped SDL_Texture*
		*/
		struct SDL_Texture* GetSDLTexture() const;

		/**
		* Update texture data on the GPU. This must be called at most one per frame.
		* This is a very slow method, be careful!
		*/
		void SendDataToGPU();

	private:
		struct SDL_Texture* m_sdlTexture;
		const uint32_t m_pixelBufferRowSize;
	};
}

#endif // _TEXTUREBUFFER_H