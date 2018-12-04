/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _USERINTERFACE_H
#define _USERINTERFACE_H

#include <SDL.h>

#include "Rasterizer/Context/Window.h"

namespace Rasterizer::Core
{
	/**
	* A simple class using imgui to render things on screens
	*/
	class UserInterface final
	{
	public:
		/**
		* Constructor of the user interface
		* @param p_window
		*/
		UserInterface(const Context::Window& p_window);

		/**
		* Update imgui components
		* @param p_deltaTime
		*/
		void Update(float p_deltaTime);

		/**
		* Render
		*/
		void Render();

	private:
		const Context::Window& m_window;
	};
}

#endif // _USERINTERFACE_H