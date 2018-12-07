/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _ACTOR_H
#define _ACTOR_H

#include <vector>
#include <memory>

#include "Rasterizer/Data/Transform.h"

namespace Rasterizer::Components
{
	/* Forward declaration to prevent multiple inclusion */
	class AActorComponent;
}

namespace Rasterizer::Actors
{
	/**
	* The actor is an entity that can get spawned in the scene
	*/
	class Actor
	{
	public:
		/**
		* Return a component
		*/
		template<typename T>
		T* GetComponent()
		{
			static_assert(std::is_base_of<Components::AActorComponent, T>::value, "T should derived from AActorComponent");

			for (auto& component : m_components)
				if (T* result = std::dynamic_pointer_cast<T>(&component); result)
					return result;

			return nullptr;
		}

		template<typename T, typename ... Args>
		T& AddComponent(Args&&... p_args)
		{
			static_assert(std::is_base_of<Components::AActorComponent, T>::value, "T should derived from AActorComponent");

			m_components.emplace_back(this, p_args...);
			return m_components.at(m_components.size() - 1);
		}

	public:
		/* Actor transform is public */
		Data::Transform transform;

	private:
		std::vector<Components::AActorComponent> m_components;
	};
}

#endif // _ACTOR_H