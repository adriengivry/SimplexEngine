/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Rasterizer/Utils/Event.h"

namespace Rasterizer::Data
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
		*/
		Transform(glm::vec3 p_localPosition, glm::quat p_localRotation);

		/**
		* Defines a parent to the transform
		* @param p_parent
		* @param p_addChild (Directly add this as a child of the parent)
		*/
		void SetParent(Data::Transform& p_parent, bool p_addChild = true);

		/**
		* Initialize transform with raw data
		* @param p_position
		* @param p_rotation
		*/
		void GenerateMatrices(glm::vec3 p_position, glm::quat p_rotation);

		/**
		* Re-update world matrices to use parent transformations
		*/
		void UpdateWorldMatrices();

		/**
		* Check if the transform has a parent
		*/
		bool HasParent() const;

		/**
		* Set the position of the transform in the local space
		* @param p_newPosition
		*/
		void SetPosition(glm::vec3 p_newPosition);

		/**
		* Set the rotation of the transform in the local space
		* @param p_newRotation
		*/
		void SetRotation(glm::quat p_newRotation);

		/**
		* Translate in the local space
		* @param p_translation
		*/
		void Translate(const glm::vec3& p_translation);

		/**
		* Rotate in the local space
		* @param p_rotation
		*/
		void Rotate(const glm::quat& p_rotation);

		/**
		* Return the local position of the transform
		*/
		glm::vec3 GetLocalPosition() /* SHOULD BE CONST BUT CANT */;

		/**
		* Return local rotation of the transform
		*/
		glm::quat GetLocalRotation() /* SHOULD BE CONST BUT CANT */;

		/**
		* Return the world position of the transform
		*/
		glm::vec3 GetWorldPosition() /* SHOULD BE CONST BUT CANT */;

		/**
		* Return the world rotation of the transform
		*/
		glm::quat GetWorldRotation() /* SHOULD BE CONST BUT CANT */;

		/**
		* Return the local matrix
		*/
		const glm::mat4& GetLocalMatrix() const;

		/**
		* Return the world matrix
		*/
		const glm::mat4& GetWorldMatrix() const;

	public:
		Utils::Event<> TransformChangedEvent;

	private:
		glm::mat4	m_localMatrix;
		glm::mat4	m_worldMatrix;
		Transform*	m_parent;
	};
}

#endif // _TRANSFORM_H