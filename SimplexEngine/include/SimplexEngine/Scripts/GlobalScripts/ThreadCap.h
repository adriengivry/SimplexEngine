/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _THREADCAP_H
#define _THREADCAP_H

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Scripts/GlobalScripts/IGlobalScript.h"
#include "SimplexEngine/Threading/ThreadManager.h"
#include "SimplexEngine/Inputs/InputManager.h"

namespace SimplexEngine::Scripts::GlobalScripts
{
	/**
	* Cap the maximum amount of threads that the application can use
	*/
	class API_SIMPLEXENGINE ThreadCap final : public IGlobalScript
	{
	public:
		/**
		* Constructor of the script
		* @param p_threadManager
		* @param p_inputManager
		*/
		ThreadCap(Threading::ThreadManager& p_threadManager, Inputs::InputManager& p_inputManager);

		/**
		* Update the script
		* @param p_deltaTime
		*/
		virtual void Update(float p_deltaTime) override;

	private:
		Threading::ThreadManager& m_threadManager;
		Inputs::InputManager& m_inputManager;
		uint32_t m_currentThreadCap;
	};
}

#endif // _THREADCAP_H