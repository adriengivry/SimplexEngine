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
		*/
		RasterizationModeSelector(Rendering::Rasterizer& p_rasterizer, const Inputs::InputManager& p_inputManager);

		/**
		* Update the script
		* @param p_deltaTime
		*/
		void Update(float p_deltaTime);

		/**
		* Determine the rasterization mode following the current one
		*/
		Rendering::ERasterizationMode FindNextMode();

	private:
		Rendering::Rasterizer& m_rasterizer;
		const Inputs::InputManager& m_inputManager;
	};
}

#endif // _RASTERIZATIONMODESELECTOR_H