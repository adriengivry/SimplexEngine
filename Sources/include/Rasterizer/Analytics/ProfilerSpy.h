/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _PROFILERSPY_H
#define _PROFILERSPY_H

#include "Rasterizer/Analytics/Profiler.h"
#include "Rasterizer/Analytics/ProfilerSpy.h"

#include <string>
#include <chrono>

/**
* This macro allow the creation of profiler spies
* Any spy will die and send data to the profiler at
* the end of the scope where this macro get called
*/
#define PROFILER_SPY(name)\
		std::unique_ptr<Rasterizer::Analytics::ProfilerSpy> __profiler_spy__ = \
		Rasterizer::Analytics::Profiler::IsEnabled() ? std::make_unique<Rasterizer::Analytics::ProfilerSpy>(name) : nullptr

namespace Rasterizer::Analytics
{
	/**
	* A little informer that is created when PROFILER_SPY(name) is written.
	* It helps collecting informations about methods durations for debugging
	* event in release
	*/
	struct ProfilerSpy final
	{
		/**
		* Create the profiler spy with the given name.
		* @param p_name
		*/
		ProfilerSpy(const std::string& p_name);

		/**
		* Destroy the profiler spy.
		* On destruction, his collected data will be saved in the profiler
		*/
		~ProfilerSpy();

		const std::string name;
		const std::chrono::steady_clock::time_point start;
		std::chrono::steady_clock::time_point end;
	};
}

#endif // _PROFILERSPY_H