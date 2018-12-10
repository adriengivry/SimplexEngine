/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _THREADMANAGER_H
#define _THREADMANAGER_H

#include <thread>

#include "SimplexEngine/API/Export.h"

namespace SimplexEngine::Threading
{
	class API_SIMPLEXENGINE ThreadManager final
	{
	public:
		/**
		* Create the thread manager
		*/
		ThreadManager();

		/**
		* Return the number of threads that the application can use
		*/
		uint32_t GetMaximumThread() const;

		/**
		* Define a cap for the maximum amount of threads usable
		* @param p_newCap
		*/
		void SetThreadCap(uint32_t p_newCap);

		/**
		* Return the user defined cap
		*/
		uint32_t GetThreadCap() const;

		/**
		* Return the hardware defined cap
		*/
		uint32_t GetHardwareThreadCap() const;

	private:
		uint32_t m_hardwareThreadCap;
		uint32_t m_threadCap;
	};
}

#endif // _THREADMANAGER_H
