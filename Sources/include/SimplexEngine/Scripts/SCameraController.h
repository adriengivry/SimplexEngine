/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Scripts/IScript.h"
#include "SimplexEngine/Inputs/InputManager.h"
#include "SimplexEngine/Components/CameraComponent.h"

#pragma once
#ifndef _SCAMERACONTROLLER_H
#define _SCAMERACONTROLLER_H

namespace SimplexEngine::Scripts
{
	/**
	* A simple script to control a camera
	*/
	class SCameraController final : public IScript
	{
	public:
		/**
		* Constructor of the camera controller
		* @param p_inputManager
		* @param p_cameraComponent (The camera to control with this script)
		*/
		SCameraController(const Inputs::InputManager& p_inputManager, Components::CameraComponent& p_cameraComponent);

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
		float m_mouseSensitivity = 30.0f;
		float m_yaw = 0.0f;
		float m_pitch = 0.0f;
	};
}

#endif // _SCAMERACONTROLLER_H
