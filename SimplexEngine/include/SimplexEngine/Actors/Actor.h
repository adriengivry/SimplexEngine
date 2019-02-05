/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _ACTOR_H
#define _ACTOR_H

/* Retrocompatibility issue fixed with this macro definition (Visual Studio 15.8 issue) */
#define _ENABLE_EXTENDED_ALIGNED_STORAGE

#include <vector>
#include <memory>
#include <algorithm>

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Components/AActorComponent.h"
#include "SimplexEngine/Scripts/Behaviours/ABehaviour.h"
#include "SimplexEngine/Data/Transform.h"

namespace SimplexEngine::Actors
{
	/**
	* The actor is an entity that can get spawned in the scene
	*/
	class API_SIMPLEXENGINE Actor
	{
	public:
		/**
		* Try to get a component from the actor
		*/
		template<typename T>
		std::shared_ptr<T> GetComponent();

		/**
		* Add a component to the actor
		*/
		template<typename T, typename ... Args>
		T& AddComponent(Args&&... p_args);

		/**
		* Remove a component to the actor
		*/
		template<typename T>
		bool RemoveComponent();

		/**
		* Add a behaviour to the actor
		*/
		template<typename T, typename ... Args>
		T& AddBehaviour(Args&&... p_args);

		/**
		* Remove a component to the actor
		*/
		template<typename T>
		bool RemoveBehaviour();

		/**
		* Update every behaviours attached to this actor
		* @param p_deltaTime
		*/
		void UpdateBehaviours(float p_deltaTime);

		/**
		* Mark the actor as "dead" and wait the scene cleaner to delete it from the memory
		*/
		void Destroy();

		/**
		* Return true if the actor is marked as "dead"
		*/
		bool IsDestroyed() const;

	public:
		/* Actor transform is public */
		Data::Transform transform;
		Eventing::Event<Components::AActorComponent&> ComponentAddedEvent;
		Eventing::Event<Components::AActorComponent&> ComponentRemovedEvent;

	private:
		std::vector<std::shared_ptr<Components::AActorComponent>> m_components;
		std::vector<std::shared_ptr<Scripts::Behaviours::ABehaviour>> m_behaviours;
		bool m_destroyed = false;
	};
}

#include "SimplexEngine/Actors/Actor.inl"

#endif // _ACTOR_H