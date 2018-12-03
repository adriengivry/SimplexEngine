/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Scripts/IScript.h"
#include "Rasterizer/Context/InputManager.h"

#pragma once
#ifndef _SFPSCOUNTER_H
#define _SFPSCOUNTER_H

namespace Rasterizer::Scripts
{
	/**
	* Rotate an entity over time
	*/
	class SFPSCounter final : public IScript
	{
	public:
		/**
		* Constructor of the script
		* @p_inputManager
		*/
		SFPSCounter(const Context::InputManager& p_inputManager);

		/**
		* Update the script
		* @param p_deltaTime
		*/
		virtual void Update(float p_deltaTime) override;

		/**
		* Print the current FPS in the console
		* @param p_deltaTime
		*/
		void PrintFPS(float p_deltaTime);

	private:
		const Context::InputManager& m_inputManager;

		float m_logTimer;
		float m_logFrequency;
	};
}

#endif // _SFPSCOUNTER_H