/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _CAMERACONTROLLER_H
#define _CAMERACONTROLLER_H

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Scripts/SceneScripts/ISceneScript.h"
#include "SimplexEngine/Inputs/InputManager.h"
#include "SimplexEngine/Components/CameraComponent.h"

namespace SimplexEngine::Scripts::SceneScripts
{
	/**
	* A simple script to control a camera
	*/
	class API_SIMPLEXENGINE CameraController final : public ISceneScript
	{
	public:
		/**
		* Constructor of the camera controller
		* @param p_inputManager
		* @param p_cameraComponent (The camera to control with this script)
		* @param p_movementSpeed
		* @param p_mouseSensitivity
		*/
		CameraController(const Inputs::InputManager& p_inputManager, Components::CameraComponent& p_cameraComponent, float p_movementSpeed, float p_mouseSensitivity = 1.0f);

		/**
		* Update the script
		* @param p_deltaTime
		*/
		virtual void Update(float p_deltaTime) override;

		/**
		* Handle mouse movements
		* @param p_deltaTime
		*/
		void HandleMouse(float p_deltaTime);

		/**
		* Handle keyboard inputs
		* @param p_deltaTime
		*/
		void HandleKeyboard(float p_deltaTime);

	private:
		const Inputs::InputManager& m_inputManager;
		Components::CameraComponent& m_cameraComponent;

		/* Internal stuffs */
		float m_mouseSensitivity;
		float m_movementSpeed;
		float m_yaw = 0.0f;
		float m_pitch = 0.0f;
	};
}

#endif // _CAMERACONTROLLER_H
