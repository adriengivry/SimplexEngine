/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "Rasterizer/Core/Window.h"
#include "Rasterizer/Core/EventHandler.h"
#include "Rasterizer/Core/InputManager.h"
#include "Rasterizer/Core/EApplicationState.h"
#include "Rasterizer/Core/Renderer.h"
#include "Rasterizer/Core/UserInterface.h"
#include "Rasterizer/Core/RasterBoy.h"
#include "Rasterizer/Core/SceneManager.h"
#include "Rasterizer/Analytics/Profiler.h"
#include "Rasterizer/Utils/Clock.h"
#include "Rasterizer/Resources/Managers/MeshManager.h"
#include "Rasterizer/Utils/IniIndexer.h"
#include "Rasterizer/Entities/Camera.h"
#include "Rasterizer/Entities/Model.h"
#include "Rasterizer/Scripts/IScript.h"
#include "Rasterizer/Scenes/AScene.h"
#include "Rasterizer/Materials/AMaterial.h"

namespace Rasterizer::Core
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
		void RasterizeModels();

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
		Rasterizer::Core::Window m_window;
		Rasterizer::Core::EventHandler m_eventHandler;
		Rasterizer::Core::InputManager m_inputManager;
		Rasterizer::Core::Renderer m_renderer;
		Rasterizer::Core::UserInterface m_userInterface;
		Rasterizer::Core::RasterBoy m_rasterBoy;
		Rasterizer::Core::SceneManager m_sceneManager;
		Rasterizer::Analytics::Profiler m_profiler;
		Rasterizer::Utils::Clock m_clock;
		Rasterizer::Resources::Managers::MeshManager m_meshManager;

		/* Default stuffs */
		Rasterizer::Entities::Camera m_defaultCamera;
		std::vector<std::unique_ptr<Scripts::IScript>> m_globalScripts;
		std::unique_ptr<Materials::AMaterial> m_defaultMaterial;

		/* Other stuffs */
		EApplicationState m_applicationState;
	};
}

#endif // _APPLICATION_H