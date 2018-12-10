/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _PROFILER_H
#define _PROFILER_H

#include <unordered_map>
#include <chrono>
#include <mutex>

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Analytics/ProfilerReport.h"

namespace SimplexEngine::Analytics
{
	/* Forward declaration of the profiler spy structure */
	struct ProfilerSpy;

	/**
	* The profiler collect data about the running program
	*/
	class API_SIMPLEXENGINE Profiler final
	{
	public:
		/**
		* Create the profiler
		*/
		Profiler();

		/**
		* Generate a report containing data about the last profiling session
		*/
		ProfilerReport GenerateReport();

		/**
		* Clear any collected data
		*/
		void ClearHistory();

		/**
		* Save the given spy collected data to the profiler history
		* @param p_spy (Spy to collect data from)
		*/
		static void Save(ProfilerSpy& p_spy);

		/**
		* Verify if the profiler is currently enabled
		*/
		static bool IsEnabled();

		/**
		* Enable the profiler if it is currently disabled, and vice-versa
		*/
		static void ToggleEnable();

		/**
		* Enable the profiler
		*/
		static void Enable();

		/**
		* Disable the profiler
		*/
		static void Disable();

	private:
		/* Time relatives */
		std::chrono::steady_clock::time_point m_lastTime;

		/* Profiler settings */
		static bool __ENABLED;

		/* Collected data */
		static std::mutex __SAVE_MUTEX;
		static std::unordered_map<std::string, double>		__ELPASED_HISTORY;
		static std::unordered_map<std::string, uint64_t>	__CALLS_COUNTER;
	};
}

#endif // _PROFILER_H