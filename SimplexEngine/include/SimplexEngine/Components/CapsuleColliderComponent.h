/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _CAPSULECOLLIDERCOMPONENT_H
#define _CAPSULECOLLIDERCOMPONENT_H

#include "SimplexEngine/Components/AColliderComponent.h"

namespace SimplexEngine::Components
{
	/**
	* The CapsuleColliderComponent represents a simple capsule collider wrapping bullet capsuleShape
	*/
	class API_SIMPLEXENGINE CapsuleColliderComponent : public AColliderComponent
	{
		/**
		* Constructor of the CapsuleColliderComponent
		* @param p_owner
		* @param p_radius
		* @param p_height
		*/
		CapsuleColliderComponent(SimplexEngine::Actors::Actor& p_owner, float p_radius, float p_height);

		/**
		* Destructor of the the CapsuleColliderComponent
		*/
		~CapsuleColliderComponent();
	};
}

#endif // _CAPSULECOLLIDERCOMPONENT_H
