/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _PROFILERLOGGER_H
#define _PROFILERLOGGER_H

#include "SimplexEngine/Scripts/GlobalScripts/IGlobalScript.h"
#include "SimplexEngine/Analytics/Profiler.h"
#include "SimplexEngine/Inputs/InputManager.h"
#include "SimplexEngine/Rendering/UserInterface.h"

namespace SimplexEngine::Scripts::GlobalScripts
{
	/**
	* Display profiling data to the screen
	*/
	class ProfilerLogger final : public IGlobalScript
	{
	public:
		/**
		* Constructor of the script
		* @param p_profiler
		*/
		ProfilerLogger(Analytics::Profiler& p_profiler, const Inputs::InputManager& p_inputManager, Rendering::UserInterface& p_userInterface);

		/**
		* Update the script
		* @param p_deltaTime
		*/
		virtual void Update(float p_deltaTime) override;

		/**
		* Send an action to draw as text to the UI
		* @param p_action
		* @param p_yOffset
		*/
		void ShowAction(const Analytics::ProfilerReport::Action& p_action, int16_t yOffset);

	private:
		const Inputs::InputManager& m_inputManager;
		Analytics::Profiler& m_profiler;
		Rendering::UserInterface& m_userInterface;

		Analytics::ProfilerReport m_report;

		bool m_reportGenerationPaused;
		float m_logTimer;
	};
}

#endif // _PROFILERLOGGER