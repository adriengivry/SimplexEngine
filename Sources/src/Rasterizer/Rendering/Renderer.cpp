/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <SDL.h>

#include "Rasterizer/Rendering/Renderer.h"
#include "Rasterizer/Utils/IniIndexer.h"
#include "Rasterizer/Analytics/ProfilerSpy.h"

Rasterizer::Rendering::Renderer::Renderer(const Core::Window& p_window)
{
	auto[windowWidth, windowHeight] = p_window.GetSize();

	int flags = 0;

	if (Utils::IniIndexer::Rendering->Get<bool>("vertical_sync"))
		flags |= SDL_RENDERER_PRESENTVSYNC;

	if (Utils::IniIndexer::Rendering->Get<bool>("hardware_acceleration"))
		flags |= SDL_RENDERER_ACCELERATED;

	m_sdlRenderer = SDL_CreateRenderer(p_window.GetSDLWindow(), -1, flags);
}

SDL_Renderer* Rasterizer::Rendering::Renderer::GetSDLRenderer() const
{
	return m_sdlRenderer;
}

void Rasterizer::Rendering::Renderer::DrawText(const std::string & p_text, TTF_Font * p_font, const std::pair<int, int>& p_position, const Data::Color & p_color, Data::ETextHorizontalAlignment p_horizontalAlign, Data::ETextVerticalAlignment p_verticalAlign) const
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

void Rasterizer::Rendering::Renderer::DrawTextureBufferContent(const Buffers::TextureBuffer& p_texture)
{
	PROFILER_SPY("Renderer::DrawTexture");

	SDL_RenderCopy(m_sdlRenderer, p_texture.GetSDLTexture(), nullptr, nullptr);
}

void Rasterizer::Rendering::Renderer::Render()
{
	PROFILER_SPY("Renderer::Render");

	SDL_RenderPresent(m_sdlRenderer);
}