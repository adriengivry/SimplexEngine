/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _HARDWAREINFO_H
#define _HARDWAREINFO_H

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Scripts/GlobalScripts/IGlobalScript.h"
#include "SimplexEngine/Threading/ThreadManager.h"
#include "SimplexEngine/Rendering/UserInterface.h"

namespace SimplexEngine::Scripts::GlobalScripts
{
	class API_SIMPLEXENGINE HardwareInfo final : public IGlobalScript
	{
	public:
		/**
		* Script constructor
		* @param p_userInterface
		* @param p_threadManager
		*/
		HardwareInfo(Rendering::UserInterface& p_userInterface, Threading::ThreadManager& p_threadManager);

		/**
		* Update the script
		* @param p_deltaTime
		*/
		virtual void Update(float p_deltaTime) override;

		/**
		* Show hardware info on the screen
		*/
		void ShowHardwareInfo();

	private:
		Rendering::UserInterface& m_userInterface;
		Threading::ThreadManager& m_threadManager;
	};
}

#endif // _HARDWAREINFO_H