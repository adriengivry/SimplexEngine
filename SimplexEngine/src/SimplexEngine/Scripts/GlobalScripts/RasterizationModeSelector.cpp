/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Scripts/GlobalScripts/RasterizationModeSelector.h"

SimplexEngine::Scripts::GlobalScripts::RasterizationModeSelector::RasterizationModeSelector(Rendering::Rasterizer & p_rasterizer, const Inputs::InputManager & p_inputManager, Rendering::UserInterface& p_userInterface, bool p_displaySettings) :
	m_rasterizer(p_rasterizer),
	m_inputManager(p_inputManager),
	m_userInterface(p_userInterface),
	m_displaySettings(p_displaySettings)
{
}

void SimplexEngine::Scripts::GlobalScripts::RasterizationModeSelector::Update(float p_deltaTime)
{
	if (m_inputManager.HasKeyBeenPressed(Inputs::EKey::KEY_M))
		m_rasterizer.SetRasterizationDrawMode(FindNextDrawMode());

	if (m_inputManager.HasKeyBeenPressed(Inputs::EKey::KEY_B))
		m_rasterizer.SetRasterizationCullingwMode(FindNextCullingMode());

	if (m_displaySettings)
		DisplayCurrentSettings();
}

SimplexEngine::Rendering::ERasterizationDrawMode SimplexEngine::Scripts::GlobalScripts::RasterizationModeSelector::FindNextDrawMode()
{
	return static_cast<Rendering::ERasterizationDrawMode>((static_cast<int>(m_rasterizer.GetRasterizationDrawMode()) + 1) % (static_cast<int>(Rendering::ERasterizationDrawMode::WIREFRAME) + 1));
}

SimplexEngine::Rendering::ERasterizationCullingMode SimplexEngine::Scripts::GlobalScripts::RasterizationModeSelector::FindNextCullingMode()
{
	return static_cast<Rendering::ERasterizationCullingMode>((static_cast<int>(m_rasterizer.GetRasterizationCullingMode()) + 1) % (static_cast<int>(Rendering::ERasterizationCullingMode::FRONTFACE) + 1));
}

std::string SimplexEngine::Scripts::GlobalScripts::RasterizationModeSelector::GetDrawModeAsString()
{
	switch (m_rasterizer.GetRasterizationDrawMode())
	{
	case Rendering::ERasterizationDrawMode::DEFAULT:		return "DEFAULT";
	case Rendering::ERasterizationDrawMode::WIREFRAME:		return "WIREFRAME";
	}

	return "UNKNOWN";
}

std::string SimplexEngine::Scripts::GlobalScripts::RasterizationModeSelector::GetCullingwModeAsString()
{
	switch (m_rasterizer.GetRasterizationCullingMode())
	{
	case Rendering::ERasterizationCullingMode::DISABLED:		return "DISABLED";
	case Rendering::ERasterizationCullingMode::BACKFACE:		return "BACKFACE";
	case Rendering::ERasterizationCullingMode::FRONTFACE:		return "FRONTFACE";
	}

	return "UNKNOWN";
}

void SimplexEngine::Scripts::GlobalScripts::RasterizationModeSelector::DisplayCurrentSettings()
{
	Data::Text drawModeText;
	drawModeText.color = Data::Color::White;
	drawModeText.verticalAlign = Data::ETextVerticalAlignment::ALIGN_BOTTOM;
	drawModeText.horizontalAlign = Data::ETextHorizontalAlignment::ALIGN_RIGHT;
	drawModeText.fontSize = Data::EFontSize::SMALL_FONT;
	drawModeText.position = m_userInterface.bottomRightAnchor;
	drawModeText.position.second -= static_cast<int16_t>(2 * m_userInterface.vh);
	drawModeText.content = "Draw mode: " + GetDrawModeAsString();

	Data::Text cullingModeText;
	cullingModeText.color = Data::Color::White;
	cullingModeText.verticalAlign = Data::ETextVerticalAlignment::ALIGN_BOTTOM;
	cullingModeText.horizontalAlign = Data::ETextHorizontalAlignment::ALIGN_RIGHT;
	cullingModeText.fontSize = Data::EFontSize::SMALL_FONT;
	cullingModeText.position = m_userInterface.bottomRightAnchor;
	cullingModeText.content = "Culling mode: " + GetCullingwModeAsString();

	m_userInterface.AddText(drawModeText);
	m_userInterface.AddText(cullingModeText);
}
