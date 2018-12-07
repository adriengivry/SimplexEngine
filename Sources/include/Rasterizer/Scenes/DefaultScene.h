/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _DEFAULTSCENE_H
#define _DEFAULTSCENE_H

#include "Rasterizer/Scenes/AScene.h"

namespace Rasterizer::Scenes
{
	/**
	* The default scene of the project
	*/
	class DefaultScene final : public AScene
	{
	public:
		/**
		* Constructor of the scene, require main classes instances to get send as references
		* @param p_window
		* @param p_eventHandler
		* @param p_inputManager
		* @param p_renderer
		* @param p_userInterface
		* @param p_rasterBoy
		* @param p_profiler
		* @param p_clock
		* @param p_meshManager
		*/
		DefaultScene(SCENE_PARAMETERS);

	private:
		virtual void OnLoad() override;
		virtual void OnUnload() override;
	};
}

#endif // _DEFAULTSCENE_H