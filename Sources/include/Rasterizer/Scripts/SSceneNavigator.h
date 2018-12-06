/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _SSCENENAVIGATOR_H
#define _SSCENENAVIGATOR_H

#include "Rasterizer/Scripts/IScript.h"
#include "Rasterizer/Core/SceneManager.h"

namespace Rasterizer::Scripts
{
	/**
	* The scene navigator is reponsible for scene switching at runtime
	*/
	class SSceneNavigator : public IScript
	{
	public:
		/**
		* Constructor of the script
		* @param p_sceneManager
		*/
		SSceneNavigator(Core::SceneManager& p_sceneManager, const Core::InputManager& p_inputManager);

		/**
		* Update the script
		* @param p_deltaTime
		*/
		virtual void Update(float p_deltaTime) override;

	private:
		Core::SceneManager& m_sceneManager;
		const Core::InputManager& m_inputManager;
	};
}

#endif // _SSCENENAVIGATOR_H
