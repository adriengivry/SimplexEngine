/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Scenes/SceneManager.h"

SimplexEngine::Scenes::SceneManager::SceneManager(SCENE_PARAMETERS) :
	m_window(p_window),
	m_eventHandler(p_eventHandler),
	m_userInterface(p_userInterface),
	m_inputManager(p_inputManager),
	m_meshManager(p_meshManager)
{
}

SimplexEngine::Scenes::AScene & SimplexEngine::Scenes::SceneManager::GetSceneByName(const std::string & p_sceneName)
{
	return *m_scenes.at(p_sceneName);
}

void SimplexEngine::Scenes::SceneManager::LoadScene(const std::string& p_sceneName)
{
	/* Unload the current scene if any */
	if (m_currentScene)
		m_currentScene->Unload();

	Scenes::AScene& newScene = GetSceneByName(p_sceneName);
	m_currentScene = &newScene;
	newScene.Load();
}

SimplexEngine::Scenes::AScene* SimplexEngine::Scenes::SceneManager::GetCurrentScene()
{
	return m_currentScene;
}

bool SimplexEngine::Scenes::SceneManager::HasCurrentScene() const
{
	return m_currentScene != nullptr;
}
