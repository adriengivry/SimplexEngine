/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _CAMERA_H
#define _CAMERA_H

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
		* @param p_fov
		* @param p_ratio
		* @param p_near
		* @param p_far
		* @param p_lookAt
		* @param p_upVector
		*/
		Camera(const AltMath::Vector3f& p_position, const AltMath::Quaternion& p_rotation, float p_fov, float p_ratio, float p_near, float p_far, const AltMath::Vector3f& p_lookAt, const AltMath::Vector3f& p_upVector);

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
		const AltMath::Matrix4f& GetProjectionMatrix() const;

		/**
		* Return the current view matrix
		*/
		const AltMath::Matrix4f& GetViewMatrix() const;

		/**
		* Return the current view projection matrix
		*/
		const AltMath::Matrix4f& GetViewProjectionMatrix() const;

	private:
		float m_fov;
		float m_ratio;
		float m_near;
		float m_far;

		AltMath::Vector3f m_lookAt;
		AltMath::Vector3f m_upVector;

		AltMath::Matrix4f m_projectionMatrix;
		AltMath::Matrix4f m_viewMatrix;
		AltMath::Matrix4f m_viewProjectionMatrix;
	};
}

#endif // _CAMERA_H