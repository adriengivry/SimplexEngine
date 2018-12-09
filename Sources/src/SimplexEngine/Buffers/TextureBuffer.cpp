/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Buffers/TextureBuffer.h"

SimplexEngine::Buffers::TextureBuffer::TextureBuffer(SDL_Renderer * p_sdlRenderer, uint32_t p_width, uint32_t p_height, Uint32 p_pixelFormat, SDL_TextureAccess p_textureAccess) :
	Buffer2D(p_width, p_height),
	m_pixelBufferRowSize(p_width * sizeof(uint32_t))
{
	m_sdlTexture = SDL_CreateTexture(p_sdlRenderer, p_pixelFormat, p_textureAccess, static_cast<int>(width), static_cast<int>(height));
}

SimplexEngine::Buffers::TextureBuffer::~TextureBuffer()
{
	SDL_DestroyTexture(m_sdlTexture);
}

void SimplexEngine::Buffers::TextureBuffer::SendDataToGPU()
{
	SDL_UpdateTexture(m_sdlTexture, nullptr, data, m_pixelBufferRowSize);
}

void SimplexEngine::Buffers::TextureBuffer::SetPixel(uint32_t p_x, uint32_t p_y, const Data::Color& p_color)
{
	SetElement(p_x, p_y, p_color.Pack());
}

uint32_t SimplexEngine::Buffers::TextureBuffer::GetPixel(uint32_t p_x, uint32_t p_y)
{
	return GetElement(p_x, p_y);
}

SDL_Texture * SimplexEngine::Buffers::TextureBuffer::GetSDLTexture() const
{
	return m_sdlTexture;
}
