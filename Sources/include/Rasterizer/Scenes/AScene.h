/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _ASCENE_H
#define _ASCENE_H

#include <vector>

#include "Rasterizer/Core/Window.h"
#include "Rasterizer/Core/EventHandler.h"
#include "Rasterizer/Core/InputManager.h"
#include "Rasterizer/Core/EApplicationState.h"
#include "Rasterizer/Core/Renderer.h"
#include "Rasterizer/Core/UserInterface.h"
#include "Rasterizer/Core/RasterBoy.h"
#include "Rasterizer/Analytics/Profiler.h"
#include "Rasterizer/Utils/Clock.h"
#include "Rasterizer/Resources/Managers/MeshManager.h"
#include "Rasterizer/Scripts/IScript.h"

/**
* This header contain some usefull macro to create scenes inheriting from AScene quickly
*/
#include "Rasterizer/Scenes/ASceneDefines.h"

namespace Rasterizer::Scenes
{
	/**
	* Abstract scene that is the base class for any scene of the project.
	* A scene is basically a collection of entities and scripts.
	* It has references about most main classes instances of the project to
	* allow scripts to influence them (Ex: Allow a script to access InputManager)
	*/
	class AScene
	{
	public:
		/**
		* Constructor of the scene, require main classes instances to get send as references
		* @param p_window
		* @param p_eventHandler
		* @param p_inputManager
		* @param p_renderer
		* @param p_userInterface
		* @param p_rasterBoy
		* @param p_profiler
		* @param p_clock
		* @param p_meshManager
		*/
		AScene
		(
			Core::Window&						p_window,
			Core::EventHandler&					p_eventHandler,
			Core::InputManager&					p_inputManager,
			Core::Renderer&						p_renderer,
			Core::UserInterface&				p_userInterface,
			Core::RasterBoy&					p_rasterBoy,
			Analytics::Profiler&				p_profiler,
			Utils::Clock&						p_clock,
			Resources::Managers::MeshManager&	p_meshManager
		);

		/**
		* Create all the scene (Cameras, models, scripts)
		*/
		void Initialize();

		/**
		* Return the main camera (As a pointer, because it is nullable)
		*/
		Entities::Camera* GetMainCamera();

		/**
		* Return the vector of cameras of the scene
		*/
		std::vector<Rasterizer::Entities::Camera>& GetCameras();

		/**
		* Return the vector of models of the scene
		*/
		std::vector<Rasterizer::Entities::Model>& GetModels();

		/**
		* Return the vector of scripts of the scene
		*/
		std::vector<std::unique_ptr<Scripts::IScript>>& GetScripts();

	protected:
		/**
		* Add a camera to the scene
		* @param p_args (Arguments forwarded to the std::make_unique)
		*/
		template<typename... Args>
		void AddCamera(Args&&... p_args) { m_cameras.emplace_back(p_args...); if (!m_mainCamera) SetAsMainCamera(m_cameras.at(m_cameras.size() - 1)); }

		/**
		* Add a model to the scene
		* @param p_args (Arguments forwarded to the std::make_unique)
		*/
		template<typename... Args>
		void AddModel(Args&&... p_args) { m_models.emplace_back(p_args...); }

		/**
		* Add a script to the scene
		* @param p_args (Arguments forwarded to the std::make_unique)
		*/
		template<typename T, typename... Args>
		void AddScript(Args&&... p_args) { m_scripts.push_back(std::make_unique<T>(p_args...)); }

		/**
		* Set the given camera as the main camera of the scene (Used for rendering)
		* @param p_camera
		*/
		void SetAsMainCamera(Entities::Camera& p_camera);

	private:
		/**
		* You should create your cameras here
		*/
		virtual void CreateCameras() = 0;

		/**
		* You should create your models here
		*/
		virtual void CreateModels() = 0;

		/**
		* You should create your scripts here
		*/
		virtual void CreateScripts() = 0;

		/**
		*You should define you parent/child relations here
		*/
		virtual void DefineParents() = 0;

	protected:
		/* Accessible data for new scenes */
		Core::Window&						m_window;
		Core::EventHandler&					m_eventHandler;
		Core::InputManager&					m_inputManager;
		Core::Renderer&						m_renderer;
		Core::UserInterface&				m_userInterface;
		Core::RasterBoy&					m_rasterBoy;
		Analytics::Profiler&				m_profiler;
		Utils::Clock&						m_clock;
		Resources::Managers::MeshManager&	m_meshManager;

		/* Scene content */
		std::vector<Rasterizer::Entities::Camera> m_cameras;
		std::vector<Rasterizer::Entities::Model> m_models;
		std::vector<std::unique_ptr<Scripts::IScript>> m_scripts;

		/* References */
		Rasterizer::Entities::Camera* m_mainCamera = nullptr;
	};
}

#endif // _ASCENE_H