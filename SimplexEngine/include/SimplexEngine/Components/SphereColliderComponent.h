/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _SPHERECOLLIDERCOMPONENT_H
#define _SPHERECOLLIDERCOMPONENT_H

#include "SimplexEngine/Components/AColliderComponent.h"

namespace SimplexEngine::Components
{
	/**
	* The SphereColliderComponent represents a simple sphere collider wrapping bullet sphereShape
	*/
	class API_SIMPLEXENGINE SphereColliderComponent : public AColliderComponent
	{
		/**
		* Constructor of the SphereColliderComponent
		* @param p_owner
		* @param p_radius
		*/
		SphereColliderComponent(SimplexEngine::Actors::Actor& p_owner, float p_radius);

		/**
		* Destructor of the the SphereColliderComponent
		*/
		~SphereColliderComponent();
	};
}

#endif // _SPHERECOLLIDERCOMPONENT_H
