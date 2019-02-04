/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H

#include <unordered_map>

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Scenes/AScene.h"

namespace SimplexEngine::Scenes
{
	/**
	* This class make the scene managing pretty easy by associating strings and scenes
	*/
	class API_SIMPLEXENGINE SceneManager final
	{
	public:
		/**
		* Constructor of the scene manager
		*/
		SceneManager(SCENE_PARAMETERS);

		/**
		* Create a scene instance (Without loading content) for future load
		* @param p_sceneName
		* @param p_args
		*/
		template<typename T, typename ... Args>
		void RegisterScene(const std::string& p_sceneName) { m_scenes[p_sceneName] = std::make_shared<T>(m_window, m_inputManager, m_userInterface, m_eventHandler, m_meshManager); }

		/**
		* Remove a scene instance
		* @param p_sceneName
		*/
		void UnregisterScene(const std::string& p_sceneName);

		/**
		* Return a reference to a scene identified by the given string (Scene name)
		* @param p_sceneName
		*/
		Scenes::AScene& GetSceneByName(const std::string& p_sceneName);

		/**
		* Load the scene identified by the given string (Scene name) and unload the current scene if any
		* @param p_sceneName
		*/
		void LoadScene(const std::string& p_sceneName);

		/**
		* Return a pointer to the current scene
		*/
		Scenes::AScene* GetCurrentScene();

		/**
		* Return true if there is a current scene
		*/
		bool HasCurrentScene() const;

	private:
		void OnComponentAdded(Components::AActorComponent& p_component);
		void OnComponentRemoved(Components::AActorComponent& p_component);

	public:
		Eventing::Event<Components::AActorComponent&> ComponentAddedEvent;
		Eventing::Event<Components::AActorComponent&> ComponentRemovedEvent;

	private:
		/* Scene services (Given to every scenes) */
		const Windowing::Window&			m_window;
		const Inputs::InputManager&			m_inputManager;
		Rendering::UserInterface&			m_userInterface;
		Eventing::EventHandler&				m_eventHandler;
		Resources::Managers::MeshManager&	m_meshManager;

		std::unordered_map<std::string, std::shared_ptr<Scenes::AScene>> m_scenes;

		Scenes::AScene* m_currentScene = nullptr;

		Eventing::Event<Components::AActorComponent&>::ListenerID m_sceneComponentAddListenerID;
		Eventing::Event<Components::AActorComponent&>::ListenerID m_sceneComponentRemoveListenerID;
	};
}

#endif // _SCENEMANAGER_H