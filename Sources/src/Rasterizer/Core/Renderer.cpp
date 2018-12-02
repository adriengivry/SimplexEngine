/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <SDL.h>

#include "Rasterizer/Core/Renderer.h"

Rasterizer::Core::Renderer::Renderer(const Context::Window& p_window)
{
	auto[windowWidth, windowHeight] = p_window.GetSize();

	m_sdlRenderer = SDL_CreateRenderer(p_window.GetSDLWindow(), -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	m_finalTexture = SDL_CreateTexture(m_sdlRenderer, SDL_PIXELFORMAT_ARGB32, SDL_TEXTUREACCESS_STREAMING, static_cast<int>(windowWidth), static_cast<int>(windowHeight));
}

void Rasterizer::Core::Renderer::InitializePixelBufferSize(std::pair<uint16_t, uint16_t> p_windowSize)
{
	m_bufferWidth = p_windowSize.first;
	m_bufferHeight = p_windowSize.second;

	size_t bufferSize = m_bufferWidth * m_bufferHeight;

	m_pixelBuffer.resize(bufferSize);
	m_depthBuffer.resize(bufferSize);
}

void Rasterizer::Core::Renderer::ClearPixelBuffer()
{
	memset(m_depthBuffer.data(), 0, m_depthBuffer.size() * sizeof(decltype(m_depthBuffer)::value_type));
	memset(m_pixelBuffer.data(), 0, m_pixelBuffer.size() * sizeof(decltype(m_pixelBuffer)::value_type));
}

void Rasterizer::Core::Renderer::SetPixel(uint16_t p_x, uint16_t p_y, const Data::Color& p_color)
{
	m_pixelBuffer[p_y * m_bufferWidth + p_x] = p_color.Pack();
}

uint32_t Rasterizer::Core::Renderer::GetColor(uint16_t p_x, uint16_t p_y)
{
	return m_pixelBuffer[p_y * m_bufferWidth + p_x];
}

void Rasterizer::Core::Renderer::SetDepth(uint16_t p_x, uint16_t p_y, float p_depth)
{
	m_depthBuffer[p_y * m_bufferWidth + p_x] = p_depth;
}

float Rasterizer::Core::Renderer::GetDepth(uint16_t p_x, uint16_t p_y)
{
	return m_depthBuffer[p_y * m_bufferWidth + p_x];
}

void Rasterizer::Core::Renderer::GenerateFinalTexture()
{
	size_t bufferRowSize = m_bufferWidth * sizeof(decltype(m_pixelBuffer)::value_type);
	SDL_UpdateTexture(m_finalTexture, nullptr, m_pixelBuffer.data(), static_cast<int>(bufferRowSize));
}

void Rasterizer::Core::Renderer::DrawFinalTexture()
{
	SDL_RenderCopy(m_sdlRenderer, m_finalTexture, nullptr, nullptr);
}

void Rasterizer::Core::Renderer::Render()
{
	SDL_RenderPresent(m_sdlRenderer);
}
