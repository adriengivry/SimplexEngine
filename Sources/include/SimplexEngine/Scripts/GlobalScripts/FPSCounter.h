/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _FPSCOUNTER_H
#define _FPSCOUNTER_H

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Scripts/GlobalScripts/IGlobalScript.h"
#include "SimplexEngine/Rendering/UserInterface.h"

namespace SimplexEngine::Scripts::GlobalScripts
{
	/**
	* Display the framerate on the screen
	*/
	class API_SIMPLEXENGINE FPSCounter final : public IGlobalScript
	{
	public:
		/**
		* Constructor of the script
		* @p_userInterface
		*/
		FPSCounter(Rendering::UserInterface& p_userInterface);

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
		Rendering::UserInterface& m_userInterface;

		float m_logTimer;
		float m_logFrequency;
		uint16_t m_fps;
	};
}

#endif // _FPSCOUNTER_H