/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _ACTOR_INL
#define _ACTOR_INL

#include "SimplexEngine/Actors/Actor.h"

namespace SimplexEngine::Actors
{
	template<typename T>
	inline std::shared_ptr<T> Actor::GetComponent()
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

	template<typename T, typename ...Args>
	inline T & Actor::AddComponent(Args && ...p_args)
	{
		static_assert(std::is_base_of<Components::AActorComponent, T>::value, "T should derived from AActorComponent");

		m_components.push_back(std::make_shared<T>(*this, p_args...));
		T& instance = *dynamic_cast<T*>(m_components.at(m_components.size() - 1).get());
		ComponentAddedEvent.Invoke(instance);
		return instance;
	}

	template<typename T>
	inline bool Actor::RemoveComponent()
	{
		static_assert(std::is_base_of<Components::AActorComponent, T>::value, "T should derived from AActorComponent");

		std::shared_ptr<T> result(nullptr);

		for (auto it = m_components.begin(); it != m_components.end(); ++it)
		{
			result = std::dynamic_pointer_cast<T>(*it);
			if (result)
			{
				ComponentRemovedEvent.Invoke(*result.get());
				m_components.erase(it);
				return true;
			}
		}

		return false;
	}

	template<typename T, typename ...Args>
	inline T & Actor::AddBehaviour(Args && ...p_args)
	{
		static_assert(std::is_base_of<Scripts::Behaviours::ABehaviour, T>::value, "T should derived from ABehaviour");

		m_behaviours.push_back(std::make_shared<T>(*this, p_args...));
		T& instance = *dynamic_cast<T*>(m_behaviours.at(m_behaviours.size() - 1).get());
		return instance;
	}

	template<typename T>
	inline bool Actor::RemoveBehaviour()
	{
		static_assert(std::is_base_of<Scripts::Behaviours::ABehaviour, T>::value, "T should derived from ABehaviour");

		std::shared_ptr<T> result(nullptr);

		for (auto it = m_behaviours.begin(); it != m_behaviours.end(); ++it)
		{
			result = std::dynamic_pointer_cast<T>(*it);
			if (result)
			{
				m_behaviours.erase(it);
				return true;
			}
		}

		return false;
	}
}

#endif // _ACTOR_INL
