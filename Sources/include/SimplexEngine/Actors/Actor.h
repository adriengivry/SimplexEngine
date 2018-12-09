/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _ACTOR_H
#define _ACTOR_H

#include <vector>
#include <memory>

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Components/AActorComponent.h"
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
		std::shared_ptr<T> GetComponent()
		{
			static_assert(std::is_base_of<Components::AActorComponent, T>::value, "T should derived from AActorComponent");

			std::shared_ptr<T> result(nullptr);

			for (auto component : m_components)
			{
				result = std::dynamic_pointer_cast<T>(component);
				if (result)
					break;
			}

			return result;
		}

		/**
		* Add a component to the actor
		*/
		template<typename T, typename ... Args>
		T& AddComponent(Args&&... p_args)
		{
			static_assert(std::is_base_of<Components::AActorComponent, T>::value, "T should derived from AActorComponent");

			m_components.push_back(std::make_shared<T>(*this, p_args...));
			return *dynamic_cast<T*>(m_components.at(m_components.size() - 1).get());
		}

	public:
		/* Actor transform is public */
		Data::Transform transform;

	private:
		std::vector<std::shared_ptr<Components::AActorComponent>> m_components;
	};
}

#endif // _ACTOR_H