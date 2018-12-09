/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "SimplexEngine/API/Export.h"

/* Core */
#include "SimplexEngine/Windowing/Window.h"
#include "SimplexEngine/Eventing/EventHandler.h"
#include "SimplexEngine/Inputs/InputManager.h"
#include "SimplexEngine/Rendering/Renderer.h"
#include "SimplexEngine/Rendering/UserInterface.h"
#include "SimplexEngine/Rendering/Rasterizer.h"
#include "SimplexEngine/Scenes/SceneManager.h"

/* Analytics */
#include "SimplexEngine/Analytics/Profiler.h"

/* Utils */
#include "SimplexEngine/Utils/Clock.h"
#include "SimplexEngine/Utils/IniIndexer.h"
#include "SimplexEngine/Resources/Managers/MeshManager.h"
#include "SimplexEngine/Scripts/GlobalScripts/IGlobalScript.h"
#include "SimplexEngine/Scenes/AScene.h"
#include "SimplexEngine/Materials/AMaterial.h"

namespace SimplexEngine::Core
{
	/**
	* The Engine class contains the main logic of this application (Including main loop)
	*/
	class API_SIMPLEXENGINE Engine final
	{
	public:
		/**
		* Constructor of the application
 		*/
		Engine();

		/**
		* Add a global script to the application (Independent of the current scene)
		* @param p_args (Arguments forwarded to the std::make_unique)
		*/
		template<typename T, typename... Args>
		void AddGlobalScript(Args&&... p_args) { m_globalScripts.push_back(std::make_unique<T>(p_args...)); }

		/**
		* Update the engine
		*/
		void Update();

		/**
		* Return true if the current state of the application is RUNNING
		*/
		bool IsRunning() const;

		/**
		* Stops the application. This method is listening to the WindowClosedEvent from the EventListener
		*/
		void Stop();

	private:
		/**
		* Update scene scripts
		* @param p_deltaTime
		*/
		void UpdateSceneScripts(float p_deltaTime);

		/**
		* Update global scripts
		* @param p_deltaTime
		*/
		void UpdateGlobalScripts(float p_deltaTime);

		/**
		* Rasterize every model
		*/
		void RasterizeScene();

	public:
		/* Ini managment (Must be initialized first) */
		SimplexEngine::Utils::IniIndexer iniIndexer;

		/* Core */
		SimplexEngine::Windowing::Window				window;
		SimplexEngine::Eventing::EventHandler			eventHandler;
		SimplexEngine::Inputs::InputManager				inputManager;
		SimplexEngine::Rendering::Renderer				renderer;
		SimplexEngine::Rendering::UserInterface			userInterface;
		SimplexEngine::Rendering::Rasterizer			rasterBoy;
		SimplexEngine::Analytics::Profiler				profiler;
		SimplexEngine::Utils::Clock						clock;
		SimplexEngine::Resources::Managers::MeshManager meshManager;
		SimplexEngine::Scenes::SceneManager				sceneManager;

	private:
		/* Default stuffs */
		Actors::Actor m_defaultCamera;
		std::vector<std::unique_ptr<Scripts::GlobalScripts::IGlobalScript>> m_globalScripts;
		std::unique_ptr<Materials::AMaterial> m_defaultMaterial;

		/* Other stuffs */
		bool m_running;
	};
}

#endif // _APPLICATION_H