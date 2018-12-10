/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Scripts/GlobalScripts/RasterizationModeSelector.h"

SimplexEngine::Scripts::GlobalScripts::RasterizationModeSelector::RasterizationModeSelector(Rendering::Rasterizer & p_rasterizer, const Inputs::InputManager & p_inputManager) :
	m_rasterizer(p_rasterizer),
	m_inputManager(p_inputManager)
{
}

void SimplexEngine::Scripts::GlobalScripts::RasterizationModeSelector::Update(float p_deltaTime)
{
	if (m_inputManager.HasKeyBeenPressed(Inputs::EKey::KEY_M))
		m_rasterizer.SetRasterizationMode(FindNextMode());
}

SimplexEngine::Rendering::ERasterizationMode SimplexEngine::Scripts::GlobalScripts::RasterizationModeSelector::FindNextMode()
{
	return static_cast<Rendering::ERasterizationMode>((static_cast<int>(m_rasterizer.GetRasterizationMode()) + 1) % (static_cast<int>(Rendering::ERasterizationMode::WIREFRAME) + 1));
}
