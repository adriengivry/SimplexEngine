/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include <AltMath/AltMath.h>

#include "Rasterizer/Utils/Event.h"

namespace Rasterizer::Data
{
	/**
	* A "Transformation" represents a position (Vector3f from AltMath) and a quaternion (Quaternion from AltMath).
	* It is used to simplify code reading
	*/
	using Transformation = std::pair<AltMath::Vector3f, AltMath::Quaternion>;

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
		Transform(AltMath::Vector3f p_localPosition, AltMath::Quaternion p_localRotation);

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
		void GenerateMatrices(AltMath::Vector3f p_position, AltMath::Quaternion p_rotation);

		/**
		* Re-update world matrices to use parent transformations
		*/
		void UpdateWorldMatrices();

		/**
		* Check if the transform has a parent
		*/
		bool HasParent() const;

		/**
		* Set the position of the transform
		* @param p_newPosition
		*/
		void SetPosition(AltMath::Vector3f p_newPosition);

		/**
		* Set the rotation of the transform
		* @param p_newRotation
		*/
		void SetRotation(AltMath::Quaternion p_newRotation);

		/**
		* Return the local position of the transform
		*/
		AltMath::Vector3f GetLocalPosition() /* SHOULD BE CONST BUT CANT */;

		/**
		* Return local rotation of the transform
		*/
		AltMath::Quaternion GetLocalRotation() /* SHOULD BE CONST BUT CANT */;

		/**
		* Return the world position of the transform
		*/
		AltMath::Vector3f GetWorldPosition() /* SHOULD BE CONST BUT CANT */;

		/**
		* Return the world rotation of the transform
		*/
		AltMath::Quaternion GetWorldRotation() /* SHOULD BE CONST BUT CANT */;

		/**
		* Return the local matrix
		*/
		const AltMath::Matrix4f& GetLocalMatrix() const;

		/**
		* Return the local matrix
		*/
		const AltMath::Matrix4f& GetWorldMatrix() const;

	public:
		Utils::Event<> TransformChangedEvent;

	private:
		AltMath::Matrix4f								m_localMatrix;
		AltMath::Matrix4f								m_worldMatrix;
		Transform*										m_parent;
	};
}

#endif // _TRANSFORM_H