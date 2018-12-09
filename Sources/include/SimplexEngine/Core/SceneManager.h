/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H

#include <unordered_map>

#include "SimplexEngine/Scenes/AScene.h"

namespace SimplexEngine::Core
{
	/**
	* This class make the scene managing pretty easy by associating strings and scenes
	*/
	class SceneManager final
	{
	public:
		/**
		* Constructor of the scene manager
		*/
		SceneManager() = default;

		/**
		* Create a scenes instance (Without loading content) for future load
		* @param p_sceneName
		* @param p_args
		*/
		template<typename T, typename ... Args>
		void RegisterScene(const std::string& p_sceneName, Args&&... p_args) { m_scenes[p_sceneName] = std::make_unique<T>(p_args...); }

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

	private:
		std::unordered_map<std::string, std::unique_ptr<Scenes::AScene>> m_scenes;

		Scenes::AScene* m_currentScene = nullptr;
	};
}

#endif // _SCENEMANAGER_H