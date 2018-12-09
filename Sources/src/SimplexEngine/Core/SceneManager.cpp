/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Core/SceneManager.h"

SimplexEngine::Scenes::AScene & SimplexEngine::Core::SceneManager::GetSceneByName(const std::string & p_sceneName)
{
	return *m_scenes.at(p_sceneName);
}

void SimplexEngine::Core::SceneManager::LoadScene(const std::string& p_sceneName)
{
	/* Unload the current scene if any */
	if (m_currentScene)
		m_currentScene->Unload();

	Scenes::AScene& newScene = GetSceneByName(p_sceneName);
	m_currentScene = &newScene;
	newScene.Load();
}

SimplexEngine::Scenes::AScene* SimplexEngine::Core::SceneManager::GetCurrentScene()
{
	return m_currentScene;
}
