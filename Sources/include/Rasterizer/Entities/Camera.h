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
		* @param p_lookAt
		* @param p_upVector
		* @param p_windowWidth
		* @param p_windowHeight
		* @param p_fov (Default = 45.0f)
		* @param p_near (Default = 0.1f)
		* @param p_far (Default = 1000.0f)
		*/
		Camera(const glm::vec3& p_position, const glm::vec3& p_lookAt, const glm::vec3& p_upVector, uint32_t p_windowWidth, uint32_t p_windowHeight, float p_fov = 45.0f, float p_near = 0.1f, float p_far = 1000.0f);

		/**
		* Project a point to camera sapce
		* @param p_point
		*/
		std::pair<int32_t, int32_t> ProjectToCameraSpace(const glm::vec3& p_point) const;

		/**
		* Update the projection matrix with the current camera settings
		*/
		void UpdateProjectionMatrix();

		/**
		* Update the view matrix with the current camera settings
		*/
		void UpdateViewMatrix();

		/**
		* Update the projection view matrix with the current camera settings
		*/
		void UpdateViewProjectionMatrix();

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

	private:
		glm::vec3 m_lookAt;
		glm::vec3 m_upVector;

		uint32_t m_windowWidth;
		uint32_t m_windowHeight;
		float m_windowHalfWidth;
		float m_windowHalfHeight;

		float m_fov;
		float m_ratio;
		float m_near;
		float m_far;

		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;
		glm::mat4 m_viewProjectionMatrix;
	};
}

#endif // _CAMERA_H