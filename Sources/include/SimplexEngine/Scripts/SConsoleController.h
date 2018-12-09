/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Scripts/IScript.h"
#include "SimplexEngine/Core/InputManager.h"

#pragma once
#ifndef _SCONSOLECONTROLLER_H
#define _SCONSOLECONTROLLER_H

namespace SimplexEngine::Scripts
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
		SConsoleController(const Core::InputManager& p_inputManager);

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
		const Core::InputManager& m_inputManager;
	};
}

#endif // _SCONSOLECONTROLLER_H