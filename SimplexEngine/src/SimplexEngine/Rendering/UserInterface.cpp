/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include <SDL.h>
#include <SDL_ttf.h>

#include "SimplexEngine/Rendering/UserInterface.h"

SimplexEngine::Rendering::UserInterface::UserInterface(const Windowing::Window& p_window, const Rendering::Renderer& p_renderer, const Settings::UserInterfaceSettings& p_userInterfaceSettings) :
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
	LoadFonts(p_userInterfaceSettings.defaultFontPath, p_userInterfaceSettings.defaultFontSize, p_userInterfaceSettings.scaleWithScreenWidth);
}

void SimplexEngine::Rendering::UserInterface::AddText(const Data::Text & p_text)
{
	m_texts.push(p_text);
}

void SimplexEngine::Rendering::UserInterface::Draw()
{
	while (!m_texts.empty())
	{
		const Data::Text& text = m_texts.front();
		TTF_Font* toUse = text.fontSize == Data::EFontSize::NORMAL_FONT ? m_normalFont : (text.fontSize == Data::EFontSize::SMALL_FONT ? m_smallFont : m_bigFont);
		m_renderer.DrawText(text.content, toUse, { text.position.first, text.position.second}, text.color, text.horizontalAlign, text.verticalAlign);
		m_texts.pop();
	}
}

void SimplexEngine::Rendering::UserInterface::LoadFonts(const std::string& p_fontPath, uint32_t p_defaultFontSize, bool p_scaleWithScreenWidth)
{
	float fontSizeRatio = p_scaleWithScreenWidth ? m_window.GetWidth() / 1280.0f : 1.0f;

	m_smallFont = TTF_OpenFont(p_fontPath.c_str(), static_cast<int>(p_defaultFontSize * fontSizeRatio * 0.75f));
	m_normalFont = TTF_OpenFont(p_fontPath.c_str(), static_cast<int>(p_defaultFontSize * fontSizeRatio));
	m_bigFont = TTF_OpenFont(p_fontPath.c_str(), static_cast<int>(p_defaultFontSize * fontSizeRatio * 1.25f));
}
