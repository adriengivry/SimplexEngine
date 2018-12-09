/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Scripts/IScript.h"
#include "SimplexEngine/Analytics/Profiler.h"
#include "SimplexEngine/Core/InputManager.h"
#include "SimplexEngine/Rendering/UserInterface.h"

#pragma once
#ifndef _SPROFILERLOGGER_H
#define _SPROFILERLOGGER_H

namespace SimplexEngine::Scripts
{
	/**
	* Display profiling data to the screen
	*/
	class SProfilerLogger final : public IScript
	{
	public:
		/**
		* Constructor of the script
		* @param p_profiler
		*/
		SProfilerLogger(Analytics::Profiler& p_profiler, const Core::InputManager& p_inputManager, Rendering::UserInterface& p_userInterface);

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
		const Core::InputManager& m_inputManager;
		Analytics::Profiler& m_profiler;
		Rendering::UserInterface& m_userInterface;

		Analytics::ProfilerReport m_report;

		bool m_reportGenerationPaused;
		float m_logTimer;
	};
}

#endif // _SFPSCOUNTER_H