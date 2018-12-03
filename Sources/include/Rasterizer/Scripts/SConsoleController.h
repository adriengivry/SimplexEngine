/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Scripts/IScript.h"
#include "Rasterizer/Context/InputManager.h"

#pragma once
#ifndef _SCONSOLECONTROLLER_H
#define _SCONSOLECONTROLLER_H

namespace Rasterizer::Scripts
{
	/**
	* Rotate an entity over time
	*/
	class SConsoleController final : public IScript
	{
	public:
		/**
		* Constructor of the script
		* @p_inputManager
		*/
		SConsoleController(const Context::InputManager& p_inputManager);

		/**
		* Update the script
		* @param p_deltaTime
		*/
		virtual void Update(float p_deltaTime) override;

		/**
		* Clear the console
		*/
		void ClearConsole();

	private:
		const Context::InputManager& m_inputManager;
	};
}

#endif // _SCONSOLECONTROLLER_H