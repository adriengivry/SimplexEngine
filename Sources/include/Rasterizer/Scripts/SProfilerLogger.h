/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Scripts/IScript.h"
#include "Rasterizer/Analytics/Profiler.h"
#include "Rasterizer/Context/InputManager.h"
#include "Rasterizer/Core/UserInterface.h"

#pragma once
#ifndef _SPROFILERLOGGER_H
#define _SPROFILERLOGGER_H

namespace Rasterizer::Scripts
{
	/**
	* Rotate an entity over time
	*/
	class SProfilerLogger final : public IScript
	{
	public:
		/**
		* Constructor of the script
		* @param p_profiler
		*/
		SProfilerLogger(Analytics::Profiler& p_profiler, const Context::InputManager& p_inputManager, Core::UserInterface& p_userInterface);

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
		const Context::InputManager& m_inputManager;
		Analytics::Profiler& m_profiler;
		Core::UserInterface& m_userInterface;

		Analytics::ProfilerReport m_report;

		bool m_reportGenerationPaused;
		float m_logTimer;
	};
}

#endif // _SFPSCOUNTER_H