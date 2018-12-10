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
		m_rasterizer.SetRasterizationDrawMode(FindNextDrawMode());

	if (m_inputManager.HasKeyBeenPressed(Inputs::EKey::KEY_B))
		m_rasterizer.SetRasterizationCullingwMode(FindNextCullingMode());
}

SimplexEngine::Rendering::ERasterizationDrawMode SimplexEngine::Scripts::GlobalScripts::RasterizationModeSelector::FindNextDrawMode()
{
	return static_cast<Rendering::ERasterizationDrawMode>((static_cast<int>(m_rasterizer.GetRasterizationDrawMode()) + 1) % (static_cast<int>(Rendering::ERasterizationDrawMode::WIREFRAME) + 1));
}

SimplexEngine::Rendering::ERasterizationCullingMode SimplexEngine::Scripts::GlobalScripts::RasterizationModeSelector::FindNextCullingMode()
{
	return static_cast<Rendering::ERasterizationCullingMode>((static_cast<int>(m_rasterizer.GetRasterizationCullingMode()) + 1) % (static_cast<int>(Rendering::ERasterizationCullingMode::FRONTFACE) + 1));
}
