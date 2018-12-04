/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _CAMERA_H
#define _CAMERA_H

#include <glm/glm.hpp>

#include "Rasterizer/Entities/AEntity.h"

namespace Rasterizer::Entities
{
	/**
	* The camera is used to know how to project things on the screen
	*/
	class Camera final : public AEntity
	{
	public:
		/**
		* Camera constructor
		* @param p_position
		* @param p_rotation
		* @param p_upVector
		* @param p_windowWidth
		* @param p_windowHeight
		* @param p_fov (Default = 45.0f)
		* @param p_near (Default = 0.1f)
		* @param p_far (Default = 1000.0f)
		*/
		Camera(const glm::vec3& p_position, const glm::quat& p_rotation, const glm::vec3& p_upVector, float p_ratio, float p_fov = 45.0f, float p_near = 0.1f, float p_far = 1000.0f);

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

#endif // _CAMERA_H