/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "Rasterizer/Context/Window.h"
#include "Rasterizer/Context/EventHandler.h"
#include "Rasterizer/Context/InputManager.h"
#include "Rasterizer/Core/EApplicationState.h"
#include "Rasterizer/Core/Renderer.h"
#include "Rasterizer/Core/RasterBoy.h"
#include "Rasterizer/Utils/Clock.h"
#include "Rasterizer/Utils/IniIndexer.h"
#include "Rasterizer/Entities/Camera.h"
#include "Rasterizer/Entities/Model.h"
#include "Rasterizer/Resources/Managers/MeshManager.h"

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
		* Update the current application
		* @param p_deltaTime
		*/
		void Update(float p_deltaTime);

		/**
		* Return true if the current state of the application is RUNNING
		*/
		bool IsRunning();

		/**
		* Stops the application. This method is listening to the WindowClosedEvent from the EventListener
		*/
		void Stop();

	private:
		/* SDL Relatives */
		Rasterizer::Context::Window m_window;
		Rasterizer::Context::EventHandler m_eventHandler;
		Rasterizer::Context::InputManager m_inputManager;

		/* Core */
		Rasterizer::Core::Renderer m_renderer;
		Rasterizer::Core::RasterBoy m_rasterBoy;

		/* Utils */
		Rasterizer::Utils::Clock m_clock;

		/* Resource managers */
		Rasterizer::Resources::Managers::MeshManager m_meshManager;

		/* Scene relatives */
		Rasterizer::Entities::Camera m_camera;
		std::vector<Rasterizer::Entities::Model> m_models;

		/* Other stuffs */
		EApplicationState m_applicationState;
		float m_modelRotation = 0.0f;
		float m_logFPStimer = 0.0f;
	};
}

#endif // _APPLICATION_H