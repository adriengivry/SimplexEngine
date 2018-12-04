/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Scripts/IScript.h"
#include "Rasterizer/Context/InputManager.h"
#include "Rasterizer/Entities/Camera.h"

#pragma once
#ifndef _SCAMERACONTROLLER_H
#define _SCAMERACONTROLLER_H

namespace Rasterizer::Scripts
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
		* @param p_camera (The camera to control with this script)
		*/
		SCameraController(const Context::InputManager& p_inputManager, Entities::Camera& p_camera);

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
		const Context::InputManager& m_inputManager;
		Entities::Camera& m_camera;

		/* Internal stuffs */
		float m_mouseSensitivity = 30.0f;
		float m_yaw = 0.0f;
		float m_pitch = 0.0f;
	};
}

#endif // _SCAMERACONTROLLER_H
