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
		* @param p_position
		* @param p_rotation
		*/
		AEntity(AltMath::Vector3f p_position, AltMath::Quaternion p_rotation);

		Data::Transform transform;
	};
}

#endif // _AENTITY_H