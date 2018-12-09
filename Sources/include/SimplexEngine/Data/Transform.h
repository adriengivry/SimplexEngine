/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "SimplexEngine/Eventing/Event.h"

namespace SimplexEngine::Data
{
	/**
	* Represent a local or world transformation (Position and rotation)
	*/
	struct Transform final
	{
		/**
		* Create a transform without setting a parent
		* @param p_localPosition
		* @param p_localRotation
		* @param p_localScale
		*/
		Transform(glm::vec3 p_localPosition = glm::vec3(0.0f, 0.0f, 0.0f), glm::quat p_localRotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3 p_localScale = glm::vec3(1.0f, 1.0f, 1.0f));

		/**
		* Defines a parent to the transform
		* @param p_parent
		*/
		void SetParent(Data::Transform& p_parent);

		/**
		* Check if the transform has a parent
		*/
		bool HasParent() const;

		/**
		* Initialize transform with raw data
		* @param p_position
		* @param p_rotation
		* @param p_scale
		*/
		void GenerateMatrices(glm::vec3 p_position, glm::quat p_rotation, glm::vec3 p_scale);

		/**
		* Re-update world matrices to use parent transformations
		*/
		void UpdateWorldMatrices();

		/**
		* Set the position of the transform in the local space
		* @param p_newPosition
		*/
		void SetLocalPosition(glm::vec3 p_newPosition);

		/**
		* Set the rotation of the transform in the local space
		* @param p_newRotation
		*/
		void SetLocalRotation(glm::quat p_newRotation);

		/**
		* Set the scale of the transform in the local space
		* @param p_newScale
		*/
		void SetLocalScale(glm::vec3 p_newScale);

		/**
		* Translate in the local space
		* @param p_translation
		*/
		void TranslateLocal(const glm::vec3& p_translation);

		/**
		* Rotate in the local space
		* @param p_rotation
		*/
		void RotateLocal(const glm::quat& p_rotation);

		/**
		* Scale in the local space
		* @param p_scale
		*/
		void ScaleLocal(const glm::vec3& p_scale);

		/**
		* Return the position in local space
		*/
		const glm::vec3& GetLocalPosition() const;

		/**
		* Return the rotation in local space
		*/
		const glm::quat& GetLocalRotation() const;

		/**
		* Return the scale in local space
		*/
		const glm::vec3& GetLocalScale() const;

		/**
		* Return the position in world space
		*/
		const glm::vec3& GetWorldPosition() const;

		/**
		* Return the rotation in world space
		*/
		const glm::quat& GetWorldRotation() const;

		/**
		* Return the scale in world space
		*/
		const glm::vec3& GetWorldScale() const;

		/**
		* Return the local matrix
		*/
		const glm::mat4& GetLocalMatrix() const;

		/**
		* Return the world matrix
		*/
		const glm::mat4& GetWorldMatrix() const;

	public:
		Eventing::Event<> TransformChangedEvent;

	private:
		void PreDecomposeWorldMatrix();
		void PreDecomposeLocalMatrix();
		void PreDecomposeMatrices();

		/* Pre-decomposed data to prevent multiple decomposition */
		glm::vec3 m_localPosition;
		glm::quat m_localRotation;
		glm::vec3 m_localScale;
		glm::vec3 m_worldPosition;
		glm::quat m_worldRotation;
		glm::vec3 m_worldScale;
		glm::mat4 m_localMatrix;
		glm::mat4 m_worldMatrix;

		Transform*	m_parent;
	};
}

#endif // _TRANSFORM_H