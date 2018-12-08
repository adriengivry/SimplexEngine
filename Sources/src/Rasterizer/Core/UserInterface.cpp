/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Core/UserInterface.h"

Rasterizer::Core::UserInterface::UserInterface(const Core::Window& p_window, const Rendering::Renderer& p_renderer) :
	m_window(p_window),
	m_renderer(p_renderer),
	width(m_window.GetWidth()),
	height(m_window.GetHeight()),
	topLeftAnchor(0, 0),
	topRightAnchor(width, 0),
	bottomLeftAnchor(0, height),
	bottomRightAnchor(width, height),
	centerAnchor(width / 2, height / 2)
{
	TTF_Init();
	LoadFonts();
}

void Rasterizer::Core::UserInterface::AddText(const Data::Text & p_text)
{
	m_texts.push(p_text);
}

void Rasterizer::Core::UserInterface::Draw()
{
	while (!m_texts.empty())
	{
		const Data::Text& text = m_texts.front();
		TTF_Font* toUse = text.fontSize == Data::EFontSize::NORMAL_FONT ? m_normalFont : (text.fontSize == Data::EFontSize::SMALL_FONT ? m_smallFont : m_bigFont);
		m_renderer.DrawText(text.content, toUse, { text.position.first, text.position.second}, text.color, text.horizontalAlign, text.verticalAlign);
		m_texts.pop();
	}
}

void Rasterizer::Core::UserInterface::LoadFonts()
{
	const char* fontPath = "resources/fonts/arial.ttf";
	m_smallFont = TTF_OpenFont(fontPath, 12);
	m_normalFont = TTF_OpenFont(fontPath, 18);
	m_bigFont = TTF_OpenFont(fontPath, 24);
}
