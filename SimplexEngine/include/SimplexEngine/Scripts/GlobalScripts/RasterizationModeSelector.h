/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _RASTERIZATIONMODESELECTOR_H
#define _RASTERIZATIONMODESELECTOR_H

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Scripts/GlobalScripts/IGlobalScript.h"
#include "SimplexEngine/Rendering/Rasterizer.h"
#include "SimplexEngine/Rendering/UserInterface.h"
#include "SimplexEngine/Inputs/InputManager.h"

namespace SimplexEngine::Scripts::GlobalScripts
{
	/**
	* A simple script to switch between rasterization modes
	*/
	class API_SIMPLEXENGINE RasterizationModeSelector final : public IGlobalScript
	{
	public:
		/**
		* Script constructor
		* @param p_rasterizer
		* @param p_inputManager
		* @param p_displaySettings (True to show current rasterization settings on the bottom right of the screen)
		*/
		RasterizationModeSelector(Rendering::Rasterizer& p_rasterizer, const Inputs::InputManager& p_inputManager, Rendering::UserInterface& p_userInterface, bool p_displaySettings);

		/**
		* Update the script
		* @param p_deltaTime
		*/
		void Update(float p_deltaTime);

		/**
		* Determine the rasterization draw mode following the current one
		*/
		Rendering::ERasterizationDrawMode FindNextDrawMode();

		/**
		* Determine the rasterization culling mode following the current one
		*/
		Rendering::ERasterizationCullingMode FindNextCullingMode();

		/**
		* Return the current draw mode as a string
		*/
		std::string GetDrawModeAsString();

		/**
		* Return the current culling mode as a string
		*/
		std::string GetCullingwModeAsString();

		/**
		* Display current rasterization settings on the screen
		*/
		void DisplayCurrentSettings();

	private:
		Rendering::Rasterizer& m_rasterizer;
		const Inputs::InputManager& m_inputManager;
		Rendering::UserInterface& m_userInterface;
		bool m_displaySettings;
	};
}

#endif // _RASTERIZATIONMODESELECTOR_H