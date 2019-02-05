/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _RIGIDBODYCOMPONENT_H
#define _RIGIDBODYCOMPONENT_H

#include <bullet/btBulletCollisionCommon.h>
#include <bullet/btBulletDynamicsCommon.h>

#include <glm/glm.hpp>

#include "SimplexEngine/Components/AActorComponent.h"
#include "SimplexEngine/Components/AColliderComponent.h"

namespace SimplexEngine::Components
{
	/**
	* The rigidbody component handle physics application to the owning actor
	*/
	class API_SIMPLEXENGINE RigidbodyComponent final : public AActorComponent
	{
	public:
		/**
		* Constructor of the RigidbodyComponent
		* @param p_owner
		* @param p_mass
		*/
		RigidbodyComponent(SimplexEngine::Actors::Actor& p_owner, float p_mass);

		/**
		* Destructor of the RigidbodyComponent
		*/
		~RigidbodyComponent();

		/**
		* Defines a velocity for the RigidbodyComponent
		* @param p_velocity
		*/
		void SetVelocity(const glm::vec3& p_velocity);

		/**
		* Return the current velocity of the rigidbody
		*/
		glm::vec3 GetVelocity() const;

		/**
		* Return the transform
		*/
		btTransform* GetTransform();

		/**
		* Return the motion
		*/
		btMotionState* GetMotion();

		/**
		* Return the body
		*/
		btRigidBody* GetBody();

	private:
		btTransform m_transform;
		btMotionState* m_motion;
		btRigidBody* m_body;
	};
}

#endif // _RIGIDBODYCOMPONENT_H
