/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _SCENENAVIGATOR_H
#define _SCENENAVIGATOR_H

#include "SimplexEngine/Scripts/GlobalScripts/IGlobalScript.h"
#include "SimplexEngine/Scenes/SceneManager.h"

namespace SimplexEngine::Scripts::GlobalScripts
{
	/**
	* The scene navigator is reponsible for scene switching at runtime
	*/
	class SceneNavigator : public IGlobalScript
	{
	public:
		/**
		* Constructor of the script
		* @param p_sceneManager
		*/
		SceneNavigator(Scenes::SceneManager& p_sceneManager, const Inputs::InputManager& p_inputManager);

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

#endif // _SCENENAVIGATOR_H
