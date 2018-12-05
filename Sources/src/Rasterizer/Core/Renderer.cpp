/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <SDL.h>

#include "Rasterizer/Core/Renderer.h"
#include "Rasterizer/Utils/IniIndexer.h"
#include "Rasterizer/Analytics/ProfilerSpy.h"

Rasterizer::Core::Renderer::Renderer(const Core::Window& p_window)
{
	auto[windowWidth, windowHeight] = p_window.GetSize();

	int flags = 0;

	if (Utils::IniIndexer::Rendering->Get<bool>("vertical_sync"))
		flags |= SDL_RENDERER_PRESENTVSYNC;

	if (Utils::IniIndexer::Rendering->Get<bool>("hardware_acceleration"))
		flags |= SDL_RENDERER_ACCELERATED;

	m_sdlRenderer = SDL_CreateRenderer(p_window.GetSDLWindow(), -1, flags);
	m_finalTexture = SDL_CreateTexture(m_sdlRenderer, SDL_PIXELFORMAT_ARGB32, SDL_TEXTUREACCESS_STREAMING, static_cast<int>(windowWidth), static_cast<int>(windowHeight));
}

void Rasterizer::Core::Renderer::InitializePixelBufferSize(std::pair<uint16_t, uint16_t> p_windowSize)
{
	m_bufferWidth = p_windowSize.first;
	m_bufferHeight = p_windowSize.second;

	size_t bufferSize = m_bufferWidth * m_bufferHeight;

	m_pixelBufferSizeof = static_cast<uint32_t>(bufferSize * sizeof(decltype(m_pixelBuffer)::value_type));
	m_depthBufferSizeof = static_cast<uint32_t>(bufferSize * sizeof(decltype(m_depthBuffer)::value_type));

	m_pixelBufferRowSize = static_cast<int>(m_bufferWidth * sizeof(decltype(m_pixelBuffer)::value_type));

	m_pixelBuffer.resize(bufferSize);
	m_depthBuffer.resize(bufferSize);
}

void Rasterizer::Core::Renderer::DrawText(const std::string & p_text, TTF_Font * p_font, const std::pair<int, int>& p_position, const Data::Color & p_color, Data::ETextHorizontalAlignment p_horizontalAlign, Data::ETextVerticalAlignment p_verticalAlign) const
{
	PROFILER_SPY("Renderer::DrawText");
	SDL_Surface* surface = TTF_RenderText_Solid(p_font, p_text.c_str(), { p_color.r, p_color.g, p_color.b });

	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_sdlRenderer, surface);
	SDL_Rect bounds = surface->clip_rect;

	bounds.x += p_position.first;
	bounds.y += p_position.second;

	switch (p_horizontalAlign)
	{
	case Data::ETextHorizontalAlignment::ALIGN_RIGHT:
		bounds.x -= bounds.w;
		break;

	case Data::ETextHorizontalAlignment::ALIGN_CENTER:
		bounds.x -= bounds.w / 2;
		break;
	}

	switch (p_verticalAlign)
	{
	case Data::ETextVerticalAlignment::ALIGN_BOTTOM:
		bounds.y += bounds.h;
		break;

	case Data::ETextVerticalAlignment::ALIGN_CENTER:
		bounds.y -= bounds.h / 2;
		break;
	}

	SDL_RenderCopy(m_sdlRenderer, texture, nullptr, &bounds);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void Rasterizer::Core::Renderer::ClearPixelBuffer()
{
	PROFILER_SPY("Renderer::ClearPixelBuffer");

	memset(m_pixelBuffer.data(), 0, m_pixelBufferSizeof);
}

void Rasterizer::Core::Renderer::ClearDepthBuffer()
{
	PROFILER_SPY("Renderer::ClearDepthBuffer");

	memset(m_depthBuffer.data(), 0, m_depthBufferSizeof);
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
	float depth = m_depthBuffer[p_y * m_bufferWidth + p_x];
	return depth == 0.0f ? std::numeric_limits<float>::max() : depth;
}

void Rasterizer::Core::Renderer::GenerateFinalTexture()
{
	PROFILER_SPY("Renderer::GenerateFinalTexture");

	SDL_UpdateTexture(m_finalTexture, nullptr, m_pixelBuffer.data(), m_pixelBufferRowSize);
}

void Rasterizer::Core::Renderer::DrawFinalTexture()
{
	PROFILER_SPY("Renderer::DrawFinalTexture");

	SDL_RenderCopy(m_sdlRenderer, m_finalTexture, nullptr, nullptr);
}

void Rasterizer::Core::Renderer::Render()
{
	PROFILER_SPY("Renderer::Render");

	SDL_RenderPresent(m_sdlRenderer);
}
