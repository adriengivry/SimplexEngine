/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Scripts/SSceneNavigator.h"

Rasterizer::Scripts::SSceneNavigator::SSceneNavigator(Core::SceneManager & p_sceneManager, const Core::InputManager& p_inputManager) :
	m_sceneManager(p_sceneManager),
	m_inputManager(p_inputManager)
{
}

void Rasterizer::Scripts::SSceneNavigator::Update(float p_deltaTime)
{
	if (m_inputManager.HasKeyBeenPressed(SDL_SCANCODE_1))
		m_sceneManager.LoadScene("Default");

	if (m_inputManager.HasKeyBeenPressed(SDL_SCANCODE_2))
		m_sceneManager.LoadScene("Test");
}