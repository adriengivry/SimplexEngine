/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Scripts/IScript.h"
#include "SimplexEngine/Core/UserInterface.h"

#pragma once
#ifndef _SFPSCOUNTER_H
#define _SFPSCOUNTER_H

namespace SimplexEngine::Scripts
{
	/**
	* Display the framerate on the screen
	*/
	class SFPSCounter final : public IScript
	{
	public:
		/**
		* Constructor of the script
		* @p_userInterface
		*/
		SFPSCounter(Core::UserInterface& p_userInterface);

		/**
		* Update the script
		* @param p_deltaTime
		*/
		virtual void Update(float p_deltaTime) override;

		/**
		* Register a text to draw in the UI
		*/
		void ShowFPS();

	private:
		Core::UserInterface& m_userInterface;

		float m_logTimer;
		float m_logFrequency;
		uint16_t m_fps;
	};
}

#endif // _SFPSCOUNTER_H