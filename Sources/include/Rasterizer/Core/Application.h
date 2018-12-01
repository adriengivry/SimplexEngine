/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <GyvrIni/Core/IniFile.h>

#include "Rasterizer/Context/Window.h"
#include "Rasterizer/Context/EventHandler.h"
#include "Rasterizer/Core/EApplicationState.h"
#include "Rasterizer/Core/Renderer.h"
#include "Rasterizer/Utils/Clock.h"
#include "Rasterizer/Entities/Camera.h"
#include "Rasterizer/Entities/Model.h"

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
		* Return true if the current state of the application is RUNNING
		*/
		bool IsRunning();

		/**
		* Stops the application. This method is listening to the WindowClosedEvent from the EventListener
		*/
		void Stop();

	private:
		GyvrIni::Core::IniFile m_windowINI;

		Rasterizer::Context::Window m_window;
		Rasterizer::Context::EventHandler m_eventHandler;
		Rasterizer::Core::Renderer m_renderer;
		Rasterizer::Utils::Clock m_clock;
			
		EApplicationState m_applicationState;

		/* Some data */
		Rasterizer::Data::Mesh m_defaultMesh;

		/* Scene relatives */
		Rasterizer::Entities::Camera m_camera;
		Rasterizer::Entities::Model m_model;

		/* Animation stuffs */
		float m_modelRotation = 0.0f;
	};
}

#endif // _APPLICATION_H