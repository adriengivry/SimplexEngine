/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _ACOLLIDERCOMPONENT_H
#define _ACOLLIDERCOMPONENT_H

#include <bullet/btBulletCollisionCommon.h>

#include "SimplexEngine/Components/AActorComponent.h"

namespace SimplexEngine::Components
{
	/**
	* The AColliderComponent defines a base for every colliders of the SimplexEngine
	* It simply wraps a btCollisionShape of bullet physics (btCollisionShape is itself abstract
	* and can contains any collision shape)
	*/
	class API_SIMPLEXENGINE AColliderComponent : public SimplexEngine::Components::AActorComponent
	{
	public:
		/**
		* Constructor of the ACollidercomponent
		* @param p_owner
		*/
		AColliderComponent(SimplexEngine::Actors::Actor& p_owner);

		/**
		* Destructor of the AColliderComponent (Virtual destructor that children should implement)
		*/
		virtual ~AColliderComponent();

		/**
		* Return the collision shape of the AColliderComponent
		*/
		btCollisionShape* GetShape();

	protected:
		btCollisionShape* m_shape;
	};
}

#endif // _ACOLLIDERCOMPONENT_H