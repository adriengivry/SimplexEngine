/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _FPSCONTROLLER_H
#define _FPSCONTROLLER_H

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Scripts/Behaviours/ABehaviour.h"
#include "SimplexEngine/Inputs/InputManager.h"
#include "SimplexEngine/Components/CameraComponent.h"
#include "SimplexEngine/Components/RigidbodyComponent.h"

namespace SimplexEngine::Scripts::Behaviours
{
	/**
	* A simple script to control a camera
	*/
	class API_SIMPLEXENGINE FPSController final : public Behaviours::ABehaviour
	{
	public:
		/**
		* Constructor of the FPSController
		* @param p_owner
		* @param p_inputManager
		* @param p_movementSpeed
		* @param p_mouseSensitivity
		*/
		FPSController(Actors::Actor& p_owner, const Inputs::InputManager& p_inputManager, float p_movementSpeed, float p_jumpStrength, float p_mouseSensitivity = 1.0f);

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
		Components::RigidbodyComponent& m_rigidbodyComponent;

		/* Internal stuffs */
		float m_mouseSensitivity;
		float m_movementSpeed;
		float m_yaw = 0.0f;
		float m_pitch = 0.0f;
		float m_jumpStrength;
	};
}

#endif // _FPSCONTROLLER_H
