/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _CAMERACOMPONENT_H
#define _CAMERACOMPONENT_H

#include <glm/glm.hpp>

#include "Rasterizer/Components/AActorComponent.h"

namespace Rasterizer::Components
{
	/**
	* The camera component is a component that allow an actor to get
	* interpreted as a scene camera
	*/
	class CameraComponent : public AActorComponent
	{
	public:
		/**
		* Camera constructor
		* @param p_owner
		* @param p_upVector
		* @param p_windowWidth
		* @param p_windowHeight
		* @param p_fov (Default = 45.0f)
		* @param p_near (Default = 0.1f)
		* @param p_far (Default = 1000.0f)
		*/
		CameraComponent(Actors::Actor& p_owner, const glm::vec3& p_upVector, float p_ratio, float p_fov = 45.0f, float p_near = 0.1f, float p_far = 1000.0f);

		/**
		* Needed
		*/
		virtual void Test() override {}

		/**
		* Return the current projection matrix
		*/
		const glm::mat4& GetProjectionMatrix() const;

		/**
		* Return the current view matrix
		*/
		const glm::mat4& GetViewMatrix() const;

		/**
		* Return the current view projection matrix
		*/
		const glm::mat4& GetViewProjectionMatrix() const;

		/**
		* Return the forward vector of the camera
		*/
		const glm::vec3& GetForward() const;

	private:
		void UpdateForwardVector();
		void UpdateProjectionMatrix();
		void UpdateViewMatrix();
		void UpdateViewProjectionMatrix();

	private:
		glm::vec3 m_forward;
		glm::vec3 m_upVector;

		float m_ratio;
		float m_fov;
		float m_near;
		float m_far;

		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;
		glm::mat4 m_viewProjectionMatrix;
	};
}

#endif // _CAMERACOMPONENT_H