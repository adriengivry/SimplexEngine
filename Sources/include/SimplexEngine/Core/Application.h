/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _APPLICATION_H
#define _APPLICATION_H

/* Core */
#include "SimplexEngine/Core/Window.h"
#include "SimplexEngine/Core/EventHandler.h"
#include "SimplexEngine/Core/InputManager.h"
#include "SimplexEngine/Core/EApplicationState.h"
#include "SimplexEngine/Rendering/Renderer.h"
#include "SimplexEngine/Core/UserInterface.h"
#include "SimplexEngine/Rendering/Rasterizer.h"
#include "SimplexEngine/Core/SceneManager.h"

/* Analytics */
#include "SimplexEngine/Analytics/Profiler.h"

/* Utils */
#include "SimplexEngine/Utils/Clock.h"
#include "SimplexEngine/Utils/IniIndexer.h"
#include "SimplexEngine/Resources/Managers/MeshManager.h"
#include "SimplexEngine/Scripts/IScript.h"
#include "SimplexEngine/Scenes/AScene.h"
#include "SimplexEngine/Materials/AMaterial.h"

namespace SimplexEngine::Core
{
	/**
	* The Application class contains the main logic of this application (Including main loop)
	*/
	class Application final
	{
	public:
		/**
		* Constructor of the application
 		*/
		Application();

		/**
		* Run the actual application (Blocking method, it is a loop).
		* Returns an exit code.
		*/
		int Run();

		/**
		* Create the current scene
		*/
		void CreateScenes();

		/**
		* Create global scripts (Independent of the current scene)
		*/
		void CreateGlobalScripts();

		/**
		* Add a global script to the application (Independent of the current scene)
		* @param p_args (Arguments forwarded to the std::make_unique)
		*/
		template<typename T, typename... Args>
		void AddGlobalScript(Args&&... p_args) { m_globalScripts.push_back(std::make_unique<T>(p_args...)); }

		/**
		* Update the current application
		* @param p_deltaTime
		*/
		void Update(float p_deltaTime);

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

		/**
		* Return true if the current state of the application is RUNNING
		*/
		bool IsRunning() const;

		/**
		* Stops the application. This method is listening to the WindowClosedEvent from the EventListener
		*/
		void Stop();

	private:
		/* Core */
		SimplexEngine::Core::Window m_window;
		SimplexEngine::Core::EventHandler m_eventHandler;
		SimplexEngine::Core::InputManager m_inputManager;
		SimplexEngine::Rendering::Renderer m_renderer;
		SimplexEngine::Core::UserInterface m_userInterface;
		SimplexEngine::Rendering::Rasterizer m_rasterBoy;
		SimplexEngine::Core::SceneManager m_sceneManager;
		SimplexEngine::Analytics::Profiler m_profiler;
		SimplexEngine::Utils::Clock m_clock;
		SimplexEngine::Resources::Managers::MeshManager m_meshManager;

		/* Default stuffs */
		Actors::Actor m_defaultCamera;
		std::vector<std::unique_ptr<Scripts::IScript>> m_globalScripts;
		std::unique_ptr<Materials::AMaterial> m_defaultMaterial;

		/* Other stuffs */
		EApplicationState m_applicationState;
	};
}

#endif // _APPLICATION_H