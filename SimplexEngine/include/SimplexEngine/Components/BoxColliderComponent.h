/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _BOXCOLLIDERCOMPONENT_H
#define _BOXCOLLIDERCOMPONENT_H

#include <glm/glm.hpp>

#include "SimplexEngine/Components/AColliderComponent.h"

namespace SimplexEngine::Components
{
	/**
	* The BoxColliderComponent represents a simple box collider wrapping bullet boxShape
	*/
	class API_SIMPLEXENGINE BoxColliderComponent final : public AColliderComponent
	{
	public:
		/**
		* Constructor of the BoxColliderComponent
		* @param p_owner
		* @param p_size
		*/
		BoxColliderComponent(SimplexEngine::Actors::Actor& p_owner, const glm::vec3& p_size);

		/**
		* Destructor of the the BoxColliderComponent
		*/
		virtual ~BoxColliderComponent();
	};
}

#endif // _BOXCOLLIDERCOMPONENT_H