/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _AENTITY_H
#define _AENTITY_H

#include "Rasterizer/Data/Transform.h"

namespace Rasterizer::Entities
{
	/**
	* The Entity class represent something that is localized in the world
	*/
	class AEntity
	{
	public:
		/**
		* Entity constructor
		* @param p_localPosition
		* @param p_localRotation
		* @param p_localScale
		*/
		AEntity(glm::vec3 p_localPosition = glm::vec3(0.0f, 0.0f, 0.0f), glm::quat p_localRotation = glm::quat(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3 p_localScale = glm::vec3(1.0f, 1.0f, 1.0f));

		/**
		* Defines a parent to the entity
		* @param p_parent
		*/
		void SetParent(AEntity& p_parent);

		Data::Transform transform;

	private:
		AEntity* m_parent;
	};
}

#endif // _AENTITY_H