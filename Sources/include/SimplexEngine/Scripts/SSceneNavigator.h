/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _SSCENENAVIGATOR_H
#define _SSCENENAVIGATOR_H

#include "SimplexEngine/Scripts/IScript.h"
#include "SimplexEngine/Scenes/SceneManager.h"

namespace SimplexEngine::Scripts
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
		SSceneNavigator(Scenes::SceneManager& p_sceneManager, const Inputs::InputManager& p_inputManager);

		/**
		* Update the script
		* @param p_deltaTime
		*/
		virtual void Update(float p_deltaTime) override;

	private:
		Scenes::SceneManager& m_sceneManager;
		const Inputs::InputManager& m_inputManager;
	};
}

#endif // _SSCENENAVIGATOR_H
