/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _PROFILERREPORT_H
#define _PROFILERREPORT_H

#include <vector>

namespace SimplexEngine::Analytics
{
	/**
	* Contains profiling data about a running period
	*/
	struct ProfilerReport final
	{
		/**
		* Data about an action (Called method)
		*/
		struct Action final
		{
			std::string name;
			double duration;
			double percentage;
			uint64_t calls;
		};

		double elaspedTime;
		std::vector<Action> actions;
	};
}

#endif // _PROFILERREPORT_H