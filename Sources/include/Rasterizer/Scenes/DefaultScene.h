/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _DEFAULTSCENE_H
#define _DEFAULTSCENE_H

#include "Rasterizer/Scenes/AScene.h"

namespace Rasterizer::Scenes
{
	/**
	* The default scene of the project
	*/
	class DefaultScene final : public AScene
	{
	public:
		/**
		* Constructor of the scene, require core classes to get send as references
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
		DefaultScene
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
		* You should create your cameras here
		*/
		virtual void CreateCameras() override;

		/**
		* You should create your models here
		*/
		virtual void CreateModels() override;

		/**
		* You should create your scripts here
		*/
		virtual void CreateScripts() override;
		
		/**
		*You should define you parent/child relations here
		*/
		virtual void DefineParents() override;
	};
}

#endif // _DEFAULTSCENE_H