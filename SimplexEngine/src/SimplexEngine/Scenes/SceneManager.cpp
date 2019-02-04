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

void SimplexEngine::Scenes::SceneManager::UnregisterScene(const std::string & p_sceneName)
{
	m_scenes.erase(p_sceneName);
}

SimplexEngine::Scenes::AScene & SimplexEngine::Scenes::SceneManager::GetSceneByName(const std::string & p_sceneName)
{
	return *m_scenes.at(p_sceneName);
}

void SimplexEngine::Scenes::SceneManager::LoadScene(const std::string& p_sceneName)
{
	/* Unload the current scene if any */
	if (m_currentScene)
	{
		m_currentScene->Unload();
		m_currentScene->ComponentAddedEvent.RemoveListener(m_sceneComponentAddListenerID);
		m_currentScene->ComponentRemovedEvent.RemoveListener(m_sceneComponentRemoveListenerID);
	}

	Scenes::AScene& newScene = GetSceneByName(p_sceneName);
	m_currentScene = &newScene;
	m_sceneComponentAddListenerID = newScene.ComponentAddedEvent.AddListener(std::bind(&SceneManager::OnComponentAdded, this, std::placeholders::_1));
	m_sceneComponentRemoveListenerID = newScene.ComponentRemovedEvent.AddListener(std::bind(&SceneManager::OnComponentRemoved, this, std::placeholders::_1));
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

void SimplexEngine::Scenes::SceneManager::OnComponentAdded(Components::AActorComponent& p_component)
{
	ComponentAddedEvent.Invoke(p_component);
}

void SimplexEngine::Scenes::SceneManager::OnComponentRemoved(Components::AActorComponent& p_component)
{
	ComponentRemovedEvent.Invoke(p_component);
}
