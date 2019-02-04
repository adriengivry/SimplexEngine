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

#include "SimplexEngine/Scenes/SceneManager.h"
#include "SimplexEngine/Components/RigidbodyComponent.h"

namespace SimplexEngine::Physics
{
	/**
	* Handle the creation and update of the physical world
	*/
	class PhysicsManager final
	{
	public:
		/**
		* Create the PhysicsManager
		* @param p_sceneManager (Needed to iterate over current scene actors)
		*/
		PhysicsManager(Scenes::SceneManager& p_sceneManager);

		/**
		* Destructor of the PhysicsManager
		*/
		~PhysicsManager();

		/**
		* Update the physical world
		*/
		void Update(float p_deltaTime);

	private:
		void MoveRigidbody(Components::RigidbodyComponent& p_target);
		void OnComponentAdded(Components::AActorComponent& p_component);
		void OnComponentRemoved(Components::AActorComponent& p_component);

	private:
		Scenes::SceneManager& m_sceneManager;

		btDynamicsWorld*			m_world;
		btDispatcher*				m_dispatcher;
		btCollisionConfiguration*	m_collisionConfig;
		btBroadphaseInterface*		m_broadphase;
		btConstraintSolver*			m_solver;
	};
}

#endif // _PHYSICSMANAGER_H