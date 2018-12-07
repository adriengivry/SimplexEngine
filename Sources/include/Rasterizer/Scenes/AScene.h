/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _ASCENE_H
#define _ASCENE_H

#include <vector>
#include <memory>

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
#include "Rasterizer/Actors/Actor.h"

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
		* Load scene data (Cameras, models, scripts)
		*/
		void Load();

		/**
		* Unload scene data (Cameras, models, scripts)
		*/
		void Unload();

		/**
		* Return the vector of scripts as const reference
		*/
		const std::vector<std::unique_ptr<Scripts::IScript>>& GetScripts() const;

		/**
		* Return the vector of actors as const reference
		*/
		const std::vector<std::unique_ptr<Rasterizer::Actors::Actor>>& GetActors() const;

	protected:
		/**
		* Add an actor to the scene
		* @param p_args (Arguments forwarded to the actor constructor)
		*/
		template<typename T, typename... Args>
		T& AddActor(Args&&... p_args) 
		{
			m_actors.push_back(std::make_unique<T>(p_args...));
			return *m_actors.at(m_actors.size() - 1);
		}

		/**
		* Add a script to the scene
		* @param p_args (Arguments forwarded to the std::make_unique)
		*/
		template<typename T, typename... Args>
		void AddScript(Args&&... p_args)
		{ 
			m_scripts.push_back(std::make_unique<T>(p_args...));
		}

	private:
		virtual void OnLoad() = 0;
		virtual void OnUnload() = 0;

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
		std::vector<std::unique_ptr<Rasterizer::Actors::Actor>>		m_actors;
		std::vector<std::unique_ptr<Scripts::IScript>>				m_scripts;
	};
}

#endif // _ASCENE_H