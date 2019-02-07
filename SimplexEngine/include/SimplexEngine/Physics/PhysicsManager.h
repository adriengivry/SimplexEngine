/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _PHYSICSMANAGER_H
#define _PHYSICSMANAGER_H

#include <bullet/btBulletCollisionCommon.h>
#include <bullet/btBulletDynamicsCommon.h>

#include "SimplexEngine/Components/RigidbodyComponent.h"

namespace SimplexEngine::Scenes { class SceneManager; }

namespace SimplexEngine::Physics
{
	/**
	* Handle the creation and update of the physical world
	*/
	class API_SIMPLEXENGINE PhysicsManager final
	{
	public:
		/**
		* Create the PhysicsManager
		*/
		PhysicsManager();

		/**
		* Destructor of the PhysicsManager
		*/
		~PhysicsManager();

		/**
		* Defines the gravity to apply to the world
		* @param p_gravity
		*/
		void SetGravity(const glm::vec3& p_gravity);

		/**
		* Define the sceneManager to use
		* @param p_sceneManager
		*/
		void ProvideSceneManager(Scenes::SceneManager& p_sceneManager);

		/**
		* Update the physical world
		*/
		void Update(float p_deltaTime);

	private:
		void MoveRigidbody(Components::RigidbodyComponent& p_target);
		void OnComponentAdded(Components::AActorComponent& p_component);
		void OnComponentRemoved(Components::AActorComponent& p_component);

	private:
		Scenes::SceneManager* m_sceneManager;

		btDynamicsWorld*			m_world;
		btDispatcher*				m_dispatcher;
		btCollisionConfiguration*	m_collisionConfig;
		btBroadphaseInterface*		m_broadphase;
		btConstraintSolver*			m_solver;
	};
}

#endif // _PHYSICSMANAGER_H