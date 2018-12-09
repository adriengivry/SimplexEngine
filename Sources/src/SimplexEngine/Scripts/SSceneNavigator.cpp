/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Scripts/SSceneNavigator.h"

SimplexEngine::Scripts::SSceneNavigator::SSceneNavigator(Scenes::SceneManager & p_sceneManager, const Inputs::InputManager& p_inputManager) :
	m_sceneManager(p_sceneManager),
	m_inputManager(p_inputManager)
{
}

void SimplexEngine::Scripts::SSceneNavigator::Update(float p_deltaTime)
{
	if (m_inputManager.HasKeyBeenPressed(Inputs::EKey::KEY_1))
		m_sceneManager.LoadScene("Default");

	if (m_inputManager.HasKeyBeenPressed(Inputs::EKey::KEY_1))
		m_sceneManager.LoadScene("Test");
}
